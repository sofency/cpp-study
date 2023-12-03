#include<iostream>
using namespace std;

class Test
{
  public:
    Test(initializer_list<string> list)
    {
      for(auto begin = list.begin(); begin != list.end(); begin++)
      {
        names.push_back(*begin);
      }
    }

    vector<string>& get()
    {
      return this->names;
    }

  private:
    vector<string> names;
};
// 列表初始化
int main(int argc, char const *argv[])
{
  Test test({"aos", "alice", "212"});
  // 在原数组上操作
  test.get().push_back("hello wofl");

  for_each(test.get().begin(), test.get().end(), [](string name){cout << name << " ";});
  cout << endl;

  // 这样也可以遍历
  for (auto &it : test.get())
  {
    cout << it << " ";
  }
  cout << endl;
  return 0;
}
