// C++ program to illustrate implicit conversions
#include <iostream>
using namespace std;
 
class Demo{
    public:
        /*explicit*/ Demo(int n){
            demo1 = n;
        }
        int getDemo(){
            return demo1;
        }
    private:
        int demo1;
};
 
void getDemoExternally(Demo demo){
    cout << demo.getDemo();
}
// Driver Code
int main()
{
    getDemoExternally(10);
    return 0;
}
// Output : 10

// Do viec ko dung explicit cho constructor dan den viec compile ngam dinh chuyen doi 10 -> Demo. 
// De tranh viec nay can them tu khoa explicit truoc constructor
