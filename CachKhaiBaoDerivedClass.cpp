#include <iostream>

using namespace std;

class Base {
    protected: 
        int width;
        int height;
    public:
        
        Base() {

        }

        virtual float dientich() = 0;
};

class Derived : public Base {        
    public :
        int k;
        Derived() {
            Base::height = 10;
            Base::width = 2;
        }
        float dientich() {
            return (Base::width * Base::height);
        }
};

int main() {

    // Case1:
    Derived* x = new Derived();
    x->k = 10; // Ok
    // Case2:
    Base* y = new Derived();

    // y->k = 10; // error cant access to member data of Derived

    cout << "Dien tich x: " << x->dientich() << endl;
    cout << "Dien tich y: " << y->dientich() << endl;
    
    return 0;
}