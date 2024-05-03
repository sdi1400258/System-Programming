
#ifndef BLOOMFILTER_H
#define BLOOMFILTER_H

#include <string>

using namespace std;

class BloomFilter {
public:
    static int filtersize; // bytes

    BloomFilter();
    virtual ~BloomFilter();
    
    inline int getBits() const {
        return filtersize*8;
    }
    
    void add(string str);
    bool test(string str) const;
private:
    unsigned char * data;
};



#endif /* BLOOMFILTER_H */

