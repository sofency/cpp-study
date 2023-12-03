#include<iostream>
using namespace std;

int main(int argc, char const *argv[])
{
  vector<int> list;
  for(int i = 0; i < 10; i++)
  {
    list.push_back(i);
  }
  // 查找容器中是否有9的元素
  // 只针对有序序列
  bool ret = binary_search(list.begin(), list.end(), 8);
  if (ret) {
    cout <<  "容器中有9" << endl;
  }
  return 0;
}
