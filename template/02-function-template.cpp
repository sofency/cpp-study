#include <iostream>
using namespace std;
// 全局函数类外实现 比较复杂

// 这段代码如果下类下面 类中的函数会找不到
template <class T1, class T2>
class Person;

// 之所以提前声明 因为函数show_person_info 已经使用了该类

template <class T1, class T2>
// 全局函数没必要加作用域
void show_person_info(Person<T1, T2> p)
{
  cout << "类外实现 name:" << p.name << endl;
}

template <class T1, class T2>
class Person
{
  // 全局函数类内实现
  friend void show_info(Person<T1, T2> p)
  {
    cout << "name:" << p.name << endl;
  }

  // 如果是全局函数类外实现 需要让编译器提前知道这个函数的存在
  // 需要加空参数列表<> 不加<> 则是普通的函数 不是模版函数
  // 必须在前面提前 声明该函数
  friend void show_person_info<>(Person<T1, T2> p);

public:
  Person(T1 name, T2 age)
  {
    this->name = name;
    this->age = age;
  }
  T1 name;
  T2 age;
};

int main(int argc, char const *argv[])
{
  Person<string, int> person("Tom", 12);
  // 调用全局函数类内实现的函数
  show_info(person);

  show_person_info(person);
  return 0;
}
