#include<iostream>
#include<list> 
using namespace std;

//list的优点 采用动态存储分配，不会造成内存浪费和溢出
// 链表执行插入和删除非常方便，修改指针即可
// 链表灵活 但是指针空间 占用内存 以及查询比较耗时
// push_back(elem) 尾部加入一个元素
// pop_back() 删除容器中最后一个元素
// push_front(elem) 在容器开头插入一个元素
// clear() 移除容器中所有数据
// remove(elem) 删除容器中所有与elem值匹配的元素
// erase(beg,end) 删除[beg, end)区间的数据，返回下一个数据
// erase(pos) 删除pos位置的数据，返回下一个数据的位置
// front() 返回第一个元素
// back() 返回最后一个元素
// 不可以用中括号 at访问元素 不支持随机访问

void test(const list<int> &l)
{
  for(list<int>::const_iterator it = l.begin(); it != l.end(); it++)
  {
    cout << *it << ",";
  }
  cout << endl;
}

int main(int argc, char const *argv[])
{
  list<int> li;
  li.push_back(10);
  li.push_back(11);
  test(li);


  // 创建10个100
  list<int> list1(10, 100); // lists.assign(10,100); lists.assign(li.begin(), li.end())
  test(list1);

  // 插入
  list1.insert(list1.begin(), 130);

  // 删除元素
  list1.remove(10000);

  // 列表元素的翻转
  test(list1);
  // 原地翻转
  list1.reverse();
  test(list1);
  


  return 0;
}
