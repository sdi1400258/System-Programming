#ifndef DISEASE_H
#define DISEASE_H

#include <string>

#include "BloomFilter.h"
#include "SkipList.h"

using namespace std;

class Disease {
private:
    string name;
    BloomFilter bloom;
    SkipList s1;
    SkipList s2;
public:
    Disease(string name, int levels = 20) : name(name), s1(20), s2(20) {
    }

    inline string GetKey() const {
        return name;
    }

    inline string GetName() const {
        return name;
    }

    inline void print(ostream & out = std::cout) const {
        out << name << endl;
    }

    inline BloomFilter & getBloomFilter() {
        return bloom;
    }
    
    inline SkipList & getSkipList(bool vaccinated) {
        if (vaccinated) {
            return s1;
        } else {
            return s2;
        }
    }

};



#endif /* DISEASE_H */

