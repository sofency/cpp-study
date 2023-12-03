#include<iostream>
using namespace std;

// final 用来修饰的方法 表示子类不可以进行修改
class Base
{
  public:
    virtual void test() = 0;
};

class Son :public Base
{
  public:
    // final修饰表示son的子类不可以修改
    // override 重写父类的函数
    void test() final override
    {
      cout << "test son" << endl;
    }
};

int main(int argc, char const *argv[])
{
  Son son;
  son.test();
  return 0;
}
