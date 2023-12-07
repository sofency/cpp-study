#include<iostream>
#include<chrono>
#include<thread>
using namespace std;

/**
 * @brief 
 * 
 */

void func(int num, string str)
{
  for (int i = 0; i < 10; i++)
  {
    this_thread::sleep_for(chrono::milliseconds(500));
    cout << "子线程: i=" << i << " num: " << num << ", str: " << str << endl;
  }
}

void execute()
{
  for (int i = 0; i < 10; i++)
  {
    this_thread::sleep_for(chrono::seconds(1));
    cout << "子线程: i=" << i << endl;
  }
}

void foo()
{
  this_thread::sleep_for(chrono::seconds(2));
}

// joinable()函数用于判断主线程和子线程是否处理关联（连接）状态
// 线程中的资源是不能被复制的
void joinable()
{
  // 线程不指定要执行的函数不会运行 所以它的joinable为false
  thread t;
  cout << "before starting, joinable: " << t.joinable() << endl;
  // 开始执行线程里面的函数 所有返回true
  t = thread(foo);
  cout << "after starting, joinable: " << t.joinable() << endl;

  // join之后 函数就执行完了 所以子线程与主线程关系不存在了 所以返回false
  t.join();
  cout << "after joining, joinable: " << t.joinable() << endl;

  thread t1(foo);
  cout << "after starting, joinable: " << t1.joinable() << endl;
  // 子线程调用了detach()函数之后，父子线程分离，同时二者的连接断开，所以返回false
  t1.detach();
  cout << "after detaching, joinable: " << t1.joinable() << endl;
}

/**
 * @brief 
 * yield()，在线程中调用这个函数之后，处于运行态的线程会主动让出自己已经抢到的CPU时间片，
 * 最终变为就绪态，这样其它的线程就有更大的概率能够抢到CPU时间片了
 * 
 * detach()函数的作用是进行线程分离，分离主线程和创建出的子线程。在线程分离之后，主线程退出也会一并销毁创建出的所有子线程，
 * 在主线程退出之前，它可以脱离主线程继续独立的运行，任务执行完毕之后，这个子线程会自动释放自己占用的系统资源。建议使用join 
 * 子线程和主线程分离之后，在主线程中就不能再对这个子线程做任何控制了，比如：通过join()阻塞主线程等待子线程中的任务执行完毕，
 * 或者调用get_id()获取子线程的线程ID。有利就有弊，鱼和熊掌不可兼得，建议使用join()。
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char const *argv[])
{
  cout << "主线程的线程ID: " << this_thread::get_id() << endl;
  // 后面两个是func函数的参数
  thread t(func, 520, "i love you");
  thread th(execute);
  cout << "线程 t 的线程ID: " << t.get_id() << endl;
  cout << "线程t1的线程ID: " << th.get_id() << endl;

  // 等待他俩执行完成
  th.join();
  t.join();

  cout << "start sleep until 2 seconds" << endl;
  // 获取当前系统的时间
  auto now = chrono::system_clock::now();
  // 时间间隔为2s
  chrono::seconds sec(2);
  // 当前时间点后休眠2s
  this_thread::sleep_until(now + sec);

  cout << "CPU number :" << thread::hardware_concurrency() << endl;
  return 0;
}
