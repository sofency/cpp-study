#include "circle.h"
#include <math.h>

void Circle::set_point(Point point)
{
  center = point;
}

void Circle::set_length(int num)
{
  length = num;
}

void Circle::detect_distance(Point other)
{
  cout << center.get_x() << ":" << center.get_y() << endl;
  int distance = pow(abs(other.get_x() - center.get_x()), 2) + pow(abs(other.get_y() - center.get_y()), 2);
  distance = sqrt(distance);
  cout << "distance:" << distance << ":" << length << endl;
  string message = distance > length ? "圈外" : (distance == length ? "圈上" : "圈内");
  cout << message << endl;
}