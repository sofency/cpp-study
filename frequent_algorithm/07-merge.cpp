#include<iostream>
using namespace std;

// beg1 - end1
// beg2 - end2
// dest 目标容器起始位置 
// merge(iterator beg1, iterator end1, iterator beg2, iterator end2, iterator dest)
// 注意两个容器必须是有序的

void print_info(int val)
{
  cout << val << " ";
}
int main(int argc, char const *argv[])
{
  vector<int> v1;
  vector<int> v2;
  for (int i =0; i< 10; i++)
  {
    v1.push_back(i);
    v2.push_back(i+1);
  }
  vector<int> target;
  // 分配空间
  target.resize(v1.size()+ v2.size());

  
  merge(v1.begin(), v1.end(), v2.begin(), v2.end(), target.begin());
  for_each(target.begin(), target.end(), print_info);
  cout << endl;
  return 0;
}
