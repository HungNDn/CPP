#include <iostream>
using namespace std;

// This situation is only has bit number constain value(1) and
// all 7 remaining bits is 0 => when they & => equal = 0 or equal != 0;
bool checkBitIsSetOrNot(int number, int bitNumber) {
    // equal != 0
    if(number & (1 << bitNumber)) {  
        cout << "number bit " << bitNumber << " is SET";
        return true;
    } else {
        cout << "number bit " << bitNumber << " is not SET";
        return false;
    }
    return false;
}

enum class Align {
    None    = 0x00,
    Top     = 0x01,
    Left    = 0x02,
    Bottom  = 0x04,
    Right   = 0x08,
};

int main() {
    int a = 1;
    cout << "So 1 dich sang trai 3 bit: " << (a << 3) << endl; // 0000 0001 << 1 => 0000 1000 = 8
    checkBitIsSetOrNot(31, 3);
    return 0;
}