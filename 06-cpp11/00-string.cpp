#include<iostream>
using namespace std;

int main(int argc, char const *argv[])
{
  // 字面量加R 这样不用加转义字符
  string path = R"(D:\hello\path\code)";
  cout << path << endl;

  // 保留原来的格式输出
  // 不加R 换行输出会报错
  string html = R"(
    <html>
      <title>sofency</title>
      <body>
        <span>hello world</span>
      </body>
    </html>
  )";

  cout << html << endl;
  return 0;
}
