#include <iostream>
using namespace std;

class Building
{
  friend class GoodGay;

public:
  string setting_room;

private:
  string bedding_room;

public:
  Building() : setting_room("客厅"), bedding_room("卧室") {}
};

// 好基友
class GoodGay
{
public:
  void visit();
  // 指针要指向创建的对象
  Building *building;
  GoodGay()
  {
    building = new Building();
  }
};

// 类外实现
void GoodGay::visit()
{
  cout << "好基友进入 " << building->setting_room << endl;
  cout << "好基友进入 " << building->bedding_room << endl;
}

int main(int argc, char const *argv[])
{

  GoodGay gay;
  gay.visit();
  return 0;
}
