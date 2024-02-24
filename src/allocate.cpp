#include <iostream>
#include "allocate.h"

using namespace std;

void allocate1d(int n, double*& arr) 
{
    cout << "allocate1d" << endl;
    arr = new double[n];
}

void deallocate1d(double*& arr) 
{
    cout << "deallocate1d" << endl;
    delete[] arr;
}

void allocate2d() 
{
    cout << "allocate2d" << endl;
}

void deallocate2d() 
{
    cout << "deallocate2d" << endl;
}
