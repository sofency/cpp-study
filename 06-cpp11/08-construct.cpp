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

int main(int argc, char const *argv[])
{
  
  Animal animal("aluce", 21);
  cout << animal.name << "," << animal.age << endl;

  Dog dog("wangwang", 21);
  // 这样可以调用父类的方法

  // 因为子类中也有speak方法，所以如果不在子类中声明父类的speak方法 将无法调用
  dog.speak("hello world");
  dog.speak();
  return 0;
}
