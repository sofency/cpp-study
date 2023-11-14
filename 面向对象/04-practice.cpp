#include "circle.cpp"

void test()
{
  // 局部变量中 存储在栈区 这样可以观察到即执行构造函数也执行了析构函数
  Circle circle;
}
int main(int argc, char const *argv[])
{
  test();
  Circle circle;
  circle.set_length(5);
  Point radius;
  radius.set_x(0);
  radius.set_y(0);
  circle.set_point(radius);

  Point other;
  other.set_x(3);
  other.set_y(4);
  circle.detect_distance(other);
  return 0;
}
