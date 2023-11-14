#pragma once
#include <iostream>
#include "point.cpp"
using namespace std;

class Circle
{
  int length;
  Point center;

public:
  // 构造函数 没有返回值 创建对象的时候，会调用 且只调用一次；
  Circle()
  {
    cout << "构造函数" << endl;
  }
  // 析构函数 对象销毁前会执行该函数
  ~Circle()
  {
    cout << "析构函数" << endl;
  }

public:
  void set_point(Point point);
  void set_length(int length);
  void detect_distance(Point other);
};