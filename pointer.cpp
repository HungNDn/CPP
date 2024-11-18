#include<iostream>

using namespace std;
int main() {
    int a = 20;
    int b = 30;
    int* p = &a;
    cout <<"address1: " << p << endl;
    int*temp = p;
    cout <<"address: " << temp << endl;
    p = &b;
    cout <<"address2: " << p << endl;
    return 0;
}