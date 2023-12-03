#include<iostream>
using namespace std;

int main(int argc, char const *argv[])
{
  string name = "sofency";
  string location;
  // 第二个参数是char类型
  // 操作的是自身
  location.assign(10,'w');
  cout << location << endl;

  name += " world";
  // 从哪个位置开始 切多少个字符
  string sub = name.substr(2, 9);
  cout << sub << endl;
  // append 追加从目标字符串的1位置开始的4个字符串 tuen
  sub.append("student", 1, 4);
  cout << sub << ", " << name << endl;


  // 查找字符串 找到返回索引 找不到返回-1
  int pos = name.find("wor"); //从左往右查找
  int rpos = name.rfind("wor"); // 从右往前查找
  cout << "查找的位置是" << pos << endl;

  // 替换从0到2的字符串为alice
  name.replace(0,2, "alice");
  cout << name << endl;

  string str1 = "alice";
  string str2 = "sofnecy";
  // 比较两个字符串是否相等 == 0 表示相等
  cout << str1.compare(str2) << endl;

  // 对单个字符进行修改
  str1.at(0) = 'c';
  str2[0] = 'W';
  cout << str1 << ":" << str2 << endl;

  string email = "sofency@qq.com";
  pos = email.find('@');
  string username = email.substr(0, pos);
  string info = email.substr(pos + 1, email.length());
  cout << username << "," << info << endl;
  return 0;
}
