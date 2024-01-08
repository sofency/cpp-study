#include <iostream>
using namespace std;

class Person {
 public:
  int get_age() { return *age; }
  Person(int age) {
    // 在堆区上开辟内存
    this->age = new int(age);
  }

  Person& operator=(Person& p) {
    // 判断当前对象的age是否存在 不存在则创建 存在则从堆区进行删除操作 防止浅拷贝
    if (age != NULL) {
      delete age;
      age = NULL;
    }
    age = new int(*p.age);
    return *this;
  }

  // 关系运算符重载 != > <
  bool operator==(Person& p) {
    // 加上* 比较真实值
    return *p.age == *this->age;
  }

  // 重载函数调用符号 第一个括号不能添加参数
  void operator()(string location) { cout << "location:" << location << endl; }
  // c++ 默认还附带有赋值操作 不过是浅拷贝  浅拷贝有一个问题就是 对象被赋值给多个对象时 底层调用的是一个age
  // 导致在执行析构函数时 报错 因此我们重写对象的赋值操作
  ~Person() {
    if (age != NULL) {
      delete age;
      age = NULL;
    }
  }

 private:
  int* age;
};

int main(int argc, char const* argv[]) {
  Person p1(10);
  Person p2(20);
  Person p3(30);
  bool result = p1 == p2;
  cout << "比较的结果为:" << result << endl;

  p3 = p2 = p1;
  bool result1 = p1 == p2;
  cout << "比较的结果为:" << result1 << endl;

  cout << p3.get_age() << endl;

  // 调用重载的函数调用运算符
  p1("beijing");
  return 0;
}
