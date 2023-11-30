#include <iostream>
using namespace std;

// 声明
// template <typename T> 或者
template <class T>
void custom_swap(T &a, T &b)
{
  T temp = a;
  a = b;
  b = temp;
}

template <typename T>
void sort(T &arr, int length)
{
  for (int i = 0; i < length; i++)
  {
    int index = 0;
    for (int j = 0; j < length - i; j++)
    {
      if (arr[index] < arr[j] && index != j)
      {
        index = j;
      }
    }
    // 放到最后一位
    custom_swap(arr[length - i - 1], arr[index]);
  }
}

template <typename T>
void print_arr(T &arr)
{
  for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
  {
    cout << arr[i] << " ";
  }
  cout << endl;
}
int main(int argc, char const *argv[])
{

  int a = 10;
  int b = 20;
  // 自动类型推断
  custom_swap(a, b);
  cout << a << "," << b << endl;

  // 指定类型 模版必须确定出T的数据类型，才可以使用
  custom_swap<int>(a, b);
  cout << a << "," << b << endl;

  double temp_a = 1.0;
  double temp_b = 2.0;
  custom_swap<double>(temp_a, temp_b);
  cout << temp_a << "," << temp_b << endl;

  int arr[] = {4, 2, 9, 7, 5, 1, 6, 2};
  sort(arr, sizeof(arr) / sizeof(arr[0]));
  print_arr(arr);
  return 0;
}

// 普通函数和模版函数的区别
// 普通函数执行时 可以进行隐式类型转换 比如 位数小的可以转为大的 char 可以放到 int 类型的函数参数中
// 模版函数， 用自动类型推导，不可以发生隐式类型转换
// 模版函数   用显式指定类型 可以发生隐式类型转换