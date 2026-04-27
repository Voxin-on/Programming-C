#include "field.h"
#include <locale.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void testHorizontalWin() {
    Field field(true);
    int moves[] = {1, 1, 2, 2, 3, 3, 4};
    
    for (int col : moves)
        field.makeTurn(col);

    if (field.isWon(true)) 
        cout << "Test Horizontal Win: pass" << endl;
    else 
        cout << "Test Horizontal Win: fail" << endl;
}

void testDiagonallWin() {
    Field field(true);
    int moves[] = {1, 2, 2, 3, 3, 4, 3, 4, 4, 7, 4};
    
    for (int col : moves)
        field.makeTurn(col);

    if (field.isWon(true)) 
        cout << "Test Diagonal Win: pass" << endl;
    else 
        cout << "Test Diagonal Win: fail" << endl;
}

void runRandomTest(int iterations) {
    srand(time(NULL));
    for (int t = 0; t < iterations; t++) {
        Field field(rand() % 2);
        
        while (!field.isOver()) {
            int randomCol = (rand() % FIELD_WIDTH) + 1;
            field.makeTurn(randomCol);
        }
    }
    cout << "Successfully completed: " << iterations << " iterations" << endl;
}

int main(void){
    setlocale(LC_ALL, "Russian");

    testHorizontalWin();
    testDiagonallWin();
    runRandomTest(1000);

    Field field(true);
    while (!field.isOver()){
        field.print();
        cout<<"Ходит "<<
        (field.isRedTurnNow() ? "красный" : "желтый")<<
        " игрок, введите ход (1-7)"<<endl;
        int column; cin>>column;   
        field.makeTurn(column);
    }
    field.printResult();
    
    return 0;
}