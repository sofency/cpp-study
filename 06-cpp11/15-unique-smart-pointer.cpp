#include<iostream>
#include<functional>
using namespace std;
/**
 * @brief 
 * 独占智能指针
 * unique_ptr 是一个独占智能指针，它不允许其他的智能指针共享其内部的指针
 */

unique_ptr<int> func()
{
  // 这是创建个匿名的独占指针
  return unique_ptr<int>(new int(100));
}
int main(int argc, char const *argv[])
{
  // 创建独占智能指针
  unique_ptr<int> ptr(new int(10));
  // unique_ptr<int> ptr2 = ptr; // error 它不允许将一个unique_ptr赋值给另一个unique_ptr
  // 可以通过move转移给其他的unique_ptr
  unique_ptr<int> target = std::move(ptr); // 这样原始指针的所有权就被转移了
  // 还可以通过函数返回值
  unique_ptr<int> target1 = func(); 

  // 原本get操作已经获取不到了，解除对原始内存的管理 get
  cout << ptr.get()  << " origin target:" << target.get()<< endl;
  ptr.reset(); //只不过显示声明下释放管理权
  target.reset(new int(250)); //重新指定智能指针管理的原始对象 是新的地址 而不是在原来的位置进行覆盖操作
  cout << "current target location:" << target.get() << ",value:" << *target.get() << endl;

  // 独占指针指定删除器
  // void(*)(int*) 它定义了一个指向函数的指针，该函数接受一个指向整数的指针作为参数，并返回void
  unique_ptr<int, void(*)(int*)> ptr2(new int(10), [](int *p) {delete p;});

  // unique_ptr<int, func_ptr> ptr1(new int(10), [&](int*p) {delete p; });	// error
  // 在lambda表达式没有捕获任何外部变量时，可以直接转换为函数指针，
  // 一旦捕获了就无法转换了，如果想要让编译器成功通过编译，那么需要使用可调用对象包装器来处理声明的函数指针
  unique_ptr<int, function<void(int*)>> ptr3(new int(10), [&](int *p) {delete p;});
  return 0;
}
