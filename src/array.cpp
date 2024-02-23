#include <iostream>
#include "allocate.h"
#include "array.h"

array1d::array1d(int n)
{
    len = n;
    allocate1d(n, arr);
    //*arr = new double[n];
    for (int i=0; i<len; i++) {
        arr[i] = 0;
    } 
}

array1d::~array1d()
{
    deallocate1d(arr);
    //delete[] arr;
}

void array1d::printArray()
{
    for (int i=0; i<len; i++) {
        cout << arr[i] << endl;
    } 
}
