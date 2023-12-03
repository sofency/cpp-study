#pragma once
#include <iostream>
using namespace std;

// 实现一个通用的数组类
// 1.可以将内置的数据类型以及自定义的数据类型进行存储
// 2.将数据中的数据存储到堆区
// 3.构造函数中可以传入数组容量
// 4.提供拷贝构造函数 以及operator= 防止浅拷贝
// 5.使用尾插法和尾删法对数组进行新增和删除
// 6.可以通过下标的方式进行访问数组中的元素
// 7.可以获取数组中的元素个数和数组容量

template <class T>
class Array
{
public:
  Array(int capacity)
  {
    this->capacity = capacity;
    this->t = new T[capacity];
    this->length = 0;
  }
  // 拷贝
  Array(const Array &array)
  {
    this->capacity = array.capacity;
    this->length = array.length;
    this->t = new T[this->capacity];
    for (int i = 0; i < this->length; i++)
    {
      this->t[i] = array.t[i];
    }
  }
  // 数据在添加的过程中需要先判断是否超过容量 如果超过 需要重新申请内存
  void add(T num)
  {
    // 判断内存容量
    if (this->length + 1 > this->capacity)
    {
      cout << "正在扩容" << endl;
      show(',');
      if (this->capacity < 50)
      {
        this->capacity = this->capacity * 2;
      }
      else
      {
        this->capacity = this->capacity + this->capacity / 2;
      }
      T *t = new T[this->capacity];
      for (int i = 0; i < this->length; i++)
      {
        t[i] = this->t[i];
      }
      // 删掉之前的数据
      delete[] this->t;
      this->t = t;
    }
    this->t[this->length] = num;
    this->length++;
  }
  void show(char seq)
  {
    cout << "当前容量:" << this->capacity << endl;
    cout << "当前长度:" << this->length << endl;
    cout << "当前数据:";
    for (int i = 0; i < this->length - 1; i++)
    {
      cout << this->t[i] << seq;
    }
    cout << this->t[this->length - 1] << ";" << endl;
  }

  // 赋值操作 防止浅拷贝
  Array &operator=(Array &array)
  {
    if (this->t != NULL)
    {
      delete[] this->t;
      this->t = NULL;
    };
    return *new Array(array);
  }

  ~Array()
  {
    if (this->t != NULL)
    {
      delete[] this->t;
      this->t = NULL;
    }
  }

private:
  T *t;
  int capacity;
  int length;
};