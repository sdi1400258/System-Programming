#ifndef SESSION_PARENT_H
#define SESSION_PARENT_H

#include <fstream>
#include <sstream>
#include "Disease.hpp"
#include "Country.hpp"
#include "ChildInfo.h"
#include "dentro.h"
#include "TravelRequestList.h"

using namespace std;

class SessionParent {
public:
    BinaryTree<Country> countries;
    BinaryTree<Disease> diseases;
    BinaryTree<ChildInfo> children;
    int accepted, rejected;
    
    TravelRequestList books;
    
    SessionParent();
    
    SessionParent(const SessionParent& orig);
    
    ~SessionParent() ;
};

#endif /* SESSION_H */

