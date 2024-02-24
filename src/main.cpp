#include <iostream>
#include <cmath>
#include "array.h"
#include "allocate.h"

using namespace std;

void setInitialSolution(int n, double*& y, double*& u)
{
    for (int i=0; i<n; i++) {
        u[i] = y[i] + sin(M_PI*y[i]);
    } 
}

/* Function to find minimum dt required for time-accurate solution of scalar
 * diffusion equation based on the VNN number stability requirement for a for-
 * ward difference in time and central difference in space:
 *
 *      VNN = \frac{dt}{Re (dy)^2}
 *
 * Parameters:
 * -----------
 *  int      n   ... size of finite difference array;
 *  double   Re  ... Reynolds number of the simulation;
 *  double   VNN ... von Neumann stability number (upper bound of 0.5 here);
 *  double*& y   ... discretized non-dimensional domain.
 *
 * Return:
 * -------
 *  double dtmin ... minimum of computed array of local dt.
 */
double findMinimumDeltat(int n, double Re, double VNN, double*& dy)
{
    // Declaration of variables:
    double* dt;
    double dtmin;

    // Initialization of local dt array.
    arrayZeros(n-1, dt);

    // Compute local dt;
    for (int i=0; i<(n-1); i++) {
        dt[i] = VNN*Re*(pow(dy[i],2.0));
    }
    //printArray(n-1, dt);

    // Compute minimum dt for time-accurate:
    dtmin = dt[0];
    for (int i=1; i<(n-1); i++) {
        if (dt[i] < dtmin) {
            dtmin = dt[i];
        }
    }
    
    // Deallocate temporary array:
    deallocate1d(dt);
    
    // Return mininum:
    return dtmin;
}

void advanceInTime(
    int n, double Re, double dt, 
    double*& dy, double*& u, double*& unew
)
{
    for (int i=1; i<(n-1); i++) {
        unew[i] = u[i] + \
            (dt/Re)*((2/(dy[i]+dy[i-1])) *
                    ((u[i+1]-u[i])/dy[i]-(u[i]-u[i-1])/dy[i-1]));
    }
    // Boundary conditions:
    unew[0]   = 0;
    unew[n-1] = 1;
}

int main() 
{
    // Parameters:
    int n = 11;
    double *y, *dy, *u0, *u, *unew;
    double Re = 1.0;
    double VNN = 0.5;
    double dt;
    int it = 1;
    int itmax = 201;

    // Initialize arrays:
    linSpace(0.0, 1.0, n, y);
    arrayZeros(n, u0);
    arrayZeros(n, u);
    arrayZeros(n, unew);

    // Initial parametrization:
    // 1. initial solution;
    // 2. array spacing computation;
    // 3. minimal dt for time-accurate solution;
    setInitialSolution(n, y, u0);
    spacingArray(n, y, dy);
    dt = findMinimumDeltat(n, Re, VNN, dy);
    //printArray(n, u0);
    
    // Advance in time:
    copyArray(n, u0, u);
    while (it < itmax) {
        advanceInTime(n, Re, dt, dy, u, unew);
        copyArray(n, unew, u);
        if (it % 10 == 0) {
            printArray(n, u);
        }
        it++;
    }

    // Deallocate memory:
    deallocate1d(y);
    deallocate1d(dy);
    deallocate1d(u0);
    deallocate1d(u);
    deallocate1d(unew);
    return 0;
}
