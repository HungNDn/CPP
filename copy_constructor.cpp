#include <iostream>
class Car {
    public:
        int *a;
        Car(){
            std::cout << "Car" << std::endl;
            a = new int[10];
        };

        // Copy constructor
        Car(const Car& car) {
            a = new int[10];
            for(int i = 0; i < 10; i++){
                a[i] = car.a[i];
            }
        }

        virtual ~Car(){
            delete[] a;
            std::cout << "~Car" << std::endl;
        };
        
        virtual int wheel_car() {
            std::cout << "4 wheels" << std::endl;
            return 4;
        }
};

int main() {
    Car car;
    Car car1 = car;
    car1.wheel_car();
    return 0;
}

// Output : 
// Car
// 4 wheels
// ~Car
// run(88417,0x1f3867a80) malloc: Double free of object 0x130e06910
// run(88417,0x1f3867a80) malloc: *** set a breakpoint in malloc_error_break to debug
// zsh: abort      ./run

// Do ko tao constructor copy. Khi delete car => 
// ta lai tiep tuc delete car1(ma car1 co pointer a, ma a da bi huy truoc roi, ta lai huy lai)

// Sau khi them copy constructor =>
// Output: 
// Car
// 4 wheels
// ~Car
// ~Car