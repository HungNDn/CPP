#include <iostream>
#include <algorithm>
using namespace std;

// insert a element into array at pos
void insertIntoArrayAt(int pos, int value, int a[], int n) {
    n++;
    for(int i = n; i >= pos; i--) {
        a[i] = a[i-1]; //a[8] = a[7]; a[7] = a[6]
    }
    a[pos] = value;
}

// Delete a element get out array at pos
void deleteArrayAt(int pos, int a[], int n) {
    n--;
    for (int i = pos; i < n; i++) {
        a[i] = a[i+1];
    }
    
}

// swap 2 elements
void swap(int& a, int& b) {
    int temp = a;
    a = b; 
    b = temp;
}
// sort in ascending order: bubble sort
void sortAscending(int a[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if(a[i] < a[j])
                swap(a[i], a[j]);
        }    
    } 
}
// linear search
int linearSearch(int value, int a[], int n) {
    for (int i = 0; i < n; i++) {
        if(a[i] == value) 
            return i;
    }
    return -1; 
}

// binary search
int binarySearch(int value, int a[], int l, int r) {
    if(r >= l) {
        int mid = (l + (r - 1)) / 2;
        if(a[mid] == value) 
            return mid;
        if(a[mid] > value) 
            return binarySearch(value, a, l, mid - 1); 
        return binarySearch(value, a, mid + 1, r);
    }
    return -1;
}

int main() {
    int a[] = {1,3,4,6,7,3,2};
    int n = sizeof(a) / sizeof(a[0]);
    int valueSearch = 6;

    // insertIntoArrayAt(3, 10, a, n);
    // deleteArrayAt(3, a, n);

    // cout << "Number " << valueSearch << " at " << linearSearch(valueSearch, a, n);  

    // Only using binarySearch on a array which is sorted
    // sort(a, a + n); 
    sortAscending(a, n);
    for (int i = 0; i < n; i++) {
        cout << a[i]  << " ";
    }
    
    cout << "\nNumber " << valueSearch << " at " << binarySearch(valueSearch, a, 0, n-1);  
    return 0;
}