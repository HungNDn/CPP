#ifndef OBSERVER_H
#define OBSERVER_H
#include <iostream>
#include <string.h>
using namespace std;
class Observer {
public:
    virtual void update(string operation) = 0;
};

#endif // OBSERVER_H
