#include "SkipList.h"
#include "datecmp.h"

SkipList::SkipList(int maxlevel) : maxlevel(maxlevel) {
    Date date;
    first = Dimiourgia_Item_listas(NULL, date);
    last = Dimiourgia_Item_listas(NULL, date);

    for (int i = 0; i < maxlevel; i++) {
        first->next[i] = last;
    }

    update = new SkipListNode*[maxlevel];

    for (int i = 0; i < maxlevel; i++) {
        update[i] = NULL;
    }
}

SkipList::~SkipList() {
    SkipListNode * cur, * next;

    cur = this->first;

    while (cur) {
        next = cur->next[0];

        delete [] cur->next;
        delete cur;
        cur = next;
    }

    delete [] update;

    return;
}

void SkipList::Add_Item(Citizen * item, Date date) {
    SkipListNode * tmp = this->first;

    for (int i = maxlevel - 1; i >= 0; i--) {
        while (tmp->next[i]->getValue() < item->GetTautotita()) {
            tmp = tmp->next[i];
        }

        update[i] = tmp;
    }

    tmp = tmp->next[0];

    if (tmp->getValue() == item->GetTautotita()) {
        return;
    }

    int lvl = 1 + rand() % maxlevel;

    SkipListNode * node = Dimiourgia_Item_listas(item, date);

    for (int i = 0; i < lvl; i++) {
        node->next[i] = update[i]->next[i];
        update[i]->next[i] = node;
    }
}

void SkipList::Remove_Item(int id) {
    SkipListNode * tmp = this->first;

    for (int i = maxlevel - 1; i >= 0; i--) {
        while (tmp->next[i]->getValue() < id) {
            tmp = tmp->next[i];
        }

        update[i] = tmp;
    }

    tmp = tmp->next[0];

    if (tmp->getValue() != id) {
        return;
    }

    for (int i = 0; i < maxlevel; i++) {
        if (update[i]->next[i]->getValue() != id) {
            break;
        }
        update[i]->next[i] = tmp->next[i];
    }

    delete [] tmp->next;
    delete tmp;
}

SkipListNode * SkipList::Get_Item(int id) {
    SkipListNode * tmp = this->first;

    for (int i = maxlevel - 1; i >= 0; i--) {
        while (tmp->next[i]->getValue() < id) {
            tmp = tmp->next[i];
        }
        update[i] = tmp;
    }

    tmp = tmp->next[0];

    if (tmp->getValue() == id) {
        return tmp;
    } else {
        return NULL;
    }
}

int SkipList::Count_Item(string country) {
    SkipListNode * cur, * next;

    int count = 0;

    cur = this->first;

    while (cur) {
        next = cur->next[0];

        if (cur != first && cur != last) {
            if (cur->citizen->GetCountry() == country) {
                count++;
            }
        }

        cur = next;
    }

    return count;
}

int SkipList::Count_Item(string country, string d1, string d2) {
    SkipListNode * cur, * next;

    int count = 0;

    cur = this->first;

    while (cur) {
        next = cur->next[0];

        if (cur != first && cur != last) {
            string d3 = cur->date.get_str("%d-%m-%Y");
            if (cur->citizen->GetCountry() == country && datecmp(d3, d1, d2) == true) {
                count++;
            }
        }

        cur = next;
    }

    return count;
}

int SkipList::Count_Item_By_Age(int off, string country) {
    SkipListNode * cur, * next;

    int count = 0;

    cur = this->first;

    while (cur) {
        next = cur->next[0];

        if (cur != first && cur != last) {
            if (cur->citizen->GetCountry() == country) {
                int c_off = cur->citizen->GetAge()/20;
                if (c_off > 3) {
                    c_off = 3;
                }
                
                if (c_off == off) {
                    count++;
                }
            }
        }

        cur = next;
    }

    return count;
}

int SkipList::Count_Item_By_Age(int off, string country, string d1, string d2) {
    SkipListNode * cur, * next;

    int count = 0;

    cur = this->first;

    while (cur) {
        next = cur->next[0];

        if (cur != first && cur != last) {
            string d3 = cur->date.get_str("%d-%m-%Y");
            if (cur->citizen->GetCountry() == country && datecmp(d3, d1, d2) == true) {
                int c_off = cur->citizen->GetAge()/20;
                if (c_off > 3) {
                    c_off = 3;
                }
                
                if (c_off == off) {
                    count++;
                }
            }
        }

        cur = next;
    }

    return count;
}

SkipListNode * SkipList::Print() {
    SkipListNode * cur, * next;

    cur = this->first;

    while (cur) {
        next = cur->next[0];

        if (cur != first && cur != last) {
            cur->citizen->print();
        }

        cur = next;
    }

    return NULL;
}

Citizen * SkipList::Get_SkipList_protos() {
    this->cur = this->first->next[0];

    if (this->cur->getValue() == INT_MAX) {
        return NULL;
    }

    return cur->citizen;
}

Citizen * SkipList::get_SkipList_epomenos() {
    if (this->cur == NULL)
        return NULL;

    this->cur = this->cur->next[0];

    if (this->cur->getValue() == INT_MAX) {
        return NULL;
    } else {
        return this->cur->citizen;
    }
}

void SkipList::Remove_All_Items() {
    SkipListNode * tmp = this->first->next[0];
    while (tmp != NULL) {
        delete tmp->citizen;
        tmp = tmp->next[0];
    }
}


