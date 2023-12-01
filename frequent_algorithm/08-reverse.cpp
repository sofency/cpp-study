#include <iostream>

using namespace std;

int main()
{
    vector<int> list = {10,20,40,20,12,23};
    // 翻转前
    for_each(list.begin(), list.end(), [](int val){cout << val << " ";});
    cout << endl;

    // 翻转后
    reverse(list.begin(), list.end());
    for_each(list.begin(), list.end(), [](int val){cout << val << " ";});
    cout << endl;
    return 0;
}