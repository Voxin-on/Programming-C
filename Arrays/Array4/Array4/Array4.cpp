#include <iostream>
#include <locale.h>
using namespace std;
int main()
{
	setlocale(LC_ALL, "Russian");
	int n;
	cout << "Введите длинну массива: ";
	cin >> n;
	int lenGlobal=0;
	int lenCurrent = 0;
	int *A = new int[n];
	cout << "Введите числа массива: ";
	for (int i = 0; i < n; i++) { 
		cin >> A[i];
		if (A[i] == 0) {
			lenCurrent++;
			if (lenCurrent > lenGlobal) lenGlobal = lenCurrent;
		}
		else lenCurrent = 0;
	}
	cout <<"Результат: " << lenGlobal;
	return 0;
}