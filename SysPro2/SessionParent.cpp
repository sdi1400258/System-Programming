#include <iostream>
#include <sstream>
#include <fstream>

#include "SessionParent.h"

using namespace std;


SessionParent::SessionParent() : accepted(0), rejected(0) {

}

SessionParent::SessionParent(const SessionParent& orig) {
    printf("ERROR: session is not copyable \n");
    exit(1); // cannot copy session
}

SessionParent::~SessionParent() {
    cout << "writing log " << endl;

    string mypid;

    stringstream ss;

    ss << getpid();

    ss >> mypid;

    string filename = "log_file." + mypid;

    ofstream fp(filename.c_str());

    countries.print(fp);

    fp << "TOTAL: " << accepted + rejected << endl;
    fp << "ACCEPTED: " << accepted << endl;
    fp << "REJECTED: " << rejected << endl;
}