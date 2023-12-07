#include<iostream>
#include<thread>
#include<mutex>
#include<chrono>
#include<atomic>
using namespace std;

struct Counter
{
  atomic_int value = {0};
  mutex locker;

  void increase()
  {
    // 这种操作在C++中是线程安全的
    value.fetch_add(1);
    cout << "increament number: " << value << " thread id : " << this_thread::get_id() << endl;
    this_thread::sleep_for(chrono::milliseconds(500));
  }

  void decrement()
  {
    // 这种操作在C++中是线程安全的
    value.fetch_sub(1);
    cout << "decrement number: " << value << " thread id : " << this_thread::get_id() << endl;
    this_thread::sleep_for(chrono::milliseconds(500));
  }
};

/**
 * @brief 
 * 1.线程t1开始执行，调用 increase 方法，value 从0增加到1。
 * 2. 在t1还未打印增加后的值的时候，线程调度器暂停了t1的执行，开始执行t2。
 * 3. 线程t2开始执行，调用 decrement 方法，value 从1减少到0。
 * 4. t2打印出减少后的值0。
 * 5. 线程调度器再次暂停t2的执行，恢复t1的执行。
 * 6. t1打印出它之前增加后的值，也就是0（因为在线程t1的视角里，它增加后的值还没被打印就被线程t2减少了）。
 * 所以，虽然你的每个操作（增加和减少）都是线程安全的，但是在打印值时并没有保证线程安全，这就可能导致你看到两个0的输出。
 * 使用互斥锁 避免打印的时候被线程不安全影响，
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char const *argv[])
{
  Counter counter;
  auto increment = bind(&Counter::increase, &counter);
  auto decrement = bind(&Counter::decrement, &counter);
  thread t1(increment);

  thread t2(decrement);

  // 尽管上面 输出的时候受线程不安全的影响，但是最终的结果是一样的

  t1.join();
  t2.join();
  cout<< counter.value.load() << endl;

  return 0;
}
