#include<iostream>
using namespace std;

// lambda 捕捉方式
// [capature]  
// [] 不捕捉任何变量
// [&]捕捉外部作用域的所有变量，并作为引用在函数体内使用
// [=] 捕捉外部作用域所有变量，并作为副本在函数体内使用 只读
// [=, &foo] 按值捕捉外部作用域中的所有变量，并按照引用补获外部变量foo
// [bar] 按值捕捉bar变量，同时不捕获其他变量
// [&bar] 按值捕捉bar变量，同时不捕获其他变量
// [this] 捕获当前类中的this

// 语法
// [capture](params) opt -> ret {body;}; opt 是函数选项 ret 是返回值类型
// opt -> ret 可以省略不写

class Test
{
  public:
    void output(int x, int y)
    {
      // [](){ cout << number << endl;}(); error 访问不到
      // &也可以
      [=](){ cout << number << "," << x << "," << y << endl;}();
      
      // [this](){ cout << number << "," << x << "," << y << endl;}(); error 无法访问到x, y
      // 捕捉到x,y 穿进去的是const 类型的无法修改
      [this, x, y](){ cout << number << "," << x << "," << y << endl;}();

      // 如果想修改x 可以加multable 注意 只是在内部有效 不会影响外部的使用
      [this, x, y]() mutable{ cout << number << "," << x << "," << y << endl; x++;}();
      cout << "outer: x=" << x << endl;

      // 修改x 数据 传递引用类型进去 this不用传递 它本身就是指针类型
      [this, &x, &y](){ x = 20; number ++;}();
      cout << x << "," << number << endl;
    }
    int number = 100;
};

int main(int argc, char const *argv[])
{
  int num = 10;
  // 这样引用变量 可以修改外部的值
  [&](){ num = 20;}();

  // [=](){num = 29;}(); error 可以捕获到变量num 但是默认是const类型的无法修改
  [=](){ cout << num << endl;}();

  // [](){cout << num << endl;}(); error []表示不捕获外部任何变量
  cout << num << endl;

  Test test;
  test.output(1,2);
  return 0;
}
