#include<iostream>
#include <memory>
using namespace std ;

class B;

class A
{
public:
    shared_ptr<B> sB; // edit to weak_ptr
    // weak_ptr<B> sB;
    A() {  cout << "A()" << endl; }
    ~A() { cout << "~A()" << endl; }
};

class B
{
public:
    shared_ptr<A> sA; // edit to weak_ptr
    // weak_ptr<A> sA;
    B() {  cout << "B()" << endl; }
   ~B() { cout << "~B()" << endl; }
};

void someFunction(shared_ptr<A> a, shared_ptr<B> b) {
    a = make_shared<A>();
    b = make_shared<B>();
    a->sB = b;
    b->sA = a;
    cout << "====: " << a.use_count();
    cout << "MMMM: " << a->sB.use_count();
}

int main()
{
    shared_ptr<A> a;
    shared_ptr<B> b;
    someFunction(a, b);  // result A() B(): only constructor, no destructor
    // error happened when using shared A tro toi B, va B tro toi A => Giai Phap weak_pointer
    cout << "====: " << a.use_count();
    
    return 0;  
}

