#include <iostream>
using namespace std;
#define PI 3.1415
// struct 和 class 的区别则是 struct 默认权限是公共的 public　class 默认权限是private
// public
// protected 类内可以访问，类外不可以访问 儿子可以访问
// private  类内可以访问 类外不可以访问 儿子也不可访问
class Circle {
  // 不写修饰类型 默认是私有的
  string info;

 public:
  // 半径
  int radius;
  // 行为
  double length() { return 2 * PI * radius; };
  double area() { return PI * radius * radius; }
};

int main(int argc, char const* argv[]) {
  // 实例化对象
  Circle circle;
  circle.radius = 10;
  cout << "周长:" << circle.length() << endl;
  cout << "面积:" << circle.area() << endl;

  return 0;
}
