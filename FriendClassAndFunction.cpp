#include <iostream>

using namespace std;

class You;
class Me {
    private:
        string name;
    protected:
        string ngaySinh;
    public:
        string lop;
        Me() {
            this->name = "Hung";
            this->ngaySinh = "06/08/1996";
            this->lop = "10A8";
        }
        friend You;
        friend void getName();
};

void getName() {
    Me me;
    cout << me.name << endl;
    cout << me.ngaySinh << endl;
    cout << me.lop << endl;
}

class You {
    private:
        Me me;
    public:
        void getName() {
            cout << this->me.name << endl;
            cout << this->me.ngaySinh << endl;
            cout << this->me.lop << endl;
        }
};

int main() {
    You you;
    you.getName();
    getName();
    return 0;
}