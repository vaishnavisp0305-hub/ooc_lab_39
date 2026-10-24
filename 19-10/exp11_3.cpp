// C++ program to demonstrate multiple catch blocks
#include <iostream>
using namespace std;

double division(int a, int b) {
    if (b == 0) {
        throw "Division by zero condition!";
    }
    return (double)a / b;
}

int main() {
    int x = 50;
    int y = 0;
    double z = 0;

    try {
        if (y == 0) {
            throw y;
        }

        z = division(x, y);
        cout << "Result: " << z << endl;
    }
    catch (int num) {
        cerr << "Exception: Divisor cannot be zero!" << endl;
    }
    catch (const char* msg) {
        cerr << "Exception: " << msg << endl;
    }
    catch (...) {
        cerr << "Unknown exception occurred!" << endl;
    }

    return 0;
}