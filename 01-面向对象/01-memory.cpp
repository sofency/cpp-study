#include <iostream>
using namespace std;
// 内存分区模型
// c++程序在执行时，将内存分为4个区域
// 代码区：存放函数体的二进制代码，由操作系统进行管理；  共享    只读
// 全局区：存放全局变量 和静态变量 以及 常量（const修饰） 常量区  const修饰的全局常量 和字符串常量
// 栈区：由编译器自动分配释放，存放函数的参数值，局部变量等
// 堆区：由程序员分配和释放，若程序员不释放，程序结束时由操作系统回收

// 返回局部变量地址
int *func()
{
  int p = 10;
  return &p;
}

// 返回局部变量地址
int *funct()
{
  // 利用new 关键字，可以将数据开辟到堆区
  // 堆区的数据 由程序员管理释放 释放 delete
  int *p = new int(10);
  return p;
}

// 引用作为函数的返回值
// 不要返回局部变量的引用
int &test()
{
  static int a = 10; // 放到全局区中
  return a;
}

// 这样 我们在函数体里面修改 则外面也要变化 因此我们必须加上const 来进行限制
void showValue(const int &val)
{
  // 传入引用 引用修改
  // val = 100; 外面的值就要改变
  cout << "inner:" << val << endl;
}

// 测试删除数据情况
void test_delete()
{
  // 这样可以
  int *q = funct();
  cout << *q << endl; // 第一次可以打印正确的数字，是因为编译器做了保留
  cout << *q << endl; // 第二次这个数据依旧可以访问 这时的数据由程序员管理
  // 释放
  delete q;

  // 创建数组
  int *arr = new int[10];
  for (int i = 0; i < 10; i++)
  {
    arr[i] = i + 10;
  }
  // 数组数据的释放
  delete[] arr;
}

int main(int argc, char const *argv[])
{
  // 静态变量 和全局变量存储的位置很近 都是放在全局区
  static int var = 9;
  int *p = func();
  cout << *p << endl; // 第一次可以打印正确的数字，是因为编译器做了保留
  cout << *p << endl; // 第二次这个数据就不再保留了

  // 引用
  // 语法 int a = 10; int &b = a;
  int a = 10;
  // 引用必须初始化 int &b; 这样写错误的 且初始化后 不可以更改
  int &b = a;
  cout << a << " " << b << endl; // 10 10
  // 修改
  b = 100;
  cout << a << " " << b << endl; // 100 100

  // 测试引用 引用就是指针常量
  int &ref = test();
  cout << ref << endl; // 10
  cout << ref << endl; // 10
  // 修改引用的值
  test() = 1000;
  cout << ref << endl; // 1000
  cout << ref << endl; // 1000

  int value = 10;
  // 里面修改了a的值
  showValue(value);
  cout << value << endl;
  return 0;
}
