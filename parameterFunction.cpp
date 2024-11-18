#include <iostream>
#include <sqlite3.h>

using namespace std;

// pass by value  
int sum(int a, int b){
    int sum = a + b;
    return sum;
}

// pass by reference
void PlusTo10(int &input) {
    input = input + 10;
} 

// pass by pointer
void EnterArray(int* a, int n) {
    int count = 0;
    while(count < n) {
        cin >> a[count];
        count++;
    }
}

// pass by pointer 
void ExportArray(int* a, int n) {
    for (int i = 0; i < n; i++) {
        cout << a[i];
        if(i < n-1) 
            cout << " ";
    }   
}

int main() {
    int a = 5; 
    int b = 10;
    cout <<"a , b before: " << a << ", " << b << endl;
    sum(a, b);
    cout <<"a , b after: " << a << ", " << b << endl;
    // pass by value
    int input = 10;
    cout << "input before: " << input << endl;
    PlusTo10(input);
    cout << "input before: " << input << endl;
    //pass by reference
    int c[20];
    int n = 4;
    EnterArray(c, 4);
    ExportArray(c, 4);
}