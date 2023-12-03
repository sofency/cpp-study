#include <iostream>
using namespace std;
class Building;
class GoodGay
{
public:
  GoodGay();
  Building *building;
  void visit();
  void visit_private(); // 可以访问私密的卧室 但是要加到友元中
};

class Building
{
  friend void GoodGay::visit_private();

public:
  string setting_room;
  Building() : setting_room("客厅"), bedding_room("卧室"){};

private:
  string bedding_room;
};

// !!!不要类内实现 否则会报错
GoodGay::GoodGay()
{
  building = new Building;
}

void GoodGay::visit()
{
  cout << "访问普通的客厅:" << building->setting_room << endl;
}

void GoodGay::visit_private()
{
  cout << "访问私密的卧室:" << building->bedding_room << endl;
}

int main(int argc, char const *argv[])
{
  GoodGay gay;
  gay.visit_private();
  return 0;
}