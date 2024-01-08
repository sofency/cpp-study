#include <iostream>
using namespace std;

// 对象的创建最后必须加;
// 创建一个类 cpp 会默认给每个类加上至少三个函数
// 默认构造 // 创建默认对象时执行
// 析构函数 //对对象销毁时执行
// 拷贝函数 // 属性拷贝
class Person {
 public:
  int age;
  string name;
  int* height;
  Person() {
    // 初始化
    height = new int(0);
  }
  // 提供了有参/拷贝构造函数 编译器则不再提供无参构造
  Person(int num, string var, int h) {
    age = num;
    name = var;
    // height存储在堆区
    height = new int(h);
  }
  // 构造拷贝 编译器默认会提供
  // 默认的拷贝 是浅拷贝 因此我们需要深拷贝 否则在析构函数释放堆区内存会报错
  // 当函数中调用多次类创建对象时 ，析构函数的执行是按照栈的方式进行执行的
  Person(const Person& p) {
    age = p.age;
    name = p.name;
    // 默认的是 height = p.height;
    height = new int(*p.height);
  }

  // 析构函数
  // 一般对象中有属性在堆区申请内存 都要进行深拷贝 且在析构函数中要进行释放
  ~Person() {
    cout << "current name:" << name << endl;
    if (height != NULL) {
      delete height;
      height = NULL;
    }
  }
};

Person do_work() {
  Person p5;
  cout << "inner:" << &p5 << endl;
  return p5;
}

void test() {
  Person p4 = do_work();
  cout << "outer:" << &p4 << endl;
}
int main(int argc, char const* argv[]) {
  // 调用的是无参的
  Person p;
  cout << "top:" << &p << endl;
  // 调用的是有参的
  Person p1(10, "有参", 90);

  // 将匿名的赋值给当前对象p2
  Person p2 = Person(10, "匿名", 100);

  // 构造拷贝
  Person p3 = Person(p2);

  // 匿名拷贝 仅有一个参数可以
  // Person p4 = (12, "元组的形式初始化"); error

  cout << "current p1" << p1.name << endl;
  cout << "current p2" << p2.name << endl;
  cout << "current p3" << p3.name << endl;
  // cout << "current p4" << p4.name << endl;

  test();
  return 0;
}
