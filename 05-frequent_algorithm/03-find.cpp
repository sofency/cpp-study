#include<iostream>
using namespace std;
#include<vector>

class Person
{
  friend ostream &operator<<(ostream &cout, Person &p);
  public:
    Person(string name, int age)
    {
      this->name = name;
      this->age = age;
    }
    string name;
    int age;

    // 如果要进行判断是否相等 需要重写
    bool operator==(const Person &p)
    {
      return this->name == p.name && this->age == p.age;
    }
};

ostream &operator<<(ostream &cout, Person &per)
{
  // 进行自定义数据类型的左移操作
  cout << "name:"<< per.name << ",age:" << per.age << " ";
  return cout;
}

template<typename T>
void find_vec(typename vector<T>::iterator &iter, const vector<T> &vec)
{
  if (iter != vec.end()) {
    cout << " 数据找到" << *iter << endl;
  } else {
    cout << "数据未找到" << endl;
  }
}
class Greater
{
  public:
    bool operator()(int val)
    {
      return val > 5;
    }
};


int main(int argc, char const *argv[])
{
  
  vector<int> arrays;
  for (int i = 0; i< 10;i++)
  {
    arrays.push_back(i);
  }

  vector<int>::iterator iter = find(arrays.begin(), arrays.end(), 8);
  find_vec<int>(iter, arrays);

  // 第三个参数必须是仿函数
  vector<int>::iterator itera = find_if(arrays.begin(), arrays.end(), Greater());
  find_vec<int>(itera, arrays);


  vector<Person> persons;
  Person per1("alice",21);
  Person per2("sofency",212);
  Person per3("oo",12);
  Person per4("optimistic",45);
  persons.push_back(per1);
  persons.push_back(per2);
  persons.push_back(per3);
  persons.push_back(per4);
  
  // 传参类型 起始位置 结束位置 要找到的函数 
  // 对于自定义数据类型要重写==操作符 因为底层不知道是如何比较的
  vector<Person>::iterator result = find(persons.begin(), persons.end(), per2);
  find_vec<Person>(result, persons);
  return 0;
}
