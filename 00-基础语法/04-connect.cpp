#include <iostream>
using namespace std;
#define MAX 1024

struct person
{
  string name;
  int age;
  string location;
  string cellphone;
};
struct address_notes
{
  int length;
  struct person per[MAX];
};

// 展示菜单
void show_menu()
{
  cout << "*******************************" << endl;
  cout << "*      1.添加联系人           *" << endl;
  cout << "*      2.展示联系人           *" << endl;
  cout << "*      3.查找联系人           *" << endl;
  cout << "*      4.修改联系人           *" << endl;
  cout << "*      5.删除联系人           *" << endl;
  cout << "*      0.退出                 *" << endl;
  cout << "*******************************" << endl;
}

void add_notes(struct address_notes *notes)
{
  struct person per;
  cout << "请输入姓名" << endl;
  cin >> per.name;
  cout << "请输入年龄" << endl;
  cin >> per.age;
  cout << "请输入住址" << endl;
  cin >> per.location;
  cout << "请输入联系方式" << endl;
  cin >> per.cellphone;
  notes->per[notes->length] = per;
  notes->length++;
}

// 展示联系方式
void show_notes(struct address_notes *notes)
{
  cout << "姓名\t"
       << "年龄\t"
       << "住址\t"
       << "联系方式" << endl;
  for (int i = 0; i < notes->length; i++)
  {
    cout << notes->per[i].name << "\t"
         << notes->per[i].age << "\t"
         << notes->per[i].location << "\t"
         << notes->per[i].cellphone << endl;
  }
}
// 根据姓名查找
void find_notes(struct address_notes notes, string name)
{
  cout << "姓名\t"
       << "年龄\t"
       << "住址\t"
       << "联系方式" << endl;
  for (int i = 0; i < notes.length; i++)
  {
    if (notes.per[i].name == name)
    {
      cout << notes.per[i].name << "\t"
           << notes.per[i].age << "\t"
           << notes.per[i].location << "\t"
           << notes.per[i].cellphone << endl;
      return;
    }
  }
  cout << "抱歉，通讯录中无此人" << endl;
}

void delete_note(struct address_notes *notes, string name)
{
  int index = 0;
  for (int i = 0; i < notes->length; i++)
  {
    if (notes->per[i].name == name)
    {
      continue;
    }
    notes->per[index++] = notes->per[i];
  }
  notes->length = index;
}

int main(int argc, char const *argv[])
{
  struct address_notes notes;

  while (true)
  {
    show_menu();
    cout << "请输入选项" << endl;
    int section;
    cin >> section;
    switch (section)
    {
    case 1:
      add_notes(&notes);
      break;
    case 2:
      show_notes(&notes);
      break;
    case 3:
    {
      string name;
      cout << "请输入要查询的名字" << endl;
      cin >> name;
      find_notes(notes, name);
      break;
    }
    case 4:
    {
      string name;
      cout << "请输入要删除 的名字" << endl;
      cin >> name;
      delete_note(&notes, name);
      break;
    }
    case 0:
      return 0;
      break;
    }
    // 以下是mac电脑专属的
    // system("getchar()");
    // system("clear");
  }

  return 0;
}
