#include <iostream> 
#include <unistd.h>

using namespace std;

int main() {
    int i = 10;
    
    int a = i++;
    cout << "a, i: " << a << " " << i << endl; 

    int j = 10;
    int b = ++j;
    cout << "b, j: " << b << " " << j << endl;

    return 0;
}