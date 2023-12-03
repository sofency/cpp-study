#include<iostream>
using namespace std;
#include<algorithm>
#include <random>



// 普通函数
void print(int val)
{
  cout << val << " ";
}
// 仿函数
struct print_info
{
  public:
    void operator()(int val)
    {
      cout << val << " ";
    }
  /* data */
};


int main(int argc, char const *argv[])
{
  vector<int> arrays;
  for (int i = 0; i< 10;i++)
  {
    arrays.push_back(i);
  }

  // 新版乱序为shuffle 旧版已删除 
  default_random_engine e(time(0));   //设置随机种子
  shuffle(arrays.begin(), arrays.end(), e);
  // 打印
  for_each(arrays.begin(), arrays.end(), print);
  cout << endl;
  for_each(arrays.begin(), arrays.end(), print_info());

  cout << endl;
  return 0;
}

