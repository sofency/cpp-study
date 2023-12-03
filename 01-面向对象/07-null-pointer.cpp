#include <iostream>
using namespace std;

class Person
{
public:
  void echo()
  {
    cout << "hello world success" << endl;
  }
  void echo_name()
  {
    // 默认执行的时候 name 会执行 this->name
    cout << "hello world error" << name << endl;
  }
  string name;
};
// 函数的执行
int main(int argc, char const *argv[])
{

  Person *p = NULL;
  p->echo(); // 正确执行
  // p->echo_name(); // 错误执行 因为对应this为null
  return 0;
}
