#include<iostream>
#include<set>
using namespace std;

// 所有元素插入时自动被排序 底层属于二叉树
// set    不允许存在重复的元素
// multiset 允许存在相同的元素


void printSet(set<int> &s) {
  for (set<int>::const_iterator start = s.begin(); start != s.end(); start++){
    cout << *start << " ";
  }
  cout << endl;
}

void make_pair_test() {
  // 创建对组
  pair<string, int> p("sofency", 20);
  cout << p.first << "," << p.second << endl;

  // 第二种方式
  pair<string,int> p2 = make_pair("alice", 21);
  cout << p.first << "," << p.second << endl;
}

class MyCompare
{
  public:
  bool operator()(int v1, int v2){
    return v1 > v2;
  }
};

class Person{
  public:
    Person(string name, int age){
      this->name = name;
      this->age = age;
    }
    string name;
    int age;
};

class PersonCompare{

  public:
    bool operator()(const Person &p1, const Person &p2){
      return p1.age > p2.age;
    }
};

void custom_type_set()
{
  set<Person, PersonCompare> s;
  Person p1("sofency", 25);
  Person p2("alice", 23);
  Person p3("sophia", 19);
  Person p4("kenth", 30);

  s.insert(p1);
  s.insert(p2);
  s.insert(p3);
  s.insert(p4);

  for(set<Person, PersonCompare>::iterator p = s.begin(); p != s.end(); p++){
    cout << "name:" << (*p).name << ", age:" << (*p).age << endl;
  }

}

int main(int argc, char const *argv[])
{
  
  set<int> s;
  // 数据的插入只有insert
  s.insert(21);
  s.insert(20);

  // 判断empty
  cout << s.empty() << endl;
  cout << s.size() << endl;

  printSet(s);

  // 拷贝
  set<int> s2(s);
  s2.insert(60);
  // 容器交换
  s2.swap(s);
  // 清空
  // s2.clear();
  // 清除区间 
  // 清除
  s2.erase(s.begin());

  s2.erase(30);
  printSet(s2);
  cout << s.size() << endl;  

  // set容器自定义排序
  set<int, MyCompare> s3;
  s3.insert(32);
  s3.insert(45);

  
  for(set<int, MyCompare>::iterator it = s3.begin(); it != s3.end(); it ++){
    cout << *it  << endl;
  }

  custom_type_set();
  return 0;
}
