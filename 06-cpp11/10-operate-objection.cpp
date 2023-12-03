#include<iostream>
using namespace std;
// 函数可调用对象

void print(int num, string name)
{
  cout << num << "," << name << endl;
}

// 1. 函数指针
using funcptr = void(*)(int, string);

class Test
{
  public:
    string location;
    // 仿函数重载
    void operator()(string name){
      cout << name << endl;
    }

    // 将类对象转换为函数指针
    operator funcptr()
    {
      // return hello; error hello是属于对象的  对象还没创建出来 所以不行
      return world; // 静态方法是属于类的，因此可以
    }

    void hello(int num, string info)
    {
      cout << "hello " << num << "," << info << endl;
    }

    static void world(int num, string info)
    {
      cout << "world " << num << "," << info << endl;
    }
};

int main(int argc, char const *argv[])
{
  // 1 将函数指针赋值
  funcptr f = print;
  f(1, "sofency");

  // 2. 对象仿函数重载
  Test t;
  t("alice");

  // Test test("sasa"); error 这样写是错误的 必须上面写

  // 3. 可转换为函数指针的类对象
  Test tt;
  tt(1, "sasa");

  // 4. 类的函数指针
  funcptr f1 = Test::world;
  f1(1, "alice");

  using func = void(Test::*)(int, string);
  func f2 = &Test::hello;

  // 类的成员指针
  using ptr = string Test::*;
  ptr pp = &Test::location;


  Test tttt; // 创建 Test 类的实例
  (tttt.*f2)(1, "sasasasa"); // 通过成员函数指针调用 hello 函数
  // 使用上述
  tttt.*pp = "sofency";

  cout << tttt.location << endl;

  // 语法 
  // function<返回值类型(函数参数列表)> = 函数指针;
  // 1.包装普通类型
  function<void(int, string)> f3 = print;
  // 2.包装类的静态函数
  function<void(int, string)> f4 = Test::world;
  // 3.包装仿函数
  Test t5;
  function<void(string)> f5 = t5; // 代替的是这个 operator()(string name)
  // 4.包装转换为函数指针的对象
  Test t6;
  function<void(int, string)> f6 = t6; // operator funcptr() 这种类型 调用的还是world函数
  f6(1, "21212");



  return 0;
}
