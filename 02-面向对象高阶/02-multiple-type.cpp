#include <iostream>
using namespace std;
// 多态
// 静态多态的函数地址早绑定，编译阶段确定函数地址
// 动态多态的函数地址晚绑定，运行阶段确定函数地址

class Animal
{
public:
  string name;
  // 虚函数
  // 作为动物父类 这个speak 没有绑定类型的话 没有什么意思 因此可以设置为纯虚函数 virtual void speak() = 0;
  // 只要包含一个纯虚函数 这个类就是抽象类
  // 1. 无法实例化当前Animal对象
  // 2. 子类必须实现父类的纯虚函数
  virtual void speak() = 0;

  // 必须加上该 不然 子类在堆区创建完对象后，delete操作会报错
  virtual ~Animal()
  {
    cout << "animal" << endl;
  }
};

class Cat : public Animal
{
public:
  void speak()
  {
    cout << name << ":小猫在说话" << endl;
  }
};

class Dog : public Animal
{
public:
  // 重写父类的函数
  virtual void speak()
  {
    cout << name << ":小狗在说话" << endl;
  }

  ~Dog()
  {
    cout << "dog" << endl;
  }
};

// 如果要想让猫说话 就让这个地址晚绑定
void doSpeak(Animal &animal)
{
  animal.speak();
}

int main(int argc, char const *argv[])
{
  // 如果不将Animal中的speak 加virtual的话 无法执行猫自己的speak方法
  // 这就是多态
  Animal *animal = new Dog;
  animal->name = "xiaohei";
  doSpeak(*animal);

  // 释放堆区数据 如果不在抽象类中加上虚析构函数 也会警告 报错 即 在Animal中 virtual ~Animal(){}
  // 这样在进行删除的时候 都会执行animal 和dog的析构函数 顺序 先执行dog的 再执行animal的
  delete animal;
  return 0;
}
