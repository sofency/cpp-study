#include<iostream>
#include<map>
using namespace std;

// class MyCompare
// {
//   public:
//   bool operator()(pair<string, int> v1, pair<string,int> v2){
//     return v1.second > v2.second;
//   }
// };

bool compare(pair<string, int> &v1, pair<string,int> &v2){
    return v1.second > v2.second;
}
int main(int argc, char const *argv[])
{
  // 同理multimap 可以存放重复的key map 不可以
  // 也可以指定自定义的仿函数 默认的仿函数排序时根据key的
  map<string, int> container;
  container.insert(pair<string, int>("sofencu", 21));
  container.insert(pair<string, int>("alice", 29));
  container.insert(pair<string, int>("sasa", 12));
  // 对于重复的key c++不会覆盖对应的value
  container.insert(pair<string, int>("sasa", 21));

  container.insert(pair<string, int>("ee", 1));

  for (map<string, int>::iterator current = container.begin(); current != container.end(); current ++)
  {
    cout << "name:" << (*current).first << ",age:" << (*current).second << endl;
  }
  cout << container.empty() << "," << container.size() << endl;

  // 按照key进行删除
  container.erase("ee");

  map<string,int>::iterator m = container.find("sasa");
  // 查找成功返回对应键值对 查找不成功返回对应的end()
  if (m != container.end())
  {
    cout << "查找成功" << (*m).second << endl;
  }else{
    cout << "查找失败" << endl;
  }
  // 对于multimap 可以使用count(key)查询相同key的个数
  

  vector<pair<string, int> > result(container.begin(), container.end());

  sort(result.begin(), result.end(), compare);

  cout << "排序后"<< endl;
  for (vector<pair<string, int> >::iterator temp = result.begin(); temp != result.end(); temp ++) 
  {
    cout << "name:" << (*temp).first << ",age:" << (*temp).second << endl;
  }

  return 0;
}
