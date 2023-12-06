#include<iostream>
using namespace std;

/**
 * @brief weak_ptr解决循环引用的问题
 * 
 */

struct TA;
struct TB;

struct TA
{
    shared_ptr<TB> bptr;
    ~TA()
    {
        cout << "class TA is disstruct ..." << endl;
    }
};

struct TB
{
    shared_ptr<TA> aptr;
    ~TB()
    {
        cout << "class TB is disstruct ..." << endl;
    }
};

struct TTA;
struct TTB;

struct TTA
{
    weak_ptr<TTB> bptr;
    ~TTA()
    {
        cout << "class TTA is disstruct ..." << endl;
    }
};

struct TTB
{
    weak_ptr<TTA> aptr;
    ~TTB()
    {
        cout << "class TTB is disstruct ..." << endl;
    }
};

class Other
{
  ~Other()
  {
    cout << "other" << endl;
  }
};

template<class T1, class T2>
void testPtr(T1* t1, T2* t2)
{
    shared_ptr<T1> ap(t1);
    shared_ptr<T2> bp(t2);
    cout << "T1 object use_count: " << ap.use_count() << endl;
    cout << "T2 object use_count: " << bp.use_count() << endl;

    // ap里面的bp共享指针初始化 构成a 引用b, b引用a
    ap->bptr = bp;
    bp->aptr = ap;
    cout << "T1 object use_count: " << ap.use_count() << endl;
    cout << "T2 object use_count: " << bp.use_count() << endl;
}

int main()
{
    // testPtr<TA, TB>(new TA, new TB);
    testPtr<TTA, TTB>(new TTA, new TTB);

    return 0;
}