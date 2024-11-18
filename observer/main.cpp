//#include "TestSingleTon.h"

//int main()
//{
//    TestSingleTon* test;
//    test = TestSingleTon::getSingleTonInstance("Hello");
//    test = TestSingleTon::getSingleTonInstance("HelloWorld");
//    return 0;
//}

#include "Dev.h"
#include "Database.h"

int main() {
    Database db;
    Dev dev;
    db.registerObserver(&dev);
    db.editRecord("Add");
    return 0;
}
