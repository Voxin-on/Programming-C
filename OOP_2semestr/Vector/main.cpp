#include "vector.h"
#include <iostream>
#include <ctime>

using namespace std;

void testBasic() {
    // Assignment
    Array a(1);
    Array b(5);
    for (int i = 0; i < 5; i++) b.insert(i);

    cout << "Size before assignment: " << a.getSize() << endl;

    a = b;
    cout << "After assignment:\n" << a;

    // Copy constructor
    Array c(a);
    cout << "Copy:\n" << c;

    // Index access
    cout << "Index access:" << endl;
    cout << a[4] << endl;
    a[4] = 20;
    cout << a[4] << endl;
}

void testModifyAndExceptions() {
    Array arr(5);
    for (int i = 0; i < 5; i++) arr.insert(i);

    // Insert
    cout << "Insert:" << endl;
    arr.insert(100);
    arr.insert(50, 2);
    cout << arr;

    // Remove
    cout << "Remove:" << endl;
    arr.remove(2);
    cout << arr;

    // Exception
    cout << "Exception test:" << endl;
    try {
        arr.remove(100);
    }
    catch (const ArrayException& e) {
        cout << "Error caught" << endl;
    }
}

double runIosif(int N, int k, int& result) {
    Array arr(N);

    for (int j = 0; j < N; j++) {
        arr.insert(j);
    }

    clock_t start = clock();

    int ind = 0;
    while (arr.getSize() > 1) {
        ind = (ind + k - 1) % arr.getSize();
        arr.remove(ind);
    }

    double time = (double)(clock() - start) / CLOCKS_PER_SEC;

    result = arr[0] + 1;
    return time;
}

int main() {
    // testBasic();
    // testModifyAndExceptions();

    int numbers[7] = {1000, 5000, 10000, 50000, 100000, 500000, 1000000};
    int k = 2;

    for (int i = 0; i < 7; i++) {
        int result;
        double time = runIosif(numbers[i], k, result);

        cout << "N: " << numbers[i]
             << " Answer: " << result
             << " Time: " << time << endl;
    }

    return 0;
}