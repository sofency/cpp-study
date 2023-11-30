// 双端数组 可以对头部进行插入删除操作
// deque和vector区别：
// vector 对于头部的插入删除效率低，数据量较大，效率越低
// deque 相对而言，对头部的插入删除速度比vector快
// vector访问元素时的速度会比deque快

// 数据结构 就是个中继器 存储管理着分类的一段段 连续的内存
#include<iostream>
#include<deque>
using namespace std;


void printDeque(const deque<int> &d)
{
  for(deque<int>::const_iterator it = d.begin(); it != d.end(); it++)
  {
    cout << *it << " ";
  }
  cout << endl;
}

int main(int argc, char const *argv[])
{
  deque<int> queue;
  for(int i = 0; i< 10; i++)
  {
    queue.push_back(i);
  }
  printDeque(queue);


  // 区间拷贝
  deque<int> d1(queue.begin(), queue.end()); //等同于 deque<int> d1; d1.assign(queue.begin(), queue.end())
  printDeque(d1);

  // 复制 10个100的复制
  deque<int> d2(10,100); // 等同于 deque<int> d2; d2.assign(10,100);
  printDeque(d2);

  // 这样 里面地址变化了 说明是深拷贝
  deque<int> d4 = d2;

  // *d2.begin() = 10;
  cout << "d4:" <<  &(*d4.begin()) << ",d2:" << &(*d2.begin())<<  endl;

  // 同理也有resize 修改容量的操作
  // 大小
  cout << d2.size() << endl;
  // 容量 没有容量的限制
  cout << d4.__capacity() << endl;
  // 判空
  cout << d4.empty() << endl;

  // 插入数据  尾删
  d4.push_back(10);
  d4.push_front(60); // 前插

  // 删除一个
  d4.erase(d4.begin()+3);
  // 区间删除
  d4.erase(d4.begin(), d4.begin()+2);

  // 访问
  d4.at(1); // d4[1] d4.front(), d4.back();

  
  // 排序
  sort(d4.begin(), d4.end());
  printDeque(d4);

  return 0;
}
