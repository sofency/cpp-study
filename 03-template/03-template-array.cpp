#include "03-template-array.hpp"

void addInfo(Array<int> &array)
{
  srandom((unsigned)time(NULL));

  for (int i = 0; i < 100; i++)
  {
    int num = rand() % 1000;
    array.add(num);
  }
}

int main(int argc, char const *argv[])
{
  Array<int> array(10);
  addInfo(array);
  array.show(',');
  return 0;
}
