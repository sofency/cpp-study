#include<iostream>
using namespace std;

class Animal
{
  public:
    Animal(const function<void(int, string)> &f):callback(f){}

    void notify(int id, string name)
    {
      callback(id, name); // 通过调用构造函数得到的函数指针
    }
    private:
      function<void(int, string)> callback;
};

void print(int id, string name)
{
  cout << "id:"<< id << ",name:" << name << endl;
}

int main(int argc, char const *argv[])
{
  Animal animal(print);
  animal.notify(1, "sofency");

  // 参数1 函数名
  // 参数2 是对应的id
  // 参数3 占位符 表示的是从后面的("sofency") 中找第一个参数进行填充
  bind(print, 12, placeholders::_1)("alice");

  // 这样也可以
  auto func = bind(print, 21, placeholders::_1);
  func("hello world");

  auto func1 = bind(print, placeholders::_1, placeholders::_2);
  func1(2, "hello cpp");

  //语法总结
  // auto f = std::bind(类函数/成员地址，类实例对象地址，绑定的参数占位符)
  return 0;
}
