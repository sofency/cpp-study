#include <iostream>
using namespace std;

// 1.如果普通函数和模版函数同时存在（函数名和参数个数都相同，且输入参数类型和普通函数的参数类型一样），优先执行普通函数
// 2.要想执行模版函数，需要加空模版参数列表
// 3.模版函数也可以发生重载
// 4.如果模版函数更适合，则优先执行模版函数 比如输入参数为char ,普通函数为int  这样优先执行模版函数
// 最好不要同时使用

void my_print(int a, int b)
{
  cout << "普通函数," << a << endl;
}

template <typename T>
void my_print(T a, T b)
{
  cout << "模版函数" << a << endl;
}

template <typename T>
void my_print(T a, T b, T c)
{
  cout << "模版函数" << a << endl;
}

// 类模版没有自动类型推导的使用方式
// 类模版在模版参数列表中可以有默认参数
// 类模版中的成员函数 只有在调用的时候才会执行 比如模版 T 是person 模版方法中调用了person.show()方法 可能不存在，但是不会报错
template <class NameType, class AgeType = int>
class Person
{
public:
  Person(NameType name, AgeType age)
  {
    this->name = name;
    this->age = age;
  }

  void show()
  {
    cout << "name:" << this->name << ", age:" << this->age << endl;
  }
  NameType name;
  AgeType age;
};

// 函数的模版化
template <class T1, class T2>
void print_person(Person<T1, T2> &p)
{
  p.show();
  cout << "查看参数类型" << typeid(T1).name() << endl;
  cout << "查看参数类型" << typeid(T2).name() << endl;
}

// 如果父类有模版参数 子类在继承的时候尽量也写上
template <class T>
class Base
{
public:
  T base;
};

// 这样即指明了父类的类型，同样也可以定义子类中属性的类型
template <class T1, class T2>
class Son : public Base<T2>
{
public:
  Son(T1 name, T2 age);
  void show();
  T1 name;
  T2 age;
};

// 类构造函数 类外实现
template <class T1, class T2>
Son<T1, T2>::Son(T1 name, T2 age)
{
  this->name = name;
  this->age = age;
}

template <class T1, class T2>
void Son<T1, T2>::show()
{
  cout << this->name << ":" << this->age << endl;
}

int main(int argc, char const *argv[])
{
  my_print(2, 3);      // 优先执行普通函数
  my_print<>(2, 3);    // 设置为空参数列表 执行模版函数
  my_print<>(2, 3, 5); // 设置为空参数列表 执行模版函数

  char a = 12;
  char b = 14;
  my_print(a, b); // 如果执行普通函数 还要进行类型转换 所以执行模版函数

  Person<string, int> person("sofency", 19);
  person.show();

  // 使用默认
  Person<string> pe("sofency", 19);
  pe.show();

  print_person(pe);

  // 类模版必须指定类型 否则报错
  Son<string, int> son("sofency", 21);
  son.show();
  return 0;
}
