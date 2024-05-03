#include <iostream>
#include "lista.h"

lista::~lista() {
    ListNode * cur, * next;

    cur = this->first;
    while (cur) {
        next = cur->next;

        delete cur;
        cur = next;
    }

    return;
}

void lista::Add_lista_Item(Citizen * item, int position) {
    ListNode * tmp, * tmp2;
    int i;

    tmp2 = Dimiourgia_Item_listas(item);
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

bool lista::Remove_Item_listas(int position) {
    ListNode *tmp, * next, * prev = NULL;
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

bool lista::Remove_Auto_to_Item() {
    ListNode * prev = NULL;
    ListNode * tmp;

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

Citizen * lista::Get_Item_listas(int position) {
    ListNode * tmp;
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

Citizen * lista::Get_lista_protos() {
    this->cur = this->first;

    if (!this->first)
        return NULL;

    return this->first->data;
}

Citizen * lista::get_lista_epomenos() {
    if (this->cur == NULL)
        return NULL;

    this->cur = this->cur->next;

    if (this->cur)
        return this->cur->data;
    else
        return NULL;

}

void lista::Remove_All_Items() {
    ListNode * tmp = this->first;
    while (tmp != NULL) {
        delete tmp->data;
        tmp = tmp->next;
    }
}

