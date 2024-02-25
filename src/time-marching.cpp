#include <iostream>
#include <cmath>
#include <format>
#include "array.h"
#include "allocate.h"
#include "io.h"

using namespace std;

void setInitialSolution(int n, double*& y, double*& u)
{
    for (int i=0; i<n; i++) {
        u[i] = y[i] + sin(M_PI*y[i]);
    } 
}

/* Function to compute local time step based on stalibity constraints of scalar
 * diffusion equation with forward difference in time and central difference in 
 * space:
 *
 *      VNN = \frac{dt}{Re (dy)^2}
 *
 * Parameters:
 * -----------
 *  int      n   ... size of finite difference array;
 *  double   Re  ... Reynolds number of the simulation;
 *  double   VNN ... von Neumann stability number (upper bound of 0.5 here);
 *  double*& dy  ... local grid spacing;
 *  double*& dt  ... local time step.
 */
void computeLocalDeltat(int n, double Re, double VNN, double*& dy, double*& dt)
{
    // Compute local dt;
    for (int i=0; i<(n-1); i++) {
        dt[i] = VNN*Re*(pow(dy[i],2.0));
    }
    //printArray(n-1, dt);
}

/* Function to advance in time the scalar diffusion non-dimensionalized equation,
 * updates n+1 array based on n, Re, local time step and local grid spacing.
 *
 * Parameters:
 * -----------
 *  int      n    ... size of discretized domain and solution;
 *  double   Re   ... simulation Reynolds number;
 *  double*& dt   ... local time step;
 *  double*& dy   ... local grid spacing;
 *  double*& u    ... n -th time step solution;
 *  double*& unew ... n+1 -th time step solution, to be updated based on n.
 */
void advanceInTime(
    int n, double Re, 
    double*& dt, double*& dy, double*& u, double*& unew
)
{
    for (int i=1; i<(n-1); i++) {
        unew[i] = u[i] + \
            (dt[i]/Re)*((2/(dy[i]+dy[i-1])) *
                    ((u[i+1]-u[i])/dy[i]-(u[i]-u[i-1])/dy[i-1]));
    }
    // Boundary conditions:
    unew[0]   = 0;
    unew[n-1] = 1;
}

/* Function to compute L2 and Linfinity norms of time-marching solution conver-
 * gence.
 *
 * Parameters:
 * -----------
 *  int n           ... size of discretized domain;
 *  int it          ... current iteration;
 *  double*& u      ... q -th time solution;
 *  double*& unew   ... q+1 -th time solution;
 *  double*& delta  ... local delta of q+1 - q, size n;
 *  double*& L2     ... L2 vector, size itmax;
 *  double*& Linfty ... Linfinity vector, size itmax.
 */
void computeErrorNorms(
    int n, int it,
    double*& u, double*& unew, 
    double*& delta, double*& L2, double*& Linfty
)
{
    double L2inst = 0.0;
    double Linftyinst;
    // Compute delta form and contributions to L2:
    for (int i=0; i<n; i++) {
        delta[i] = abs(unew[i] - u[i]);
        L2inst += pow(delta[i], 2.0);
    }
    L2inst = sqrt(L2inst);
    L2[it-1] = L2inst;

    // Compute Linfty norm:
    Linftyinst = delta[0];
    for (int i=1; i<n; i++) {
        if (delta[i] > Linftyinst) {
            Linftyinst = delta[i];
        }
    }
    Linfty[it-1] = Linftyinst;
}

int main() 
{
    // Parameters:
    int n = 101;
    double *y, *dy, *dt, *u0, *u, *unew, *L2, *Linfty;
    double *delta;
    double Re = 1.0;
    double VNN = 0.6;
    double t;
    double trest = 1.0; 
    double tmax  = 4.0;
    int it = 1;
    int itrest;
    int itmax = 80001;
    string fname;

    // Initialize arrays:
    linSpace(0.0, 1.0, n, y);
    fileName("time-marching/VNN_06", "y", 0, fname);
    writeBinaryArray(fname, n, y);
    arrayZeros(n-1, dt);
    arrayZeros(n, u0);
    arrayZeros(n, u);
    arrayZeros(n, unew);
    arrayZeros(n, delta);

    // Initial parametrization:
    // 1. initial solution;
    // 2. array spacing computation;
    // 3. minimal dt for time-accurate solution;
    setInitialSolution(n, y, u0);
    spacingArray(n, y, dy);
    computeLocalDeltat(n, Re, VNN, dy, dt);
    //cout << dt << endl;
    fileName("time-marching/VNN_06", "flow", 0, fname);
    writeBinaryArray(fname, n, u0);
    
    // Advance in time:
    arrayZeros(itmax-2, L2);
    arrayZeros(itmax-2, Linfty);
    copyArray(n, u0, u);
    while (it < itmax) {
        advanceInTime(n, Re, dt, dy, u, unew);
        // Error norms:
        computeErrorNorms(n, it, u, unew, delta, L2, Linfty);
        copyArray(n, unew, u);
        if (it % 10000 == 0) {
            printArray(n, u);
            fileName("time-marching/VNN_06", "flow", it, fname);
            writeBinaryArray(fname, n, u);
        }
        it++;
    }

    // Write error norm results
    fileName("time-marching/VNN_06", "L2", itmax-1, fname);
    writeBinaryArray(fname, itmax-2, L2);
    fileName("time-marching/VNN_06", "Linfty", itmax-1, fname);
    writeBinaryArray(fname, itmax-2, Linfty);

    // Deallocate memory:
    deallocate1d(y);
    deallocate1d(dy);
    deallocate1d(dt);
    deallocate1d(u0);
    deallocate1d(u);
    deallocate1d(unew);
    deallocate1d(delta);
    deallocate1d(L2);
    deallocate1d(Linfty);
    return 0;
}
