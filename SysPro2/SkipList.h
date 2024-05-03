#ifndef SKIPLIST_H
#define SKIPLIST_H

#include <stddef.h>
#include <climits>

#include "Citizen.hpp"
#include "Date.h"


class SkipListNode {
public:
    Citizen * citizen;
    Date date;

    SkipListNode ** next;
    
    int getValue() {
        if (citizen == NULL) {
            return INT_MAX;
        } else {
            return citizen->GetTautotita();
        }
    }
};

class SkipList {
protected:
    SkipListNode * first;
    SkipListNode * last;
    int size;
    SkipListNode * cur;
    int maxlevel;
    
    SkipListNode ** update;

    SkipListNode * Dimiourgia_Item_listas(Citizen * data, Date date) {
        SkipListNode * tmp;

        tmp = new SkipListNode();

        tmp->citizen = data;
        tmp->date = date;
        tmp->next = new  SkipListNode* [maxlevel];
        
        for (int i=0;i<maxlevel;i++) {
            tmp->next[i] = NULL;
        }

        return tmp;
    }
    
public:
    SkipList(int maxlevel);
    
    virtual ~SkipList();

    inline int Empty_lista() {
        return (this->size == 0) ? 1 : 0;
    }

    inline int Get_Size_listas() {
        return this->size;
    }

    virtual void Add_Item(Citizen * item, Date date = Date());

    virtual SkipListNode * Get_Item(int id);
    
    virtual int Count_Item(string country);
    
    virtual int Count_Item(string country, string d1, string d2);
    
    virtual int Count_Item_By_Age(int off, string country);
    
    virtual int Count_Item_By_Age(int off, string country, string d1, string d2);
    
    virtual SkipListNode * Print();
    
    virtual void Remove_Item(int id);
    

    virtual Citizen * Get_SkipList_protos();

    virtual Citizen * get_SkipList_epomenos();

    virtual void Remove_All_Items();

};

#endif /* SKIPLIST_H */

