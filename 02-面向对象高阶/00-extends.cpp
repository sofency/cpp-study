#include <iostream>
using namespace std;
// class A: public B{} 语法
// public    子类    对象    都可访问
// protected 子类            可访问
// private   只有自身可访问

// cpp中 子类和父类有相同的属性和方法 子类不会重写 而是都保留 只不过调用父类的时候 需要加引用
class Base {
 public:
  Base() {
    a = 100;
    b = 200;
    c = 300;
    m = 400;
  }
  void func() { cout << "Base func" << endl; }
  int a;
  int m;

 protected:
  int b;

 private:
  int c;
};

class BaseOne {
 public:
  int m;
  BaseOne() { m = 1; }
};

// son 对象占用了16个字节
// 父类中私有成员也是被子类继承下去，只是被编译器给隐藏后访问不到
// 也可以进行多继承
class Son : public Base, public BaseOne {
 public:
  Son() {
    a = 10;  // 这样福慧复写父类的属性
  }
  // 对于静态的成员属性和函数 处理逻辑一样
  // 如果子类中出现和父类同名的成员函数，子类的同名成员会隐藏掉父类中所有同名成员函数
  // 如果想访问到父类中被隐藏的同名成员函数，需要加作用域
  void func() { cout << "Son func 调用" << endl; }
  int a;
};

int main(int argc, char const* argv[]) {
  Son son;
  cout << son.Base::a << endl;  // 调用父类的属性
  son.func();                   // 调用自身的方法
  son.Base::func();             // 调用父类的同名方法

  // son.m // 这样会报错不知道是哪个父类中的属性
  // 需要加作用域
  cout << son.BaseOne::m << endl;
  return 0;
}
