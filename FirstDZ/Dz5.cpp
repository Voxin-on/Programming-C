#include <iostream>
#include <iomanip> 
using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    int k;
    cin >> k;

    double m,km, kil=1,mil=1;
    cout << "мили"<< setw(5) << "км" <<fixed<< setprecision(4)<< endl;

    while (k >= kil){
        m = kil / 1.609344;
        cout << m<<" "<<kil<<endl;
        if (m-int(m)>0.5) {
            km = mil * 1.609344;
            cout << mil << " " << km << endl;
            mil++;
        }
        kil++;
    }

    return 0;
}