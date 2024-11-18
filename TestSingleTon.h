#ifndef TESTSINGLETON_H
#define TESTSINGLETON_H

#include <iostream>
#include <string.h>

using namespace std;

class TestSingleTon {
private:
    static TestSingleTon* mSingleTonInstance;
    string mNameObject;
    TestSingleTon(string nameObject): mNameObject(nameObject) {
        cout << "NameObject: " << nameObject << endl;
    }
public:
    ~TestSingleTon() {}
    static TestSingleTon* getSingleTonInstance(string nameObject) {
        if(mSingleTonInstance == nullptr){
            mSingleTonInstance = new TestSingleTon(nameObject);
        }
        return mSingleTonInstance;
    }
};
TestSingleTon* TestSingleTon::mSingleTonInstance = nullptr;

#endif // TESTSINGLETON_H
