#include<iostream>
using namespace std;
void func(char *p)
{
 cout << "function (char *p)" << endl; 
}

void func(int num)
{
 cout << "function (int num)" << endl; 
}

int main(int argc, char const *argv[])
{
  // 建议使用nullptr
  char * ptr1 = NULL;
  int *ptr2 = NULL;


  // 必须要进行类型转换
  int * ptr3 = (int *)ptr1;

  func(ptr1);

  func(10);

  // func(NULL); 会报错 cpp 底层NULL默认为0 是数值类型
  func(nullptr);
  return 0;
}

