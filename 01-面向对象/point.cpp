#include "point.h"

// point::进行设置 不要让参数名和属性名一样
void Point::set_x(int num)
{
  x = num;
}

void Point::set_y(int num)
{
  y = num;
}

int Point::get_x()
{
  return x;
}
int Point::get_y()
{
  return y;
}