#include <iostream>
#include <algorithm>
using namespace std;

class Solution
{
public:
  int lengthOfLongestSubstring(string s)
  {
    int length = s.length();
    int max_length = 0;
    int temp = 0;
    string temp_str = "";

    while (temp < length)
    {
      int index = temp_str.find_first_of(s.at(temp));
      if (index == -1)
      {
        temp_str += s.at(temp);
        temp++;
        max_length = max<int>(max_length, temp_str.size());
      }
      else
      {
        max_length = max<int>(max_length, temp_str.size());
        // wpew -> pew 然后继续在pew中进行查找
        temp_str = temp_str.substr(index + 1, temp + 1);
        cout << "current find str " << temp_str << " ,temp:" << temp << endl;
      }
    }
    return max_length;
  }
};

int main(int argc, char const *argv[])
{
  Solution solution;
  cout << solution.lengthOfLongestSubstring("abcabcbb") << endl;
  return 0;
}
