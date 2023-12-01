#include<iostream>
using namespace std;

// 普通函数
int power(int val)
{
  return val * val;
}

// 普通函数
void print(int val)
{
  cout << val << " ";
}

int main(int argc, char const *argv[])
{
  vector<int> arrays;
  for (int i = 0; i< 10;i++)
  {
    arrays.push_back(i);
  }

  vector<int> target;
  target.resize(arrays.size());
  // 源开始位置
  // 源结束为止
  // 目标开始位置
  // 对数据进行的操作
  transform(arrays.begin(), arrays.end(), target.begin(), power);

  for_each(target.begin(), target.end(), print);
  cout << endl;
  return 0;
}
