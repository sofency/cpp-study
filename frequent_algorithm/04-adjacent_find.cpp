#include<iostream>
using namespace std;

int main(int argc, char const *argv[])
{
  vector<int> list;
  list.push_back(0);
  list.push_back(2);
  list.push_back(0);
  list.push_back(0);
  list.push_back(3);
  list.push_back(1);
  list.push_back(4);
  list.push_back(3);
  list.push_back(3);
  list.push_back(2);
  list.push_back(2);


  // 找到相邻重复的元素 返回第一个重复元素的索引
  vector<int>::iterator pos = adjacent_find(list.begin(), list.end());
  for(;pos!=list.end(); pos++)
  {
    cout << " 数据找到" << *pos << endl;
  }
  

  return 0;
}
