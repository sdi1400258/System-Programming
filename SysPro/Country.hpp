#ifndef COUNTRY_H
#define COUNTRY_H

#include <string>

using namespace std;

class Country {
private:
    string name;
public:

    Country(string name) : name(name) {
        
    }

    inline string GetKey() const {
        return name;
    }

    inline string GetName() const {
        return name;
    }

    inline void print() const {
        cout << name <<  " " << endl;
        
        cout << endl;
    }
};

#endif /* COUNTRY_H */

