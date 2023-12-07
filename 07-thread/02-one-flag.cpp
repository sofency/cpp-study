#include<iostream>
#include<thread>
using namespace std;

/**
 * @brief 在某些特定的情况下，某些函数只能在多线程环境下调用一次，比如要初始化某个对象，而这个对象只能被初始化一次，
 * 就可以使用call_once()来保证函数在多线程环境下只能被调用一次。使用call_once()的时候，需要一个one_flag作为call_once()的传入参数
 * 
 */

once_flag flag;
void do_once(int num, string str)
{
  cout << "name: " << str << ", age: " << num << endl;
}

/**
 * @brief 
 * name: alice, age: 20  只有第一个传入的age name 输出了
 * do something age:1
 * do something age:2
 * do something age:3
 * 
 * @param age 
 * @param name 
 */
void do_something(int age, string name)
{
  // 静态的成员 同样也是只初始化第一次 
  static int num = 1;
  call_once(flag, do_once, age, name);
  cout << "do something age:" << num ++ << endl; 
}
int main(int argc, char const *argv[])
{
  /* code */
  thread t1(do_something, 20, "alice");
  thread t2(do_something, 19, "hello world");
  thread t3(do_something, 22, "sofency");

  t1.join();
  t2.join();
  t3.join();
  return 0;
}
