#include<iostream>
#include<map>
using namespace std;

// 模版设置默认值
template<typename T = long>
auto test(T t, int m) -> decltype(t + m)
{
  return t + m;
}
int myTest(int a, string b)
{
  cout << "a:" << a << ",b:" << b << endl;
  return 0;
}
// 函数定义别名
typedef int (*func)(int, string); // 一般定义
using func1 = int(*)(int, string); // 使用using


template<typename T>
// typedef map<int, T> hash; error
struct MapType
{
  typedef map<int, T> hash;
};
// 如果使用 typedef 只能上述定义

// 还可以 使用using
template<typename T>
using hashMap = map<int, T>;


int main(int argc, char const *argv[])
{
  auto ret = test(1,2);

  cout << ret << endl;

  // myTest就是函数的地址
  func1 fu = myTest;
  // 这样调用
  fu(1, "sofency");

  hashMap<string> Map;
  Map.insert(make_pair(1, "sofency"));
  Map.insert(make_pair(2, "alice"));
  for_each(Map.begin(), Map.end(), [](pair<int, string> p){cout << p.first << ","<< p.second << endl;});

  return 0;
}
