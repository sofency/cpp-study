#include<iostream>
#include<memory>
using namespace std;

/**
 * @brief 
 * 智能指针式存储指向动态分配（堆）对象指针的类，用于生存期的控制，能够确保在离开指针所在作用域时，自动的销毁动态分配
 * 的对象，防止内存泄漏，智能指针的核心实现技术就是引用计数，每使用一次，内部引用计数+1，每析构一次，美不的引用计数减1
 * 减为0时，删除所指向的堆内存
 */


class Test
{
public:
    Test() 
    {
        cout << "construct Test..." << endl;
    }
    Test(int x) 
    {
        cout << "construct Test, x = " << x << endl;
    }
    Test(string str) 
    {
        cout << "construct Test, str = " << str << endl;
    }
    ~Test()
    {
        cout << "destruct Test ..." << endl;
    }
};

void get()
{
  // 通过智能指针可以管理一个普通变量或者对象的地址，此时原始地址就不可见了。
  // 当我们想要修改变量或者对象中的值的时候，就需要从智能指针对象中先取出数据的原始内存的地址再操作，
  // 解决方案是调用共享智能指针类提供的get()方法，其函数原型如下

  int len = 128;
  shared_ptr<char> ptr(new char[len]);
  // 得到指针的原始地址
  char* add = ptr.get();
  memset(add, 0, len);
  strcpy(add, "我是要成为海贼王的男人!!!");
  cout << "string: " << add << endl;
  
  // 指针赋值
  shared_ptr<int> p(new int);
  *p = 100;
  cout << *p.get() << "  " << *p << endl;

}

void copy()
{
  // 使用智能指针管理一块 int 型的堆内存, 内部引用计数为 1
  shared_ptr<int> ptr1(new int(520));
  cout << "ptr1管理的内存引用计数: " << ptr1.use_count() << endl;
  //调用拷贝构造函数
  shared_ptr<int> ptr2(ptr1);
  cout << "ptr2管理的内存引用计数: " << ptr2.use_count() << endl;
  shared_ptr<int> ptr3 = ptr1;
  cout << "ptr3管理的内存引用计数: " << ptr3.use_count() << " ptr2:"<< ptr2.use_count() << endl;
  // 上述执行完后 内存int 上面的ptr1 ptr2 ptr3引用计数都为3

  //调用移动构造函数
  shared_ptr<int> ptr4(std::move(ptr1));
  cout << "ptr4管理的内存引用计数: " << ptr4.use_count() << endl;
  std::shared_ptr<int> ptr5 = std::move(ptr2);
  cout << "ptr5管理的内存引用计数: " << ptr5.use_count() << endl;
}

void count()
{
  // 使用智能指针管理一块 int 型的堆内存
  shared_ptr<int> ptr1(new int(520));
  cout << "ptr1管理的内存引用计数: " << ptr1.use_count() << endl;
  // 使用智能指针管理一块字符数组对应的堆内存
  shared_ptr<char> ptr2(new char[12]);
  cout << "ptr2管理的内存引用计数: " << ptr2.use_count() << endl;
  // 创建智能指针对象, 不管理任何内存
  shared_ptr<int> ptr3;
  cout << "ptr3管理的内存引用计数: " << ptr3.use_count() << endl;
  // 创建智能指针对象, 初始化为空
  shared_ptr<int> ptr4(nullptr);
  cout << "ptr4管理的内存引用计数: " << ptr4.use_count() << endl;
}
void make_share()
{
   // 使用智能指针管理一块 int 型的堆内存, 内部引用计数为 1
  shared_ptr<int> ptr5 = make_shared<int>(520);
  cout << "ptr5管理的内存引用计数: " << ptr5.use_count() << endl;

  shared_ptr<Test> ptr6 = make_shared<Test>();
  cout << "ptr6管理的内存引用计数: " << ptr6.use_count() << endl;

  shared_ptr<Test> ptr7 = make_shared<Test>(520);
  cout << "ptr7管理的内存引用计数: " << ptr7.use_count() << endl;

  shared_ptr<Test> ptr8 = make_shared<Test>("我是要成为海贼王的男人!!!");
  cout << "ptr8管理的内存引用计数: " << ptr8.use_count() << endl;

  // 对于一个未初始化的共享智能指针，可以通过reset方法来初始化，当智能指针中有值的时候，调用reset会使引用计数减1。
  ptr8.reset();
}


// 自定义删除器函数，释放int型内存
void deleteIntPtr(int* p)
{
    delete p;
    cout << "int 型内存被释放了...";
}

/**
 * @brief 当智能指针管理的内存对应的引用计数变为0的时候，这块内存就会被智能指针析构掉了。
 * 另外，我们在初始化智能指针的时候也可以自己指定删除动作，这个删除操作对应的函数被称之为删除器，
 * 这个删除器函数本质是一个回调函数，我们只需要进行实现，其调用是由智能指针完成的
 * 
 * @return voide 
 */
void delete_pointer()
{
  // 指定删除器
  shared_ptr<int> ptr(new int(250), deleteIntPtr);

  // 注意删除数组时
  // 在C++11中使用shared_ptr管理动态数组时，需要指定删除器，
  // 因为std::shared_ptr的默认删除器不支持数组对象，具体的处理代码如下：
   shared_ptr<int> ptr_array(new int[10], [](int* p) {delete[]p; });
  // 或者如下
  shared_ptr<int> ptr_arrays(new int[10], default_delete<int[]>());
}

int main(int argc, char const *argv[])
{
  get();

  delete_pointer();
  return 0;
}


