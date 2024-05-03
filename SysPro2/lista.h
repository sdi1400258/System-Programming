#ifndef LISTA_H_
#define LISTA_H_

#include "Citizen.hpp"

class ListNode {
public:
    Citizen * data;
    ListNode * next;
};

/* Mia sindedemeni lista ektelesis
        ola iserxonte me pointer 
        ola prosthetonte stin arxi iii sto telos gia kaliteri apodosi*/

class lista {
protected:
    ListNode * first;
    ListNode * last;
    int size;
    ListNode * cur;

    /*
            dimiourgei kai arxikopoiei ton arxiko komvo , gia tin isagwgi toy sti lista
     */

    ListNode * Dimiourgia_Item_listas(Citizen * data) {
        ListNode * tmp;

        tmp = new ListNode();

        tmp->data = data;
        tmp->next = NULL;

        return tmp;
    }
public:

    lista()
    : first(NULL), last(NULL), size(0), cur(NULL) {
    }
    virtual ~lista();

    /* epistrefei 1 an i lista einai adeia*/

    inline int Empty_lista() {
        return (this->size == 0) ? 1 : 0;
    }

    /*epistrefei ton aritmo twn kombwn tis listas */

    inline int Get_Size_listas() {
        return this->size;
    }

    /* prosthetei stoixeio me pointer sto telos tis listas*/

    inline void Add_Item_Telos_listas(Citizen * item) {
        this->Add_lista_Item(item, this->size - 1);
    }

    /* prosthetei stoixio sti lista se #position tis listas
            An den dothei deuteri parametro me ti thesi, tote to stoixeio
            tha mpeis tin arxi tis listas
     */

    virtual void Add_lista_Item(Citizen * item, int position = 0);

    /* diagrafei stoixeio apo ti lista apo to position*/

    bool Remove_Item_listas(int position);

    /* 
            diagrafei auto to item tis lsitas
     */

    bool Remove_Auto_to_Item();

    /*epistrefei to stoixeio apo ti thesi position*/

    Citizen * Get_Item_listas(int position);

    /* get to proto stoixeio tis listas kai arxikopoiei tin epanalipsi */

    Citizen * Get_lista_protos();

    /* get to epomeno stoixeio tis listas apo tin epanalipsi.
            Ean den iparxei tote epistrefete to NULL*/

    Citizen * get_lista_epomenos();

    /* Diagrafei ola ta stoixeia apo ti lista , kai meta diagrafei kai ti lista */

    void Remove_All_Items();
};

#endif /* LISTA_H_*/
