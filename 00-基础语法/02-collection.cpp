#include <iostream>
using namespace std;
#include "swap.cpp"

void reverse_array(int *array, int length)
{
  for (int i = 0; i < length / 2; i++)
  {
    int temp = array[length - i - 1];
    array[length - i - 1] = array[i];
    array[i] = temp;
  }
}
// 降序
void bubbling_sort_prev(int *array, int length)
{
  for (int i = 0; i < length; i++)
  {
    int temp = array[i];
    int index = i;
    for (int j = i; j < length; j++)
    {
      if (array[j] > temp)
      {
        temp = array[j];
        index = j;
      }
    }
    // 交换
    int temp_value = array[i];
    array[i] = array[index];
    array[index] = temp_value;
  }
}

// 升序
// 1. 先默认最后一个为最大值
// 2. 从0开始 依次将当前值与第一步定义的值进行比较 大于则替换最大值，并记住索引
// 3. 交换 默认最大值与找到的最大值
// 4. 并默认 最后第二个为最大值 依次
void bubbling_sort_tail(int *array, int length)
{
  for (int i = 0; i < length; i++)
  {
    int temp = array[length - i - 1];
    int index = length - i - 1;
    for (int j = 0; j < length - i; j++)
    {
      if (array[j] > temp)
      {
        temp = array[j];
        index = j;
      }
    }
    // 交换
    int temp_value = array[length - i - 1];
    array[length - i - 1] = array[index];
    array[index] = temp_value;
  }
}

void bubbling_sort(int *array, int length)
{
  for (int i = 0; i < length - 1; i++)
  {
    bool flag = false;
    for (int j = 1; j < length - i; j++)
    {
      if (array[j - 1] > array[j])
      {
        int temp = array[j];
        array[j] = array[j - 1];
        array[j - 1] = temp;
        flag = true;
      }
    }
    // 已经排好序了
    if (!flag)
      break;
  }
}

// 数组的定义
int define_array()
{
  // int array[5]; 未初始化 直接定义 默认为0
  // int array[5] = {1, 2, 4, 5, 6}; 赋值操作
  // 这样不指定数组长度
  int array[] = {1, 2, 3, 4, 5, 6, 7};

  cout << "查看元素array[0]的地址:" << &array[0] << endl;
  cout << "查看元素array[1]的地址:" << &array[1] << endl;
  // 这种必须要设置列数
  // int tuple[][4] = {{1, 2, 3, 4}, {3, 4, 5, 6}};
  // 这样可以计算出来
  int tuple[][4] = {1, 2, 3, 4, 3, 4, 5, 6};
  //
  cout << "查看二维数组的地址:" << &tuple[1] << endl;
  cout << "查看二维数组的地址:" << tuple[0] << endl;
  cout << "查看二维数组的地址:" << tuple << endl;

  return sizeof(array) / sizeof(int);
}

// 函数的声明
// 提前声明
int max(int a, int b);

int main(int argc, char const *argv[])
{
  cout << "数组长度:" << define_array() << endl;
  int num[] = {5, 2, 1, 4, 9, 3, 7, 5, 1};
  bubbling_sort(num, sizeof(num) / sizeof(int));
  for (int i = 0; i < sizeof(num) / sizeof(int); i++)
  {
    cout << num[i] << " ";
  }
  cout << endl;

  // 分文件编写
  int a = 10;
  int b = 20;
  cout << "a地址" << &a << endl;
  cout << "a地址上的值|解引用" << *(&a) << endl;

  swap(&a, &b);
  cout << "a=" << a << endl;
  cout << "b=" << b << endl;

  // 但是如果要赋值新的位置 会报错 因为系统0-255是系统占用的 不允许访问
  int *p = NULL;
  // 野指针 这块地址也不是你申请的 当你要访问 就会报错
  // int *x = (int*)0x9898;

  return 0;
}

int max(int a, int b)
{
  return a > b ? a : b;
}