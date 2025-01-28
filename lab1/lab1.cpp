#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>
using namespace std;


extern "C" double function(double x, double a)
{
    double result, part1, part2, part3, part4;

    double A = a / 2;
    // |x - a / 2| + 1
    asm volatile(
        "fldl %2 \n"                // load a / 2
        "fldl %1 \n"                // load x
        "fsubp %%st(0), %%st(1) \n" // x - a / 2
        "fabs \n"                   // |x - a / 2|
        "fld1 \n"                   // load 1
        "faddp %%st(0), %%st(1) \n" // |x - a / 2| + 1
        "fstpl %0 \n"               // result in part1
        : "=m"(part1)               // записать в переменную
        : "m"(x), "m"(A)
        : "%st");

    // ln(|x - a / 2| + 1)
    part1 = log(part1);

    A = 3 * a;
    // tan((x * pi) / (3 * a))
    asm volatile(
        "fldl %1 \n" // load x
        "fldpi \n"   // load pi
        "fmulp \n"   // x * pi
        "fldl %2 \n" // load 3 * a
        "fdivrp \n"  // (x * pi) / (3 * a)
        "fsincos \n" // sin/cos(...)
        "fdivrp \n"  // tan(...)
        "fstpl %0 \n"
        : "=m"(part2)
        : "m"(x), "m"(A)
        : "%st");

    // x / a
    asm volatile(
        "fldl %1 \n" // load x
        "fldl %2 \n" // load a
        "fdivrp \n"  // x / a
        "fstpl %0 \n"
        : "=m"(part3)
        : "m"(x), "m"(a)
        : "%st");

    // 2 ^ (x / a)
    part4 = pow(2, part3);

    // result
    asm volatile(
        "fldl %1 \n" // load part1
        "fldl %2 \n" // load part2
        "faddp \n"   // part1 + part2
        "fldl %3 \n" // load part3
        "fldl %4 \n" // load part4
        "faddp \n"   // part3 + part4
        "fdivrp \n"  // (part1 + part2) / (part3 + part4)
        "fstpl %0 \n"
        : "=m"(result)
        : "m"(part1), "m"(part2), "m"(part3), "m"(part4)
        : "%st");

    cout << part1 << "   " << part2 << "   " << part3 << "   " << part4 << endl;
    return result;
}

int main()
{
    ofstream outputFile("result.txt");

    const double a = 2.0;
    double dh;
    cout << "Enter the step dh: ";
    cin >> dh;

    for (double X = -a; X <= a; X += dh)
    {
        double res = function(X, a);
        cout << X << "\t\t" << res << endl;
        outputFile << X << "\t\t" << res << endl;
    }

    outputFile.close();

    return 0;
}