#include<iostream>
using namespace std;
#include<algorithm>

// 运算符重载参数有一个称为一元谓词，两个成为二元谓词
struct GreaterFive
{
  public:
    bool operator()(int val){
      return val > 5;
    }
};

class Compare
{
  public:
    bool operator()(int val, int val2){
      return val > val2;
    }
};

int main(int argc, char const *argv[])
{
  vector<int> vec;
  for(int i = 0; i < 7;i++) {
    vec.push_back(i);
  }

  vector<int>::iterator iter = find_if(vec.begin(), vec.end(), GreaterFive());
  if(iter == vec.end()){
    cout << "未找到" << endl;
  }else{
    cout << *iter << endl;
  }

  // sort(vec.begin(), vec.end(), Compare());
  // 或者使用内嵌的仿函数
  sort(vec.begin(), vec.end(), greater<int>());

  for(vector<int>::iterator temp = vec.begin(); temp!=vec.end(); temp++)
  {
    cout << *temp << " ";
  }
  cout << endl;

  vector<bool> result;
  result.push_back(true);
  result.push_back(false);
  result.push_back(true);

  // 利用逻辑非 将容器result搬运到result2中，并执行取反操作
  vector<bool> result2;
  result2.resize(result.size());
  // 将result的begin-end之间的数据取反操作 赋值给 从result2开始的值
  transform(result.begin(), result.end(), result2.begin(), logical_not<bool>());
  for(vector<bool>::iterator tem = result2.begin(); tem!=result2.end(); tem++)
  {
    cout << *tem << " ";
  }
  cout << endl;

  return 0;
}
