#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "datevacc.h"

using namespace std;

void datevacc_test() {
    string dv, dt;

    cout << "Type date of vaccination (DD-MM-YYYY) " << endl;
    cin >> dv;

    cout << "Type date of traveling (DD-MM-YYYY) " << endl;
    cin >> dt;

    string vacc;
    vacc = datevacc(dv, dt);
    cout << vacc << endl;

}

bool datevacc(string datev, string datet) {
    string dayv, monthv, yearv, dayt, montht, yeart;

    dayv = datev.substr(0, 2);
    monthv = datev.substr(3, 2);
    yearv = datev.substr(6, 4);

    dayt = datet.substr(0, 2);
    montht = datet.substr(3, 2);
    yeart = datet.substr(6, 4);

    int formatv, formatt, idayv, imonthv, iyearv, idayt, imontht, iyeart, month = 30, year = 365, acc = 180, sub, wr = 0;

    idayv = atoi(dayv.c_str());
    imonthv = atoi(monthv.c_str());
    iyearv = atoi(yearv.c_str());

    idayt = atoi(dayt.c_str());
    imontht = atoi(montht.c_str());
    iyeart = atoi(yeart.c_str());

    formatv = idayv + (month * imonthv) + (year * iyearv);
    formatt = idayt + (month * imontht) + (year * iyeart);

//    cout << formatv << endl;
//    cout << formatt << endl;

    sub = formatt - formatv;

//    cout << sub << endl;

    if (sub <= acc && sub > wr) {
        return true;
    } else if (sub > acc) {
        return false;
    } else if (sub < wr) {
        return false;
    } else if (sub == wr) {
        return true;
    }

    return false;

}