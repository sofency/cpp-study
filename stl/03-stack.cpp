#include<iostream>
#include<stack> //栈 先进后出
#include<queue> //队列 先进先出
using namespace std;

int main(int argc, char const *argv[])
{
  stack<int> stack;
  stack.push(21);
  stack.push(23);
  stack.push(40);

  // 弹出栈顶
  stack.pop();
  // 输出栈顶的元素
  cout << stack.top() << endl;
  return 0;
}
