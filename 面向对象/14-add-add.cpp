#include <iostream>
using namespace std;

// 自定义整型的包装类型
class Integer
{
  friend ostream &operator<<(ostream &cout, Integer &integer);

public:
  Integer()
  {
    this->num = 0;
  }

  // 自定义 前置++操作
  Integer &operator++()
  {
    this->num++;
    return *this;
  }

  // 自定义后置++ int 占位使用 无论什么类型都是该值 加上该值 表示后置++
  Integer operator++(int)
  {
    // 值拷贝操作
    Integer temp = *this;
    this->num++;
    return temp;
  }

private:
  int num;
};

ostream &operator<<(ostream &cout, Integer &integer)
{
  // 进行自定义数据类型的左移操作
  cout << integer.num << " ";
  return cout;
}

int main(int argc, char const *argv[])
{
  Integer num;
  cout << ++(++num) << endl;
  cout << num << endl;

  // 貌似还不支持 cout<< num ++ << endl;
  num++;
  cout << num << endl;
  return 0;
}
