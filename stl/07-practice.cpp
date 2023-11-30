#include<iostream>
#include<algorithm>
using namespace std;
#include<map>

class Worker
{
  public:
    Worker(string name, int salary)
    {
      this->name = name;
      this->salary = salary;
    }
  string name;
  int salary;
};

// 生成招聘人数
void recruit_people(vector<Worker> &workers) { 
  srandom((unsigned)time(NULL));

  string names[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J"};
  for (int i = 0; i< sizeof(names) / sizeof(names[0]); i++)
  {
    workers.push_back(Worker(names[i], rand() % 10000 + 10000));
  }
}

// 分配组
multimap<int, Worker> divide_group(const vector<Worker> &workers)
{
  srandom((unsigned)time(NULL));
  multimap<int, Worker> company;
  for (vector<Worker>::const_iterator worker = workers.begin(); worker != workers.end(); worker ++)
  {
    int departmentCode = rand() % 3;
    company.insert(make_pair(departmentCode, *worker));
  }
  return company;
}

int main(int argc, char const *argv[])
{
  vector<Worker> workers;
  recruit_people(workers);
  multimap<int, Worker> company = divide_group(workers);
  string groups[] = {"美术", "策划", "开发"};
  for (int i = 0; i< 3; i++)
  {
    multimap<int, Worker>::iterator pos = company.find(i);
    int count = company.count(i);
    int index = 0;
    cout << groups[i] << " 部门员工人数为 " << count<< endl;
    for(;pos != company.end() && index < count; pos ++, index++)
    {
      cout <<"name:"<< (*pos).second.name << ", salary:"<< (*pos).second.salary << endl;
    }
  }
  return 0;
}
