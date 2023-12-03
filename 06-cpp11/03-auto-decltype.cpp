#include<iostream>
#include<map>
using namespace std;

// 1. auto 自动类型推导 类似于java 高版本的var
// 2. auto 不能作为函数的形参函数修饰 因为函数未被调用，无法知道具体的类型
// 3. auto 不能用在类的非静态成员中，因为之后类初始化创建对象时 才知道具体的类型
//              class Test { 
//                   auto name = "str"; //error
//                   static auto num = 21; //ok
//              }
// 4. auto不能用于修饰数组  
//          auto arr[] = {1,2,3,4} //error
//          int array[] = {1,2,3,4}
//          auto temp = array; // ok 可以推导为 int *
//          auto temp[] = array; // 这段是错的
// 5. 不能推导模版
//         template<typename T>
//         struct Test{}
//         int main(){
//            Test<double> t;
//            Test<auto> te = t;// error
//         }

// decltype的推导可以不用初始化，但是auto需要初始化 
// decltype 的推导也是在编译器完成的 只是用于表达式类型的推导 并不会计算表达式的值
// decltype(表达式) var = 10;
// decltype(func()) var = 10; 返回值的数据类型就是变量的类型
// class Test{
//   public:
//       int num = 9;
// }
// const Test obj;
// int a = 10;
// 加了const 且加了括号则为 const int &类型
// decltype((obj.num)) b = a;
// 表达式是一个左值，或者被括号包围，使用decltype推导的是表达式类型的引用
// 普通的 decltype(m) d = 10; m就是一个简单的右值
// decltype(n=n+m) d = 10;  


class First
{
  public:
    static int get()
    {
      return 10;
    }
};

class Second
{
  public:
    static string get()
    {
      return "hello world";
    }
};

template<class T>
void func()
{
  auto ret = T::get();
  cout << ret << endl;
}

// 返回值类型后置
template<typename T, typename U>
auto add(T t, U u) -> decltype(t+u)
{
  return t + u;
}

int main(int argc, char const *argv[])
{
  
  // 推导为浮点型
  auto money = 1023.3;
  // 推导
  // auto => int
  auto *location = &money;

  // auto => int* 
  auto loca = &money;

  const auto num = 120;
  // temp 被推导为 int类型
  auto temp = num;
  temp = 21;
  cout << temp << endl;

  // 引用类型的推导
  auto current = 10;
  auto& current_temp = current;
  current_temp = 30;
  cout << current << endl;

  map<int, string> result;
  result.insert(make_pair(1, "sofnecy"));
  result.insert(make_pair(2, "alice"));
  result.insert(make_pair(3, "sophia"));

  // 可以使用auto进行方便遍历
  for(auto first = result.begin(); first!=result.end(); first++){
    cout << (*first).first << "," << (*first).second << endl;
  }

  // 这样可以使用
  func<Second>();

  // 只是用表达式的类型 来表示变量sum的类型
  int a = 10;
  decltype(a * 10 + 30) sum = 40;
  cout << sum << endl;

  auto ret = add<int, double>(1, 20.1);
  cout << ret << endl;
  return 0;
}
