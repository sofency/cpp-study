#include<iostream>
using namespace std;

/**
 * @brief 弱引用指针的作用
 * 1. 它不共享指针，不能操作资源，
 * 2. 它的构造不会增加引用计数，析构也不会减少引用计数，
 * 3. 它的主要作用就是作为一个旁观者监视shared_ptr中管理的资源是否存在
 */

// 弱指针的构造
void construct()
{
  shared_ptr<int> sp(new int(20));

  // 1. 传入共享指针
  weak_ptr<int> wk(sp);

  // 2. 等于共享指针
  weak_ptr<int> wk_one = sp;

  // 3. 等于弱指针 or 构造器
  weak_ptr<int> wk_second = wk;
  weak_ptr<int> wk_three(wk);

  cout << "释放前" << endl;
  
  cout << "wk count:" << wk.use_count() << endl;
  cout << "wk_one count:" << wk_one.use_count() << endl;
  cout << "wk_one count:" << wk_second.use_count() << endl;
  cout << "wk_one count:" << wk_three.use_count() << endl;


  // expired() 观察共享资源是否被释放
  cout << "释放后" << endl;
  sp.reset();
  cout << "是否过期 " << (wk.expired() == 1 ? "过期" : "未过期")<< endl;
  cout << "wk count:" << wk.use_count() << endl;
  cout << "wk_one count:" << wk_one.use_count() << endl;
  cout << "wk_one count:" << wk_second.use_count() << endl;
  cout << "wk_one count:" << wk_three.use_count() << endl;
}

void lock()
{
  shared_ptr<int> share_pointer_one, share_pointer_second;
  weak_ptr<int> weak_pointer;
  share_pointer_one = make_shared<int>(21);
  // 设置weak_pointer 检测share_pointer_one
  weak_pointer = share_pointer_one;
  cout << "current count :" << weak_pointer.use_count() << endl;
  // 获取一个新的共享指针类型 此时这个指针也在管理着堆内存
  share_pointer_second = weak_pointer.lock();
  cout << "current count :" << weak_pointer.use_count()  <<  ", value:"<< *share_pointer_one.get()<< endl;

  // 原始操作重置下 引用减1 share_pointer_one放弃对内存的管理 现在仅剩share_pointer_second管理内存
  share_pointer_one.reset();

  // 再拿起对内存的管理权 引用+1
  share_pointer_one = weak_pointer.lock();
  cout << "count :" << weak_pointer.use_count() << endl;
  cout << "ptr one value :" << *share_pointer_one.get()  <<  ", ptr two value:"<< *share_pointer_second.get()<< endl;
}

struct Test
{
  shared_ptr<Test> get()
  {
    return shared_ptr<Test>(this);
  }
  ~Test()
  {
    cout << "析构" << endl;
  }
};
/**
 * @brief 
 * 模板类叫做std::enable_shared_from_this<T>，这个类中有一个方法叫做shared_from_this()，
 * 通过这个方法可以返回一个共享智能指针，在函数的内部就是使用weak_ptr来监测this对象，并通过调用weak_ptr的lock()方法返回一个shared_ptr对象
 * 
 */
struct TestOther: public enable_shared_from_this<TestOther>
{
  shared_ptr<TestOther> get()
  {
    return shared_from_this();
  }
  ~TestOther()
  {
    cout << "析构" << endl;
  }
};

void return_this_exception()
{
  /**
   * @brief 如下Test析构了两次 报错
   * count1
      析构
      析构
      16-weak-smart-pointer.out(82407,0x7ff855e39640) malloc: Double free of object 0x7f9e56705c60
      16-weak-smart-pointer.out(82407,0x7ff855e39640) malloc: *** set a breakpoint in malloc_error_break to debug
      zsh: abort      ./16-weak-smart-pointer.out
   * @param Test 
   * @return shared_ptr<Test> 
   * 在这个例子中使用同一个指针this构造了两个智能指针对象share和ptr，这二者之间是没有任何关系的，
   * 因为ptr并不是通过share初始化得到的实例对象。在离开作用域之后this将被构造的两个智能指针各自析构，导致重复析构的错误。
   */
  shared_ptr<Test> share(new Test);
  shared_ptr<Test> ptr = share->get();
  cout << "count" << ptr.use_count() << endl;
}

void return_this()
{
  shared_ptr<TestOther> share(new TestOther);
  shared_ptr<TestOther> ptr = share->get();
  cout << "count: " << ptr.use_count() << endl;
}

int main(int argc, char const *argv[])
{  
  return_this();
  return 0;
}
