#include<iostream>
using namespace std;

class Animal
{
  public:
    Animal(string name)
    {
      this->name = name;
    }

    //这样调用Animal(string name) 进行初始化
    //委托构造
    Animal(string name, int age) : Animal(name)
    {
      this->age = age;
    }

    // 说话
    void speak(string word)
    {
      cout << "animal speak " << word << endl;
    }

  string name;
  int age;
};

// 继承Animal
class Dog: public Animal
{
  public:
    // 子类必须后面写上 :Animal(name, age)
    using Animal::Animal; // 在子类中可以使用父类中的构造函数
    using Animal::speak;
    // Dog(string name, int age):Animal(name, age)
    // {
    //   cout << "dog init" << endl;
    // }

    void speak()
    {
      cout << "dog speak" << endl;
    }
};

class Other
{
  public:
    string name;
};

struct Base
{
  int x;
private:
  int z;
};

struct Son
{
  // 虽然Base不可以初始化 但是Son可以
  Base base;
  int y;
};

struct Test
{
  int a = 5;
};

int main(int argc, char const *argv[])
{
  
  // Animal animal("aluce", 21);
  Animal animal = {"alice", 21}; //也可以这样初始化 因为提供了对应的构造函数 所以也可以进行这样的初始化操作

  // 但是如果Other 中有private的属性，无法像下面这样成功，必须提供构造函数
  Other other = {"sofency"};

  // Test test = {21}; // error 如果聚合对象中的属性已经初始化过，在c++11已经无法再次对他进行初始化操作


  cout << animal.name << "," << animal.age << endl;

  Dog dog("wangwang", 21);
  // 这样可以调用父类的方法

  // 因为子类中也有speak方法，所以如果不在子类中声明父类的speak方法 将无法调用
  dog.speak("hello world");
  dog.speak();

  int array[] = {1,2,3,4,5};

  // {} 设置不对Base初始化操作
  Son son = {{}, 21};
  return 0;
}
