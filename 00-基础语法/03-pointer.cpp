#include <iostream>
using namespace std;

struct student {
  string name;
  int age;
  int score;
} stu;

void test_array() {
  int array[] = {1, 2, 3, 4, 5, 6, 7};
  // array 就是数组的首地址
  int* p = array;
  for (int i = 0; i < sizeof(array) / sizeof(int); i++) {
    cout << *p << " ";
    p++;
  }
  cout << endl;
}

void type() {
  int a = 10;
  int b = 20;
  // 常量指针 const修饰的是指针 指针指向可以修改，但是指针指向的值不可以修改
  const int* p = &a;
  p = &b;  // 正确
  // *p = 20; // 错误
  // 指针常量 const 修饰的是常量，指针不可以修改，但是指针指向的值可以修改
  int* const y = &a;
  // y = &b;
  *y = 20;

  // 既修饰常量 也修饰指针  都不可以改变
  const int* const two = &a;
  // y = &b;
  //*y = 20;
}

void operate_struct(struct student* stu) {
  // 传进来的指针可以使用->
  stu->name = "alice";
  (*stu).score = 200;
  (*stu).age = 29;
}
void un_change_student(const struct student* s) {
  // 加了const 可以防止进行修改操作
}
int main(int argc, char const* argv[]) {
  // c++中在声明变量时struct可以省略
  struct student s1 = {"sofency", 21, 98};
  cout << "name:" << s1.name << endl;
  // stu 给结构体起的别名
  stu.name = "alice";
  cout << "name:" << stu.name << endl;

  struct student students[3] = {
      {"alice", 21, 98},
      {"sofency", 87, 98},
      {"alice", 21, 90},
  };

  // 结构体指针
  struct student* s = &s1;
  operate_struct(&s1);
  cout << "name:" << s1.name << " age:" << s1.age << " score:" << s1.score << endl;
  return 0;
}
