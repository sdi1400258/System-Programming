#include <iostream>
#include "TravelRequestList.h"

TravelRequestList::~TravelRequestList() {
    TravelRequestListNode * cur, * next;

    cur = this->first;
    while (cur) {
        next = cur->next;

        delete cur;
        cur = next;
    }

    return;
}

void TravelRequestList::Add_TravelRequestList_Item(TravelRequest * item, int position) {
    TravelRequestListNode * tmp, * tmp2;
    int i;

    tmp2 = Dimiourgia_Item_TravelRequestLists(item);
    if (position == 0) {
        //stin arxi
        tmp = this->first;
        this->first = tmp2;
        this->first->next = tmp;
        this->size++;
    } else if (position >= this->size - 1) {
        //teleutaia thesi, position
        tmp = this->last;
        this->last = tmp2;
        if (tmp)
            tmp->next = this->last;
        if (!this->first)
            this->first = this->last;
        this->size++;
    } else {
        //kapou sti mesi
        i = 0;
        tmp = this->first;
        while (i++<position)
            tmp = tmp->next;

        if (tmp) {
            if (tmp == this->last) {
                this->last->next = tmp2;
                this->last = tmp2;
            } else {
                tmp2->next = tmp->next;
                tmp->next = tmp2;
            }
            this->size++;
        }
    }

    return;

}

bool TravelRequestList::Remove_Item_TravelRequestLists(int position) {
    TravelRequestListNode *tmp, * next, * prev = NULL;
    int i = 0;

    if (position >= this->size)
        //ektos oriwn
        return false;

    if (position == 0) {
        next = this->first->next;
        //den diagrafw ton sindemeno komvo
        delete this->first;

        if (this->first == this->last)
            this->last = next;
        this->first = next;
        this->size--;

        return true;
    }

    tmp = this->first;
    while (i < position) {
        prev = tmp;
        tmp = prev->next;
        i++;
    }

    prev->next = tmp->next;
    delete tmp;

    this->size--;

    return true;

}

bool TravelRequestList::Remove_Auto_to_Item() {
    TravelRequestListNode * prev = NULL;
    TravelRequestListNode * tmp;

    if (this->cur == NULL)
        return false;

    tmp = this->first;
    while (tmp) {
        if (tmp == this-> cur) {
            if (prev)
                prev->next = this->cur->next;
            if (tmp == this->first)
                this->first = this->cur->next;
            if (tmp == this->last)
                this->last = prev;
            delete this->cur;
            this->size--;
            return true;
        }
        prev = tmp;
        tmp = tmp->next;
    }

    return false;

}

TravelRequest * TravelRequestList::Get_Item_TravelRequestLists(int position) {
    TravelRequestListNode * tmp;
    int i = 0;

    if (position >= this->size)
        //ektos orion
        return NULL;

    if (position == 0)
        return this->first->data;

    if (position == this->size - 1)
        return this->last->data;

    tmp = this->first;
    while (i < position) {
        tmp = tmp->next;
        i++;
    }

    return tmp->data;

}

TravelRequest * TravelRequestList::Get_TravelRequestList_protos() {
    this->cur = this->first;

    if (!this->first)
        return NULL;

    return this->first->data;
}

TravelRequest * TravelRequestList::get_TravelRequestList_epomenos() {
    if (this->cur == NULL)
        return NULL;

    this->cur = this->cur->next;

    if (this->cur)
        return this->cur->data;
    else
        return NULL;

}

void TravelRequestList::Remove_All_Items() {
    TravelRequestListNode * tmp = this->first;
    while (tmp != NULL) {
        delete tmp->data;
        tmp = tmp->next;
    }
}

