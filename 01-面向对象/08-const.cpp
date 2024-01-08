#include <iostream>
using namespace std;

class Person {
 public:
  // 加了const表示常函数 常函数只能修改常变量
  void func() const {
    this->location = "beijing";
    // this->name = "sofency"; error
  }

  // 普通函数都能修改
  void func1() {
    this->location = "beijing";
    this->name = "alice";
  }
  string name;
  mutable string location;  // 加了后可以在常量成员 函数中修改变量
};

int main(int argc, char const* argv[]) {
  const Person person;
  // 同理 常对象 只能调用常函数
  person.func();
  // person.func1();

  // 普通对象都能调用
  Person p;
  p.func();
  p.func1();

  return 0;
}
