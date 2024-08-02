#include <iostream>
using namespace std;
#include <numeric>

int main(int argc, char const* argv[]) {
  vector<int> container = {1, 2, 3, 4, 5, 6, 6};
  vector<int> container1 = {1, 2, 3, 4, 5, 6, 7};

  // 容器数据交换
  swap(container, container1);
  for_each(container.begin(), container.end(), [](int val) { cout << val << " "; });
  cout << endl;

  for_each(container1.begin(), container1.end(), [](int val) { cout << val << " "; });
  cout << endl;

  // accumulate 累加操作 在numeric中
  int total = accumulate(container.begin(), container.end(), 0);
  cout << "容器所有值结果为" << total << endl;

  vector<int> v;
  v.resize(10);
  // 填充初始值
  fill(v.begin(), v.end(), 100);
  for_each(v.begin(), v.end(), [](int val) { cout << val << " "; });
  cout << endl;

  return 0;
}
