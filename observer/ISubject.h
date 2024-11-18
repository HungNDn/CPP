#ifndef ISUBJECT_H
#define ISUBJECT_H

#include <iostream>
#include "Observer.h"
#include <string.h>
using namespace std;
class Observer;
class ISubject {
public:
    virtual void registerObserver(Observer* observer) = 0;
    virtual void removeObserver(Observer* observer) = 0;
    virtual void notifyObserver() = 0;
};

#endif // ISUBJECT_H
