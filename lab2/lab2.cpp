#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>
using namespace std;


double f(double x)
{
    return sin(100 * x) / x;
}

extern "C" double left_rectangle_integral(double (*func)(double), double low, double a, int n)
{
    double h = (a - low) / n;
    double integral = 0.0, var = 100.0;

    for (int i = 0; i < n; ++i)
    {
        double x = low + i * h;
        double y = 0.0, part = 0.0;

        asm volatile(
            "fldl %1 \n"  // load x
            "fldl %2 \n"  // load 100.0
            "fmulp \n"    // x * 100.0
            "fsin \n"     // sin(x * 100.0)
            "fldl %1 \n"  // load x
            "fdivrp \n"   // sin(x * 100.0) / x
            "fstpl %0 \n" // save result in y
            : "=m"(y)
            : "m"(x), "m"(var)
            : "%st");

        asm volatile(
            "fldl %1 \n"  // load y
            "faddl %0 \n" // integral + y
            "fstpl %0 \n" // save result in integral
            : "=m"(part)
            : "m"(y));

        integral += part;
    }

    integral *= h;

    return integral;
}

int main()
{
    ofstream outputFile("result.txt");

    const int max_steps = 10000, step_increment = 10;

    const double low = 0.0001, a = 3.0;
    double steps[max_steps / step_increment], integrals[max_steps / step_increment];

    for (int i = 0, n = step_increment; n <= max_steps; ++i, n += step_increment)
    {
        steps[i] = n;
        integrals[i] = left_rectangle_integral(f, low, a, n);
    }

    for (int i = 0; i < 1000; ++i)
    {
        outputFile << steps[i] << "\t\t" << integrals[i] << endl;
    }

    outputFile.close();
}