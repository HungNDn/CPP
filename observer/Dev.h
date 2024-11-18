#ifndef DEV_H
#define DEV_H
#include "Observer.h"
#include <string.h>
using namespace std;
class Dev : public Observer {
public:
    Dev() {}
    void update(string operation) {
        cout << "operation database : " << operation << endl;
    }
};

#endif // DEV_H
