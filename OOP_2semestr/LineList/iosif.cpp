#include "lineListCycle.h"
#include <iostream>
#include <ctime>

using namespace std;

int main() {
    int numbers[7] = {1000, 5000, 10000, 50000, 100000, 500000, 1000000};
    int k = 2;

    for (int i = 0; i < 7; i++) {
        int N = numbers[i];
        LineList<int> list;

        list.insertFirst(1); 
        LineListElem<int>* last = list.getStart();

        for (int j = 2; j <= N; j++) {
            list.insertAfter(last, j);
            last = last->getNext();
        }

        clock_t start = clock();

        LineListElem<int>* curr = list.getStart();

        while (N > 1) {
            for (int step = 0; step < k - 2; step++) {
                curr = curr->getNext();
            }

            list.deleteAfter(curr);

            curr = curr->getNext();
            N--;
        }

        double time = (double)(clock() - start) / CLOCKS_PER_SEC;

        cout << "N: " << numbers[i] << " Answer: " << list.getStart()->getData() << " Time: " << time << endl;
    }

    return 0;
}