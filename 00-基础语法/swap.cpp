#include "swap.h"
// 分文件编写
void swap(int* a, int* b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}
