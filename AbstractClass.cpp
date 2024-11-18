#include <iostream> 

using namespace std;
// abstract class always has at least a pure virtual function, 
// no has constructor and deconstructor
// access modifier : full as a class. 
// Cant create object.
// Only using it by derived class.

// When a devired class inheritance a abstract class base, 
// it must override all virtual function of base class;
class Shape {
    protected:
        float dimension;
    public: 
        void getDimension() {
            cin >> dimension;
        }
        virtual float calculateArea() = 0; // pure virtual function
};

class Square : public Shape {
    public: 
        float calculateArea() {
            return dimension * dimension;
        }
};

class Circle : public Shape {
    public: 
        float calculateArea() {
            return 3.14 * dimension * dimension;
        }
};


// Key Points of Runtime Polymorphism in C++:
// Same name different actions
// Runtime Polymorphism is achieved using function overriding
// Virtual functions are abstract functions of the base class
// The derived class must override the virtual functions
// A base class pointer pointing to a derived class object and an override function is called

int main() {
    // Shape shape; error
    Shape* square = new Square();
    Shape* circle = new Circle();

    cout << "Enter the length of the square: ";
    square->getDimension();
    cout << "Area of square: " << square->calculateArea() << endl;

    cout << "\nEnter radius of the circle: ";
    circle->getDimension();
    cout << "Area of circle: " << circle->calculateArea() << endl;

    return 0;
}