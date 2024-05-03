#ifndef COUNTRY_H
#define COUNTRY_H

#include <fstream>
#include <string>

#include "ChildInfo.h"

using namespace std;

class Country {
private:
    string name;
    ChildInfo * childInfo;
public:

    Country(string name) : name(name), childInfo(NULL) {
        
    }

    inline string GetKey() const {
        return name;
    }

    inline string GetName() const {
        return name;
    }

    inline void print(ostream & out = std::cout) const {
        if (&out == &std::cout) {
            if (childInfo == NULL) {
                out << name <<  " " << "- " << "NULL" << endl;
            } else {
                out << name <<  " " << "- " << childInfo->GetKey() << endl;
            }
        } else {
            out << name << endl;
        }
    }
    
    ChildInfo* GetChildInfo() const {
        return childInfo;
    }

    void SetChildInfo(ChildInfo* childInfo) {
        this->childInfo = childInfo;
    }

};

#endif /* COUNTRY_H */

