#include<iostream>
#include<mutex>
using namespace std;

struct Calculate
{
  Calculate() : m_i(6) {}

    void mul(int x)
    {
        lock_guard<recursive_mutex> locker(m_mutex);
        m_i *= x;
    }

    void div(int x)
    {
        lock_guard<recursive_mutex> locker(m_mutex);
        m_i /= x;
    }

    void both(int x, int y)
    {
        lock_guard<recursive_mutex> locker(m_mutex);
        mul(x);
        div(y);
    }

    int m_i;
    // 如果换成mutex 则会阻塞住;因为mutex是不可重入锁
    recursive_mutex m_mutex;
};

int main(int argc, char const *argv[])
{
  Calculate cal;
  cal.both(1,2);
  return 0;
}
