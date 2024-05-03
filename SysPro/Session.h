#ifndef SESSION_H
#define SESSION_H

#include "dentro.h"
#include "Disease.hpp"
#include "Citizen.hpp"
#include "Country.hpp"


class Session {
public:
    BinaryTree<Citizen> citizens;
    BinaryTree<Country> countries;
    BinaryTree<Disease> diseases;
    
    Session() {
        
    }
    
    Session(const Session& orig) {
        printf("ERROR: session is not copyable \n");
        exit(1); // cannot copy session
    }
    
};

#endif /* SESSION_H */

