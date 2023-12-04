#include<iostream>
#include<list>
using namespace std;

// 右值引用
class Test
{
  public:
    Test():num(new int(100))
    {
      cout << "init construct  location is " << num << endl;
    }
    // 拷贝构造函数
    Test(const Test& a): num(new int(*a.num))
    {
      cout << "copy construct : my name is tom" << endl;
    }

    // 添加移动构造函数
    Test(Test&& a) : num(a.num)
    {
        a.num = nullptr;
        cout << "move construct: my name is sunny" << endl;
    }

    ~Test()
    {
      cout << "析构函数" << endl;
      delete num;
    }

    int *num;
};

// RVC 也被优化了
Test getObj(int num)
{
  Test t ; // 调用后 就析构了
  switch (num)
  {
  case 1:
    t.num = new int(2121);
    break;
  
  default:
    t.num = new int(23);
    break;
  }
  return t;
}

Test getOne()
{
  Test t ;
  return t;
}

// 将亡值
Test&& getOther()
{
  //将亡值赋值为右值引用 进行续命操作
  return Test();
}
template<typename T>
void printValue(T &i)
{
  cout << "left value: " << i << endl;
}

template<typename T>
void printValue(T &&i)
{
  cout << "right value: " << i << endl; 
}

void forward1(int &&k)
{
  // 传进来是一个右值引用 此时右值有了名字 所以printVlaue 接收的是左值引用
  printValue(k);
}

template<typename T>
void testForward(T &&v)
{
  printValue(v);
  printValue(std::move(v));
  printValue(std::forward<T>(v));
}

/**
 * @brief 
 * int num = 10;
 * 左值 num
 * 右值 10
 * 左值引用: int &a = num;  a 是num 的别名
 * 右值引用  int &&b = 10; 这样b就是右值引用
 * 
 * 常量右值引用 const int &&number = 10;
 * 常量左值引用  const int &c = num;
 * const int &d = b; 可以用右值引用个左值引用赋值
 * const int &g = number;
 * 
 * 
 * 左值和右值是独立于他们的类型，都是占用内存的
 * 编译器会讲已命名的右值引用视为左值，将未命名的右值引用视为右值
 * 
 * 
 * 通过右值 推导(T&&或者auto&&)得到的是一个右值引用类型    传入其他函数的话就变成左值引用
 * 通过左值 推导(T&&或者auto&&)得到的是一个左值引用类型    函数内传递的话还是左值引用
 * 
 * const T&& 这个本身就是个右值引用类型，不是未定引用类型
 * 
 * auto &&或者函数参数类型自动推导的T&&是一个未定的引用类型，它需要根据初始化的值类型进行判断是左值还是右值
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char const *argv[])
{
  // c++11 进行了RVC优化 所以原对象num地址和当前t的num地址一样 但是使用getObj(1)这种无法被优化
  Test t = getOne();
  cout << "num:" << *t.num << " location: "<< t.num << endl;
  // 已经被优化了

  int x = 100;
  printValue(x);

  printValue(200);
  forward1(20);

  Test && o = getOther();
  cout << "num:" << o.num << " location: "<< o.num << endl;

  // move 方法可以将左值转换为右值，使用这个函数并不能移动任何东西，而是和移动构造函数一样都具有移动语义，将对象的状态或者所有权从
  // 一个对象转移到另一个对象，只是转移，没有内存拷贝

  // 
  Test && t4 = getOne();
  // Test && t5 = t4; error
  // 通过move 将左值转换为右值
  Test && t5 = std::move(t4);

  list<string> li = list<string> {
    "hello", "wwqwq", "sofency", "alice"
  };
  cout << "===========" << "origin li size " << li.size() << endl;

  // 浅拷贝 只是将所属权交给了lists 移动后原来的就为空了
  list<string> lists  = std::move(li);

  lists.push_back("world");
  auto ret = find(li.begin(), li.end(), "world");
  cout << "没找到:" << (ret == li.end()) << ", li size: " << li.size()<< endl;

  // forward
  // 一个右值引用作为函数参数形参时，在函数内部转发该参数给内部其他函数时，它就变成一个左值，并不是原来的类型，
  // 如果需要按照参数原来的类型转发到另一个函数，它就可以使用c++11提供的std::forward()函数，该函数实现的功能称为完美转发
  // std::forward<T>(t) 
  // 当T为左值引用类型时，t将被转换为T类型的左值
  // 当T不是左值引用类型时，t将被转换为T类型的右值

  int temp = 100;
  // 传入去右值
  testForward(520); // 左 右 右
  testForward(temp); // 左 右 左
  testForward(forward<int>(temp)); // 左 右 右    当T不是左值引用类型时，t将被转换为T类型的右值
  testForward(forward<int&>(temp)); // 左 右 左   当T为左值引用类型时，t将被转换为T类型的左值
  testForward(forward<int&&>(temp)); // 左 右 右  当T不是左值引用类型时，t将被转换为T类型的右值

  return 0;
}
