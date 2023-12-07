#include<iostream>
#include<thread>
#include<future>
using namespace std;

/**
 * @brief 线程异步操作
 * 
 */

void primise_future()
{
  promise<int> ptr;
  thread t([](promise<int> &person){
    // p.set_value(100);
    this_thread::sleep_for(chrono::seconds(3));
    cout << "睡醒了..." << endl;
    person.set_value_at_thread_exit(100); // 在执行完毕退出时激活
  }, ref(ptr));
  future<int> f = ptr.get_future();
  cout << "获取到的未来值为:" << f.get() << endl;
  t.join();
}

void package_task_future()
{
  // task中封装的是要执行的任务
  // int(int) 表示 输入为int,返回值为int
  packaged_task<int(int)> task([](int x){
    this_thread::sleep_for(chrono::seconds(3));
    return x+100;
  });

  // ref(task) 是将task的引用传进入
  thread t1(ref(task), 100);

  // 获取未来值
  cout << "获取值为:" << task.get_future().get() << endl;

  t1.join();
}

// async形式
void async_future_with_thread()
{
  cout << "主线程ID: " << this_thread::get_id() << endl;

  // 内部是创建线程执行
  future<int> f = async([](int x){
    cout << "子线程ID: " << this_thread::get_id() << endl;
    this_thread::sleep_for(chrono::seconds(3));
    return x + 100;
  }, 100);
  // 这样操作获取值
  // int result = f.get();
  // 我们可以循环操作根据状态来取值
  future_status status;
  do {
    status = f.wait_for(chrono::seconds(1));
    switch (status)
    {
      case future_status::deferred :
        cout << "线程还未执行" << endl;
        f.wait();
        break;
      case future_status::timeout :
        cout << "线程还未执行完毕" << endl;
        break;
      case future_status::ready :
        cout << "子线程返回值: " << f.get() << endl;
        break;
      default:
        break;
    }
  }while(status != future_status::ready);

}

/**
 * @brief 由于指定了launch::deferred 策略，因此调用async()函数并不会创建新的线程执行任务，
 * 当使用future类对象调用了get()或者wait()方法后才开始执行任务
 * （此处一定要注意调用wait_for()函数是不行的）
 *  主线程ID: 0x7ff855e39640
 *  数据为:子线程ID: 0x7ff855e39640
 *  只有在get操作才开始执行
 */
void async_no_thread()
{
  // 内部是创建线程执行
  cout << "主线程ID: " << this_thread::get_id() << endl;
  future<int> f = async(launch::deferred, [](int x){
    cout << "子线程ID: " << this_thread::get_id() << endl;
    this_thread::sleep_for(chrono::seconds(3));
    return x + 100;
  }, 100);
  this_thread::sleep_for(chrono::seconds(5));
  cout << "数据为:" << f.get() << endl;
}
int main(int argc, char const *argv[])
{
  async_no_thread();

  return 0;
}

