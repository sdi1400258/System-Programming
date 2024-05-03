#ifndef CITIZEN_HPP
#define CITIZEN_HPP

#include <iostream>
#include <string>

using namespace std;

class Citizen {
private:
    int tautotita;
    string firstname;
    string lastname;
    string country;
    int age;
public:

    Citizen(int tautotita, string firstname, string lastname, string country, int age) : tautotita(tautotita), firstname(firstname), lastname(lastname), country(country), age(age) {
    }
    
    inline int GetAge() const {
        return age;
    }
    
    inline string GetKey() const {
        char buffer[1000];
        sprintf(buffer, "%d", tautotita);
        string t = buffer;
        return t;
    }

    inline string GetCountry() const {
        return country;
    }

    inline string GetFirstname() const {
        return firstname;
    }

    inline string GetLastname() const {
        return lastname;
    }

    inline int GetTautotita() const {
        return tautotita;
    }
    
    inline void print() const {
        cout << tautotita << " " << firstname << " " << lastname << " " << country << " " << age << endl;;
    }
};

#endif /* EPISKEPTIS_HPP_ */