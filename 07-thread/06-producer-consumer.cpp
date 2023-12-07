#include<iostream>
#include<thread>
#include<list>
#include<chrono> // 可以不引用
#include<condition_variable>
using namespace std;

/**
 * @brief 消息队列
 * 
 */
class MessageQueue
{
  public:
    MessageQueue(int num):max_size(num) {}

    void put(const int& num)
    {
      unique_lock<mutex> locker(m_mutex);

      // cout << "队列已满, 请等待消费..." << endl;
      not_full.wait(locker, [this](){ return container.size() !=  max_size;});
    
      container.push_back(num);
      cout << num << " 被生产" << endl;
      // 通知消费者去消费
      not_empty.notify_one();
    }

    int take()
    {
        unique_lock<mutex> locker(m_mutex);
        while (container.empty())
        {
          cout << "当前队列为空, 等待生产" << endl;
          not_empty.wait(locker);
        }
        int x = container.front();
        container.pop_front();
        // 通知生产者该生产了
        not_full.notify_one();
        cout << x << " 被消费" << endl;
        return x; 
    }

    bool empty()
    {
      lock_guard<mutex> locker(m_mutex);
      return container.empty();
    }

    bool full()
    {
      lock_guard<mutex> locker(m_mutex);
      return container.size() == max_size;
    }

    int size()
    {
      lock_guard<mutex> locker(m_mutex);
      return container.size();
    }

  /**
   * @brief condition_variable 变量一般在take和put的时候配置 独占所 unique_lock使用
   * condition_variable_any 在take和put的时候还是lock_guard<mutex>使用
   * 这种情况只有等生命周期结束后才能将互斥锁释放，但是condition_variable_any可以和多种互斥锁配合使用，应用场景更广
   * condition_variable智能和独占的非递归互斥锁配合使用
   */
  private:
    list<int> container; // 存储数据队列
    mutex m_mutex; // 互斥锁
    condition_variable not_full;
    condition_variable not_empty;
    int max_size; // 队列的最大容量
};

int main(int argc, char const *argv[])
{
  MessageQueue task(50);
  auto producer = bind(&MessageQueue::put, &task, placeholders::_1);
  auto consumer = bind(&MessageQueue::take, &task);
  thread producer_thread[3];
  thread consumer_thread[3];

  // 初始化线程 并进行执行
  for(int i = 0; i < 3; i++)
  {
    producer_thread[i] = thread(producer, i+100);
    consumer_thread[i] = thread(consumer);
  }


  for(int i = 0; i < 3; i++)
  {
    producer_thread[i].join();
    consumer_thread[i].join();
  }
  return 0;
}
