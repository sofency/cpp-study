#include<iostream>
#include<mutex>
#include<thread>
using namespace std;
/**
 * @brief 线程同步
 * 
 */
int num = 0;
mutex num_lock;

void do_something(int id)
{
  for (int i = 0; i < 10; i++)
  {
    num_lock.lock();
    num ++;
    cout << "id:" << id << ", i:"<< i<< " , num:" << num << endl;
    num_lock.unlock();
    this_thread::sleep_for(chrono::milliseconds(200));
  }
}

mutex guard_lock;

void do_something_lock_guard(int id)
{
  for (int i = 0; i < 3; i++)
  {
    // 这样就可以不用手动unlock() 缺点就是 它会把整个for循环体都作为临界区，即无法细粒度控制临界区的范围
    lock_guard<mutex> lock(guard_lock);
    num ++;
    cout << "id:" << id << ", i:"<< i<< " , num:" << num << endl;
    this_thread::sleep_for(chrono::seconds(1));
  }
}

int main(int argc, char const *argv[])
{
  thread t1(do_something, 1);
  thread t2(do_something, 2);

  t1.join();
  t2.join();
  return 0;
}
