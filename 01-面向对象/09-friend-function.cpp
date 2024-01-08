#include <iostream>
using namespace std;

class House {
  // friend 函数表示 该函数可以访问到私有的变量
  friend void good_gay(House* house);

 public:
  House() {
    sitting_room = "客厅";
    bedding_room = "卧室";
  }
  string sitting_room;

 private:
  string bedding_room;
};

// 全局函数
void good_gay(House* house) {
  cout << "好基友进入 " << house->sitting_room << endl;
  // 如果不将全局函数设置为House属性的友元的话 就不可访问
  cout << "好基友进入 " << house->bedding_room << endl;
}
int main(int argc, char const* argv[]) {
  House house;
  good_gay(&house);
  return 0;
}
