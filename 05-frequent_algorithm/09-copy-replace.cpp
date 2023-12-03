#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
  vector<int> list = {1, 2, 3, 4, 5, 6};
  vector<int> target;
  target.resize(list.size());

  copy(list.begin(), list.end(), target.begin());
  for_each(target.begin(), target.end(), [](int val){ cout << val << " "; });

  cout << endl;

  // replace 所有等于3的就替换
  replace(list.begin(), list.end(), 3, 3000);
  for_each(list.begin(), list.end(), [](int val) { cout << val << " "; });
  cout << endl;

  // 大于4的替换为3000
  replace_if(list.begin(), list.end(), [](int val){ return val > 4; }, 2000);

  for_each(list.begin(), list.end(), [](int val) { cout << val << " "; });
  cout << endl;

  return 0;
}
