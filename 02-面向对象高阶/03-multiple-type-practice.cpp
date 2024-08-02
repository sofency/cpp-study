#include <iostream>
using namespace std;

class Animal {
 public:
  virtual void eat() = 0;
  virtual void study() = 0;
  virtual void action() {
    eat();
    study();
  }

  // 虚析构 或者下面
  // virtual ~Animal()
  // {
  //   cout << "父类析构" << endl;
  // };

  // 或者纯虚析构 但是需要实现 类外实现
  virtual ~Animal() = 0;
};

Animal::~Animal() {
  cout << "父类析构" << endl;
}
class Dog : public Animal {
 public:
  virtual void eat() { cout << "吃鸡腿" << endl; }

  virtual void study() { cout << "学习深蹲" << endl; }

  ~Dog() { cout << "子类的析构" << endl; }
};

int main(int argc, char const* argv[]) {
  Animal* animal = new Dog;
  animal->action();

  // 父类不写虚析构的话 是无法执行 子类的析构函数的
  delete animal;

  return 0;
}
