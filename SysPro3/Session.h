#ifndef SESSION_H
#define SESSION_H

#include <string>
#include <sstream>
#include "Disease.hpp"
#include "Citizen.hpp"
#include "Country.hpp"
#include "dentro.h"
#include "File.h"

class Session {
public:
    BinaryTree<Citizen> citizens;
    BinaryTree<Country> countries;
    BinaryTree<Disease> diseases;
    BinaryTree<File> files;
    int accepted, rejected;

    static int signo;

    Session() : accepted(0), rejected(0) {

    }

    Session(const Session& orig) {
        printf("ERROR: session is not copyable \n");
        exit(1); // cannot copy session
    }

    void log();

    void loadFromSocket(string sourceDirectory, int clientfd);

    void loadFromBST(string sourceDirectory, int clientfd);
};

#endif /* SESSION_H */

