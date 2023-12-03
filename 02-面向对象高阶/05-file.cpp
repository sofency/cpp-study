#include <iostream>
#include <fstream>
using namespace std;

void write()
{
  // 创建流对象
  // ofstream 是写操作
  // ifstream 是读操作
  // fstream 读写操作
  ofstream ofs;
  // ios::out是向流里面写数据
  // ios::in 为读文件 打开文件
  // ios::ate 初始位置，文件尾
  // ios::app 追加方式写文件
  // ios::trunc 如果文件存在，先删除再创建
  // ios::binary 二进制方式
  ofs.open("text.txt", ios::out);

  ofs << "姓名:sofency" << endl;

  ofs.close();
}
void read()
{
  ifstream ifs;
  ifs.open("text.txt", ios::in);
  if (!ifs.is_open())
  {
    cout << "文件打开失败" << endl;
    return;
  }
  // 读文件形式 4种
  // 1. 设置缓冲区
  // char buff[1024] = {0};
  // while (ifs >> buff)
  // {
  //   cout << buff << endl;
  // }

  // 2. 获取一行
  // char buff[1024] = {0};
  // // 第一个参数是存储的位置 第二个参数是空间大小
  // while (ifs.getline(buff, sizeof(buff)))
  // {
  //   cout << buff << endl;
  // }

  // 3. getline 使用string
  string buff;
  // 第一个参数是存储的位置 第二个参数是空间大小
  while (getline(ifs, buff))
  {
    cout << buff << endl;
  }

  // 第四种 一个字符一个字符读 不推荐使用
  // char temp;
  // while ((temp = ifs.get()) != EOF)
  // {
  //   cout << temp;
  // }
  ifs.close();
}
class Person
{
public:
  string name;
  int age;
};

// 写二进制
void write_binary()
{
  ofstream ofs;

  ofs.open("person.bin", ios::binary | ios::out);
  Person person = {"sofnecy", 21};
  // 强转位const char *, 还要传入对象的大小
  ofs.write((const char *)&person, sizeof(person));

  ofs.close();
}

// 读二进制文件
void read_binary()
{
  ifstream ifs;
  ifs.open("person.bin", ios::in | ios::binary);

  if (!ifs.is_open())
  {
    cout << "文件打开失败" << endl;
    return;
  }

  Person person;
  ifs.read((char *)&person, sizeof(Person));
  cout << "name:" << person.name << ","
       << "age=" << person.age << endl;

  ifs.close();
}
int main()
{
  read_binary();
  return 0;
}
