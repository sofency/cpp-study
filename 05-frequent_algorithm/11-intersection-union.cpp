#include<iostream>
using namespace std;

// 交并差的操作
int main(int argc, char const *argv[])
{
  vector<int> list1 = {1,2,3,4,5,6,7,8,9,10};
  vector<int> list2 = {2,3,6,8,9,10,11,12};
  vector<int> intersection_target;
  // 
  intersection_target.resize(min(list1.size(), list2.size()));

  // 交集 返回的是end的迭代器 
  cout << "交集结果" << endl;
  vector<int>::iterator end = set_intersection(list1.begin(), list1.end(), list2.begin(), list2.end(), intersection_target.begin());
  for_each(intersection_target.begin(), end, [](int val){cout << val << " ";});
  cout << endl;

  // 并集
  vector<int> union_target;
  union_target.resize(list1.size() + list2.size());

  // 返回的是最后一个并集的位置
  cout << "并集结果" << endl;
  vector<int>::iterator union_end = set_union(list1.begin(), list1.end(), list2.begin(), list2.end(), union_target.begin());
  for_each(union_target.begin(), union_end, [](int val){cout << val << " ";});
  cout << endl;

  // 差集
  vector<int> difference_target;
  difference_target.resize(list1.size() + list2.size());

  // 返回的是最后一个并集的位置
  // 差集要看谁对谁的差集
  // 那个区间在前面就是谁的差集 下面就是输入 list1的差集 = list - (list1 交集 list2)
  cout << "差集结果" << endl;
  vector<int>::iterator difference_end = set_difference(list1.begin(), list1.end(), list2.begin(), list2.end(), difference_target.begin());
  for_each(difference_target.begin(), difference_end, [](int val){cout << val << " ";});
  cout << endl;

  return 0;
}
