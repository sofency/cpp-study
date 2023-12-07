#include<iostream>
#include<thread>
using namespace std;
/**
 * @brief 超时锁 就是超所一定时间没获取到锁 就放弃获取锁的资源
 * 
 */
timed_mutex timed;
void work()
{
  chrono::seconds second(1);
  while (true)
  {
    if(timed.try_lock_for(second))
    {
      cout << "当前线程ID:" << this_thread::get_id() << "得到互斥锁资源"<< endl;
      // 模拟任务处理时间
      this_thread::sleep_for(chrono::seconds(4));
      timed.unlock();
      break;
    }
    else
    {
      cout << "当前线程ID:" << this_thread::get_id() << "未得到互斥锁资源"<< endl;
      // 模拟任务处理时间
      this_thread::sleep_for(chrono::milliseconds(50));
    }
  }
}

int main(int argc, char const *argv[])
{
  
  thread th(work);
  thread th1(work);
  
  th.join();
  th1.join();

  return 0;
}
