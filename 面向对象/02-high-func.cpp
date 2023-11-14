#include <iostream>
using namespace std;
// 函数默认值
// 如果某个位置已经有了参数，那么从这个位置到最后的参数必须有默认值
int add(int a, int b = 20, int c = 20, int = 10)
{
  return a + b + c;
}
// 如果函数声明中有默认参数，函数实现就不能有默认参数  即声明和实现仅有一个可以有默认值
int func(int a = 10, int b = 20);

// 函数重载 参数类型不同 参数个数不同 参数顺序不同
void funct(int a)
{
  cout << a << endl;
}

void funct(int a, int b)
{
  cout << a << ":" << b << endl;
}

void functi(int &a)
{
  cout << "functi(int &a) " << endl;
}

void functi(const int &a)
{
  cout << "functi(const int &a) " << endl;
}
int main(int argc, char const *argv[])
{

  // int = 10 是站位参数 也可以设置默认值 暂时没什么用 函数调用时如果没有默认值 必须传个值，但是函数内部无法使用
  cout << add(10, 19) << endl;
  cout << func(10) << endl;

  int a = 10;
  functi(a); // 调用的是functi(int &a) 因为引用只能指向一块内存空间

  functi(10); // 调用functi(const int &a)
  return 0;
}

int func(int a, int b)
{
  return a + b;
}