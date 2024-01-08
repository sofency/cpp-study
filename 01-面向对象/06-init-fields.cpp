#include <iostream>
using namespace std;
// 初始化列表的形式对参数进行初始话操作
class Phone {
 public:
  string type;
  Phone(string type) {
    // 当行参变量和属性名一样时可以使用this进行区分
    this->type = type;
    cout << "Phone 构造" << endl;
  }
  ~Phone() { cout << "Phone析构" << endl; }
};
class Student {
 public:
  string name;
  int height;
  Phone phone;
  static int score;
  static void func() { cout << "静态方法 在这里面只能操作静态的属性,其他的属性是属于对象私有的" << endl; }

  // 身高加 返回*this 并且用引用&来接收 这样操作的还是本身
  Student& add_height(int size) {
    this->height += size;
    // 就是指向本体
    return *this;
  }

  // 初始化列表的方式进行参数的初始化操作
  Student() : name("init"), height(0), phone("huaawei") { cout << "student init 构造" << endl; };

  Student(string na, int he, string pho) : name(na), height(he), phone(pho) { cout << "student object 构造" << endl; };

  ~Student() { cout << "student 析构" << endl; }
};

// 对象内部定义的静态变量 必须在外部进行初始化操作
// 初始化为100分
// 对于静态的变量 操作是共享的 即类的多个对象的操作 都是操作该值
// c++的静态方法 和和java中的一样
int Student::score = 100;

int main(int argc, char const* argv[]) {
  Student studentA("alice", 198, "apple");
  cout << "name:" << studentA.name << ",height:" << studentA.height << endl;

  // 类本身也可以调用静态方法
  Student::func();
  // 对象也可以调用静态方法
  studentA.func();

  // 空对象是默认只占一个字节
  // static 关键字修饰的 是和类进行关联的
  // 未被static修饰的 是和类创建的对象进行关联的

  studentA.add_height(10).add_height(20);

  cout << "height:" << studentA.height << endl;
  return 0;
}
