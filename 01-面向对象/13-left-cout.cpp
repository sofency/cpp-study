#include <iostream>
using namespace std;

class Person {
  friend ostream& operator<<(ostream& cout, Person& p);

 public:
  // 这种一般时 p << cout 我们要实现的时cout << p; 所以一般我们在全局重写
  // void operator<<(ostream &cout)
  // {
  // }
  Person(string name, string location) {
    this->name = name;
    this->location = location;
  }

 private:
  string name;
  string location;
};

// 这样可以cout << p 但是如果返回空 则无法后面补充 << endl;
ostream& operator<<(ostream& cout, Person& p) {
  cout << "name:" << p.name << ",location:" << p.location;
  return cout;
}

int main(int argc, char const* argv[]) {
  Person p("sofency", "henan");
  // 这样就可以打印对象中详细的信息了
  cout << p << endl;
  return 0;
}
