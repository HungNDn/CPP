#ifndef DATABASE_H
#define DATABASE_H
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "ISubject.h"
#include "Observer.h"
using namespace std;
class Database : public ISubject {
private:
    vector<Observer*> mObserver;
    string mOperation;
public:
    Database() {}

    void registerObserver(Observer* observer) {
        mObserver.push_back(observer);
    }

    void notifyObserver() {
        for(int i = 0 ; i < mObserver.size() ; i++) {
            mObserver[i]->update(mOperation);
        }
    }

    void removeObserver(Observer* observer) {
        vector<Observer*>::iterator x = find(mObserver.begin(), mObserver.end(), observer);
        if(x != mObserver.end())
            mObserver.erase(x);
    }

    void editRecord(string operation) {
        mOperation = operation;
        notifyObserver();
    }
};

#endif // DATABASE_H
