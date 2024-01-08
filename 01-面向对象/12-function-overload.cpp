#include <iostream>
using namespace std;
class HomeWork {
 public:
  int height;  // 作业厚度
  // cpp 内部的操作符进行重载
  HomeWork(int height) { this->height = height; }
  // operator-  // operator% 等等
  HomeWork operator+(HomeWork other) {
    HomeWork temp(0);
    temp.height = this->height + other.height;
    return temp;
  }
};

// 全局函数重载
HomeWork operator+(HomeWork work, int height) {
  HomeWork temp(0);
  temp.height = temp.height + work.height + height;
  return temp;
}
// 函数重载
int main(int argc, char const* argv[]) {
  HomeWork one(10);
  HomeWork two(20);
  HomeWork result = one + two;
  cout << "作业厚度:" << result.height << endl;

  // 将operator省略
  HomeWork work = one + 40;
  cout << "作业厚度:" << work.height << endl;

  return 0;
}
