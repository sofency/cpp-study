#include <iostream>
#include <string>
using namespace std;
// 通用格式开头

// 定义常量 使用#define 或 变量前使用const 修饰
#define MAX 5

// 数据类型 short:2 int:4 long:8
// 在 C++ 中，int 和 long 类型的变量占用字节数取决于具体的编译器和平台。
// 通常int 4 long为4或8
// long long 8

// float:4:7 四个字节 7位有效数字
// double:8:(15-16) 8个字节 15-16位有效数字

// 运算符 + - * / % ++ -- += -= /+ %= 前置和后置 ++a 先进行加1 再进行运算
// 比较运算符 == !=  > < >= <=
// 逻辑运算符 !(非) && (与) || (或)

void type_size()
{
  cout << "int:" << sizeof(int) << endl;
  cout << "long:" << sizeof(long) << endl;

  cout << "long long:" << sizeof(long long) << endl;
  cout << "short:" << sizeof(short) << endl;

  cout << "float:" << sizeof(float) << endl;

  cout << "double:" << sizeof(double) << endl;

  // 只是将ascii编码进行存储 a-97 A-65
  cout << "char:" << sizeof(char) << endl;
  // 1真 0加
  cout << "bool:" << sizeof(bool) << endl;
}

// 科学计数法
void science_show()
{
  // 科学计数法 3 * 10 ^ 3
  float number = 3e3;
  cout << number << endl;
}

// 常见的转义字符
void change_character()
{
  cout << "\\n 换行" << endl;
  cout << "\\t 水平制表符" << endl;

  // C风格字符串
  char name[] = "sofency";
  cout << name << endl;

  // C++风格字符串 必须导入 include<string>
  string blog = "hello world";
  cout << blog << endl;
}

// 数据的输入
void input()
{
  // bool 非0都是真
  int number;
  cout << "请输入整型" << endl;
  cin >> number;
  cout << "结果为" << number << endl;

  string information;
  cout << "请输入字符串信息" << endl;
  cin >> information;
  cout << "结果为" << information << endl;
}

// 选择结构
// if(){}else if() {} else{}
void choose()
{
  int score;
  cout << "请输入分数" << endl;
  cin >> score;

  // switch语法
  switch (score)
  {
  case 600 ... 700:
    cout << "985录取" << endl;
    break;
  case 550 ... 599:
    cout << "录取211" << endl;
    break;
  default:
    cout << "再来一年" << endl;
    break;
  }
}
// 循环条件
void circulate()
{
  // while(expression) {}
  // for () {}
  for (int i = 0; i < 3; i++)
  {
    cout << "current:" << i << endl;
  }
}

// 练习题
void practice(int first, int second, int third)
{
  int result = first > second ? (first > third ? first : second) : (second > third ? second : third);
  cout << "最大值为: " << result << endl;
}

// 猜数字
void guess()
{
  // 设置随机数种子
  // 版本低需要 include<ctime>
  // do {}while(expression)
  srand((unsigned int)time(NULL));
  int number = rand() % 100;
  int guess_number;
  while (true)
  {
    cout << "请输入你猜的数字" << endl;
    cin >> guess_number;
    if (guess_number > number)
    {
      cout << "你猜的数字大了" << endl;
    }
    else if (guess_number < number)
    {
      cout << "你猜的数字小了" << endl;
    }
    else
    {
      cout << "恭喜你猜对了" << endl;
      break;
    }
  }
}

int flower_number(int number)
{
  // 赋值给它 是值传递 不是引用传递
  int origin = number;
  int sum = 0;
  while (origin != 0)
  {
    int temp = origin % 10;
    sum += temp * temp * temp;
    origin = origin / 10;
  }
  return sum == number;
}

// 找到水仙花数
void find_flower_number()
{
  int start = 100;
  do
  {
    if (flower_number(start) == 1)
    {
      cout << start << endl;
    }
    start++;
  } while (start < 1000);
}

// 找出含七 或者7的倍数的数字
bool detect(int num)
{
  // 能被7整除
  if (num % 7 == 0)
    return true;
  int temp = num;
  while (temp != 0)
  {
    int number = temp % 10;
    if (number == 7)
    {
      return true;
    }
    temp = temp / 10;
  }
  return false;
}
void find_seven()
{
  for (int i = 1; i < 100; i++)
  {
    if (detect(i))
    {
      cout << i << endl;
    }
  }
}
// 打印乘法表
// continue break
void print_multiple()
{
  for (int i = 1; i < 10; i++)
  {
    for (int j = 1; j <= i; j++)
    {
      // cout << j << "*" << i << "=" << i * j << "\t" << ends;
      cout << j << "*" << i << "=" << i * j << "\t";
    }
    cout << endl;
  }
}
int main(int argc, char const *argv[])
{
  // 定义变量
  int height = 20;
  // 不可修改
  const int age = 30;
  cout << "hello world:" << height << ",常量:" << MAX << endl;
  print_multiple();
  return 0;
}
