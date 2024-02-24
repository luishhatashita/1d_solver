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

void printArray(int n, double*& arr)
{
    cout << "printArray" << endl;
    for (int i=0; i<n; i++) {
        cout << arr[i] << " , ";
    } 
    cout << endl;
}

void arrayZeros(int n, double*& arr) 
{
    cout << "arrayZeros" << endl;
    allocate1d(n, arr);
    for (int i=0; i<n; i++){
        arr[i] = 0.0;
    }
}

void linSpace(double xbegin, double xend, int n, double*& arr)
{
    cout << "linSpace" << endl;
    double dx = (xend-xbegin)/(n-1);
    allocate1d(n, arr);
    for (int i=0; i<n; i++){
        arr[i] = xbegin + i*dx;
    }
}

void spacingArray(int n, double*& arrin, double*& arrout)
{
    cout << "spacingArray" << endl;
    arrayZeros(n-1, arrout);
    for (int i=0; i<(n-1); i++) {
        arrout[i] = arrin[i+1] - arrin[i];
    }
}

void copyArray(int n, double*& arrin, double*& arrout)
{
    cout << "copyArray" << endl;
    for (int i=0; i<(n); i++) {
        arrout[i] = arrin[i];
    }
}
