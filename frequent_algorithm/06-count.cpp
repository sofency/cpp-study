#include<iostream>
using namespace std;
class Person
{
  friend ostream &operator<<(ostream &cout, Person &per);

  public:
    Person(string name, int age)
    {
      this->name = name;
      this->age = age;
    }
    string name;
    int age;

    bool operator==(const Person &p)
    {
      return p.age == this->age;
    }
};

class Compare
{
  public:
     bool operator()(const Person &p1, const Person &p2){
      return p1.age < p2.age;
    }
};

ostream &operator<<(ostream &cout, Person &per)
{
  // 进行自定义数据类型的左移操作
  cout << "name:"<< per.name << ",age:" << per.age << " ";
  return cout;
}

int main(int argc, char const *argv[])
{
  vector<Person> persons;
  Person per1("alice",21);
  Person per2("sofency",212);
  Person per3("oo",21);
  Person per4("optimistic",45);
  persons.push_back(per1);
  persons.push_back(per2);
  persons.push_back(per3);
  persons.push_back(per4);
  
  // 统计下年龄相同的人数
  int num = count(persons.begin(), persons.end(), per1);
  cout << "年龄相同的人数" << num << endl;

  // 第三个参数可以不填 按照自己对象中指定的规则进行排序
  // 自定义对象比如设置谓词
  sort(persons.begin(), persons.end(), Compare());

  for(vector<Person>::iterator pos = persons.begin();pos!=persons.end(); pos++)
  {
    cout << *pos << endl;
  }

  return 0;
}
