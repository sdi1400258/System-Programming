#include "BloomFilter.h"
#include "HashFunctions.h"

int BloomFilter::filtersize = 24;

BloomFilter::BloomFilter() {
    data = new unsigned char[filtersize];
    
    for (int i=0;i<filtersize;i++) {
        data[i] = 0;
    }
}

BloomFilter::~BloomFilter() {
    delete [] data;
}

void BloomFilter::add(string str) {
    for (int i = 0; i < 16; i++) {
        int value = hash_i( (unsigned char*) str.c_str(), i) % getBits();

        int which_byte = 0;
        int j = 8;

        do {
            if (value >= j - 8 && value < j) {
                break;
            }
            j += 8;
            which_byte++;
        } while (1);

        int which_bit = value - which_byte * 8;

        unsigned char m = 1;
        unsigned char n = m << which_bit;

        data[which_byte] = data[which_byte] | n;
    }
}

bool BloomFilter::test(string str) const {
    for (int i = 0; i < 16; i++) {
        int value = hash_i((unsigned char*) str.c_str(), i) % getBits();

        int which_byte = 0;
        int j = 8;

        do {
            if (value >= j - 8 && value < j) {
                break;
            }
            j += 8;
            which_byte++;
        } while (1);

        int which_bit = value - which_byte * 8;

        unsigned char m = 1;
        unsigned char n = m << which_bit;

        unsigned char k = data[which_byte] & n;

        if (k == 0) {
            return false;
        }
    }
    return true;
}
