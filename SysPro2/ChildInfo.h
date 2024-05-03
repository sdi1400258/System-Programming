#ifndef CHILDINFO_H
#define CHILDINFO_H

#include <sstream>
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

class ChildInfo {
private:
    int id;
    string pipe_south; // towards child
    string pipe_north; // towards parent
    int northfd, southfd;
public:
    static pid_t * pids;
    static char * buffer;
    static int buffersize;

    ChildInfo(int id) : id(id), northfd(-1), southfd(-1) {
        stringstream ss1;  
        ss1 << "pipe_south_" << id << ".fifo"; 
        ss1 >> pipe_south;
        
        
        stringstream ss2;  
        ss2 << "pipe_north_" << id << ".fifo"; 
        ss2 >> pipe_north;
    }

    inline int getID() const {
        return id;
    }
    
    inline string GetKey() const {
        string str;
        stringstream ss;  
        ss << id; 
        ss >> str;
        return str;
    }

    inline string GetName() const {
        string str;
        stringstream ss;  
        ss << id; 
        ss >> str;
        return str;
    }

    inline void print(ostream & out = std::cout) const {
        out << "Child info: " << id <<  ":" << " " << pipe_north << " " << pipe_south <<  endl;
    }
    
    inline const string & getNorthPipe() const{
        return pipe_north;
    }
    
    inline const string & getSouthPipe() const {
        return pipe_south;
    }
    
    inline int GetNorthfd() const {
        return northfd;
    }

    inline void SetNorthfd(int northfd) {
        this->northfd = northfd;
    }

    inline int GetSouthfd() const {
        return southfd;
    }

    inline void SetSouthfd(int southfd) {
        this->southfd = southfd;
    }

};

#endif /* CHILDINFO_H */

