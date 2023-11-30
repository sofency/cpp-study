#include <iostream>
// c++17 貌似不用引用了
#include <algorithm>
using namespace std;

void print_info(int val)
{
  cout << val << ",";
}

void inner_list()
{
  // > > 需要空开
  vector<vector<int> > v;
  vector<int> inner_v;

  inner_v.push_back(2);
  inner_v.push_back(5);
  v.push_back(inner_v);

  vector<int> inner_v_1;

  inner_v_1.push_back(2);
  inner_v_1.push_back(5);
  v.push_back(inner_v_1);

  for (vector<vector<int> >::iterator start = v.begin(); start != v.end(); start++)
  {
    for (vector<int>::iterator start_inner = (*start).begin(); start_inner != (*start).end(); start_inner++)
    {
      cout << *start_inner << ",";
    }
    cout << endl;
  }
}

// 收缩内存
void test()
{

  vector<int> array;
  //预留空间 如果提前知道我们的数据量为多少的话 这样可以避免扩容 来回复制的次数
  array.reserve(10000);

  for(int i = 0; i< 10000; i++)
  {
    array.push_back(i);
  }
  cout<< "容量:" << array.capacity() << ",大小:" << array.size() << endl;

  // 重新制定大小 只是将大小变为3 容量没有变化
  array.resize(3);
  cout<< "容量:" << array.capacity() << ",大小:" << array.size() << endl;

  // 巧用swap收缩内存
  vector<int>(array).swap(array); // 匿名对象
  cout<< "容量:" << array.capacity() << ",大小:" << array.size() << endl;

}

int main(int argc, char const *argv[])
{
  vector<int> v;
  // 向vector 中插入数据
  for (int i = 0; i < 10; i++)
  {
    v.push_back(i);
  }
  // 获取容器的起始指针
  vector<int>::iterator start = v.begin();
  // 1. 使用while进行遍历
  while (start != v.end())
  {
    cout << *start << ",";
    start++;
  }
  cout << endl;

  // 2. 使用stl提供的for_each进行遍历
  for_each(v.begin(), v.end(), print_info);
  cout << "" << endl;

  inner_list();

  // 这样是创建10个20在数组中
  vector<int> vec(10,20); // 等价于 vec.assign(10, 20)  10个20赋值
  for_each(vec.begin(), vec.end(), print_info);
  cout << "" << endl;
  vector<int> v3;
  // 赋值操作 将vec begin 到end 区间内的数据拷贝给v3
  v3.assign(vec.begin(), vec.end());
  for_each(v3.begin(), v3.end(), print_info);
  cout << "" << endl;

  // 判断是否为空
  cout << v3.empty() << endl;
  // 容量
  cout << v3.capacity() << endl;
  // 大小 
  cout << v3.size() << endl;
  // 重新制定大小 长了的空间用0填充 默认0填充
  v3.resize(15, 0);

  // 访问元素
  cout << v3.at(3) << "或者" << v3[3] << endl;
  cout << "第一个元素"<< v3.front() << endl;
  cout << "最后一个元素" << v3.back() << endl;



  // 插入 在开始查个100 必须传入迭代器
  v3.insert(v3.begin(), 100);
  for_each(v3.begin(), v3.end(), print_info);
  cout << "" << endl;

  // 删除 提供迭代器
  v3.erase(v3.begin());
  for_each(v3.begin(), v3.end(), print_info);
  cout << "" << endl;

  // 删除 提供区间迭代器 删除前5个元素
  v3.erase(v3.begin(), v3.begin()+5);
  for_each(v3.begin(), v3.end(), print_info);
  cout << "" << endl;
  // 清空
  v3.clear();

  // 访问元素
  cout << v3[1] << endl;
  return 0;
}
