#ifndef TRAVELREQUEST_LISTA_H_
#define TRAVELREQUEST_LISTA_H_

#include "TravelRequest.hpp"

class TravelRequestListNode{ 
public:
    TravelRequest * data;
    TravelRequestListNode * next;
};

/* Mia sindedemeni TravelRequestList ektelesis
        ola iserxonte me pointer 
        ola prosthetonte stin arxi iii sto telos gia kaliteri apodosi*/

class TravelRequestList {
protected:
    TravelRequestListNode * first;
    TravelRequestListNode * last;
    int size;
    TravelRequestListNode * cur;

    /*
            dimiourgei kai arxikopoiei ton arxiko komvo , gia tin isagwgi toy sti TravelRequestList
     */

    TravelRequestListNode * Dimiourgia_Item_TravelRequestLists(TravelRequest * data) {
        TravelRequestListNode * tmp;

        tmp = new TravelRequestListNode();

        tmp->data = data;
        tmp->next = NULL;

        return tmp;
    }
public:

    TravelRequestList()
    : first(NULL), last(NULL), size(0), cur(NULL) {
    }
    virtual ~TravelRequestList();

    /* epistrefei 1 an i TravelRequestList einai adeia*/

    inline int Empty_TravelRequestList() {
        return (this->size == 0) ? 1 : 0;
    }

    /*epistrefei ton aritmo twn kombwn tis TravelRequestLists */

    inline int Get_Size_TravelRequestLists() {
        return this->size;
    }

    /* prosthetei stoixeio me pointer sto telos tis TravelRequestLists*/

    inline void Add_Item_Telos_TravelRequestLists(TravelRequest * item) {
        this->Add_TravelRequestList_Item(item, this->size - 1);
    }

    /* prosthetei stoixio sti TravelRequestList se #position tis TravelRequestLists
            An den dothei deuteri parametro me ti thesi, tote to stoixeio
            tha mpeis tin arxi tis TravelRequestLists
     */

    virtual void Add_TravelRequestList_Item(TravelRequest * item, int position = 0);

    /* diagrafei stoixeio apo ti TravelRequestList apo to position*/

    bool Remove_Item_TravelRequestLists(int position);

    /* 
            diagrafei auto to item tis lsitas
     */

    bool Remove_Auto_to_Item();

    /*epistrefei to stoixeio apo ti thesi position*/

    TravelRequest * Get_Item_TravelRequestLists(int position);

    /* get to proto stoixeio tis TravelRequestLists kai arxikopoiei tin epanalipsi */

    TravelRequest * Get_TravelRequestList_protos();

    /* get to epomeno stoixeio tis TravelRequestLists apo tin epanalipsi.
            Ean den iparxei tote epistrefete to NULL*/

    TravelRequest * get_TravelRequestList_epomenos();

    /* Diagrafei ola ta stoixeia apo ti TravelRequestList , kai meta diagrafei kai ti TravelRequestList */

    void Remove_All_Items();
};

#endif /* LISTA_H_*/
