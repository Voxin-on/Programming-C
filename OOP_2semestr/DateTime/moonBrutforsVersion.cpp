#include "datetime.h"
#include <iostream>
#include <fstream>
#include <cstdio>
#include <ctime>

using namespace std;

int main(){
    int y,m,d;
    char sep;
    cin >> y >> sep >> m >> sep >> d;

    DateTime target(y, m, d);

    char filename[40];
    sprintf(filename, "dataMoon/moon%d.dat", y);

    ifstream file(filename);
    if (!file.is_open()) {
        return 1;
    }

    clock_t start = clock();

    file.ignore(1000, '\n');

    bool hasRise = false, hasCulmination = false, hasSet = false;
    DateTime riseTime, culminationTime, setTime;
    double prevEl = -999;
    double maxEl = -999;

    int ymd, hms;
    double t, r, el, az, fi, lg;

    while (file >> ymd >> hms >> t >> r >> el >> az >> fi >> lg){

        int fy = ymd/10000, fm = (ymd/100)%100, fd = ymd%100;
        DateTime cur(fy, fm, fd);

        if (cur<target) continue;
        else if (cur>target) break;

        int fh = hms/10000, fmin = (hms/100)%100, fsec = hms%100;
        DateTime dt(fy, fm, fd, fh, fmin, fsec);

        if (maxEl<el){
            maxEl=el;
            culminationTime=dt;
            hasCulmination=true;
        }

        if (prevEl<0 && el>0 && prevEl!=-999){
            riseTime=dt;
            hasRise=true;
        }

        if (prevEl>=0 && el<0 && prevEl!=-999){
            setTime=dt;
            hasSet=true;
        }

        prevEl = el;
    }

    clock_t end = clock();
    double time= (double)(end - start) / CLOCKS_PER_SEC;
    cout << "Time: " << time << " sec"<<endl;

    target.setFormat(DATE_ONLY);
    riseTime.setFormat(TIME_ONLY);
    setTime.setFormat(TIME_ONLY);
    culminationTime.setFormat(TIME_ONLY);

    cout<<"Date: "<<target<<endl;

    if (hasRise) cout << "Rise: " << riseTime;
    else cout << "Rise: not found"<<endl;
    if (hasCulmination) cout << "Culmination: " << culminationTime;
    else cout << "Culmination: not found"<<endl;
    if (hasSet) cout << "Set: " << setTime;
    else cout << "Set: not found"<<endl;

    file.close();

    return 0;
}