#ifndef FILE_H
#define FILE_H

#include <string>

using namespace std;

class File {
public:
    string filename;

    File();
    File(const File& orig);
    virtual ~File();

    File(string filename) : filename(filename) {
    }

    
    inline string GetKey() const {
        return filename;
    }


private:


};

#endif /* FILE_H */

