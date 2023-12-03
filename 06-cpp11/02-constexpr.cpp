#include<iostream>
using namespace std;

// constexpr用于修饰常量表达式，使得该表达式的值在编译阶段就能计算出来。返回值也是常量
// 使用constexpr关键字修饰的变量或函数，必须在声明时就提供一个常量表达式作为初始值，且在程序运行期间不能修改。

constexpr int operate(int a, int b)
{
  return a * a + b;
}

class Rectangle
{
  int _h, _w;
  public:
    // 修饰一个类时 函数体必须为空 不能在里面进行赋值
    constexpr Rectangle(int h, int w):_h(h),_w(w){}
    // 修饰一个函数 _h,_w为全局，并且在实例化后就已经是初始化后的常量了
    // 加上const 是为了防止函数修改对象的状态即两个属性 _h,_w
    // 不加const也行 就会报warning
    // 常量表达式函数体里面不允许有其他非常量表达式之外的语句
    // 例如 for (int i =0; i< 10; i++){ cout << i << endl;} 这样的操作在函数里面是不允许的 因为i是变量
    constexpr int get_area() const {return _h * _w;}
};

int main(int argc, char const *argv[])
{
  // 
  constexpr int version = operate(2, 3);

  const int ver = 5;

  // 对象在编译器就已经初始化了
  constexpr Rectangle angle(4, 5);
  cout << angle.get_area() << endl;
  return 0;
}
