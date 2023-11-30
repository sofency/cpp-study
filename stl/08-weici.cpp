#include<iostream>
using namespace std;

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
  sort(vec.begin(), vec.end(), Compare());
  for(vector<int>::iterator temp = vec.begin(); temp!=vec.end(); temp++)
  {
    cout << *temp << " ";
  }
  cout << endl;
  return 0;
}
