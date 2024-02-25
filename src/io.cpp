#include <fstream>
#include <format>
#include <iostream>
#include "io.h"

//#include <iomanip>
//#include <string>

using namespace std;

void fileName(string folder, string prefix, int it, string& fname)
{
    fname = format("./out/{}/{}_{:05d}.bin", folder, prefix, it);
    cout << fname << endl;
}

void writeBinaryArray(string fname, int n, double*& arr)
{
    cout << "writeBinaryArray" << endl;
    
    // Open a binary file for writing
    ofstream out(fname, ios::binary);

    if (!out.is_open()) {
        cerr << "Error opening file for writing." << endl;
        return;
    }

    // Write the array to the binary file
    out.write(reinterpret_cast<const char*>(arr), n*sizeof(double));

    // Close the file
    out.close();
}
