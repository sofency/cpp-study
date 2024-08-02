#include <iostream>
using namespace std;

// 菱形继承
class Animal {
 public:
  int age;
};

class Sheep : virtual public Animal {};
class Tuo : virtual public Animal {};

class SheepTuo : public Sheep, public Tuo {};

int main(int argc, char const* argv[]) {
  SheepTuo sheep;
  // sheep.age; 如果不在Sheep 和Tuo上使用虚继承 则age 会在 Sheep 和Tuo中各保存一份 进而导致子类不知道 该age该使用谁的
  sheep.Sheep::age = 18;
  sheep.Tuo::age = 28;
  // 结果仅有一个 就是上面最后进行赋值操作的
  cout << sheep.age << endl;
  cout << sheep.Sheep::age << endl;

  return 0;
}
