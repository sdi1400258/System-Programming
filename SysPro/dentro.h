#ifndef DENTRO_H
#define DENTRO_H

#include <iostream>
#include <string>

#include "Disease.hpp"
#include "Country.hpp"

using namespace std;

#define OBJECT_DENTRO_MESSAGES 0

// 1. => template 

template <typename T>
class BinaryTree {

    struct Node {
        string key;
        T * data;
        Node * left;
        Node * right;

        Node(const string key, T * data, Node * left = NULL, Node * right = NULL) : key(key), data(data), left(left), right(right) {
#if(OBJECT_DENTRO_MESSAGES)
            cout << "Dentro::Node[" << this << "] Node me dimiourgo: " << key << " dimiourgithike " << endl;
#endif
        }
    };

    Node * root;
    int counter;

    void Nodeprint(Node * n) {
        if (n != NULL) {
            Nodeprint(n->left);
            n->data->print();
            counter++;
            Nodeprint(n->right);
        }
    }

    void processTreeForVaccineStatus(Node * tn, int id) {
        if (tn != NULL) {
            processTreeForVaccineStatus(tn->left, id);

            Disease * d = dynamic_cast<Disease*> (tn->data);

            if (d == NULL) {
                return;
            }

            SkipListNode * sn_1 = d->getSkipList(true).Get_Item(id);
            SkipListNode * sn_2 = d->getSkipList(false).Get_Item(id);

            bool t1 = sn_1 != NULL;
            bool t2 = sn_2 != NULL;

            if (t1) {
                cout << d->GetKey() << ": vaccinated at " << sn_1->date.get_str() << endl;
            } 
            
            if (t2) {
                cout << d->GetKey() << ": not vaccinated " << endl;
            }

            processTreeForVaccineStatus(tn->right, id);
        }
    }

    void processTreeForPopulationStatus(Node * tn, SkipList & sl1, SkipList & sl2) {
        if (tn != NULL) {
            processTreeForPopulationStatus(tn->left, sl1, sl2);

            Country * c = dynamic_cast<Country*> (tn->data);

            if (c == NULL) {
                return;
            }

            int vaccinated_population = sl1.Count_Item(c->GetName());

            int population = sl1.Count_Item(c->GetName()) + sl2.Count_Item(c->GetName());

            float percent = vaccinated_population / (float) population * 100;

            cout << c->GetKey() << " " << vaccinated_population << " " << population << " " << percent << "%" << endl;

            processTreeForPopulationStatus(tn->right, sl1, sl2);
        }
    }

    void processTreeForPopulationStatus(Node * tn, SkipList & sl1, SkipList & sl2, string country) {
        if (tn != NULL) {
            processTreeForPopulationStatus(tn->left, sl1, sl2, country);

            Country * c = dynamic_cast<Country*> (tn->data);

            if (c == NULL) {
                return;
            }

            if (c->GetKey() == country) {
                int vaccinated_population = sl1.Count_Item(c->GetName());

                int population = sl1.Count_Item(c->GetName()) + sl2.Count_Item(c->GetName());

                float percent = vaccinated_population / (float) population * 100;

                cout << c->GetKey() << " " << vaccinated_population << " " << population << " " << percent << "%" << endl;
            }

            processTreeForPopulationStatus(tn->right, sl1, sl2, country);
        }
    }

    void processTreeForPopulationStatus(Node * tn, SkipList & sl1, SkipList & sl2, string d1, string d2) {
        if (tn != NULL) {
            processTreeForPopulationStatus(tn->left, sl1, sl2, d1, d2);

            Country * c = dynamic_cast<Country*> (tn->data);

            if (c == NULL) {
                return;
            }

            int vaccinated_population = sl1.Count_Item(c->GetName(), d1, d2);

            int population = sl1.Count_Item(c->GetName()) + sl2.Count_Item(c->GetName());

            float percent = vaccinated_population / (float) population * 100;

            cout << c->GetKey() << " " << vaccinated_population << " " << population << " " << percent << "%" << endl;

            processTreeForPopulationStatus(tn->right, sl1, sl2, d1, d2);
        }
    }

    void processTreeForPopulationStatus(Node * tn, SkipList & sl1, SkipList & sl2, string d1, string d2, string country) {
        if (tn != NULL) {
            processTreeForPopulationStatus(tn->left, sl1, sl2, d1, d2, country);

            Country * c = dynamic_cast<Country*> (tn->data);

            if (c == NULL) {
                return;
            }

            if (c->GetKey() == country) {
                int vaccinated_population = sl1.Count_Item(c->GetName(), d1, d2);

                int population = sl1.Count_Item(c->GetName()) + sl2.Count_Item(c->GetName());

                float percent = vaccinated_population / (float) population * 100;

                cout << c->GetKey() << " " << vaccinated_population << " " << population << " " << percent << "%" << endl;
            }

            processTreeForPopulationStatus(tn->right, sl1, sl2, d1, d2, country);
        }
    }

    // ----------------------------------------------------------

    void processTreeForPopulationStatusByAge(Node * tn, SkipList & sl1, SkipList & sl2) {
        if (tn != NULL) {
            processTreeForPopulationStatusByAge(tn->left, sl1, sl2);

            Country * c = dynamic_cast<Country*> (tn->data);

            if (c == NULL) {
                return;
            }

            for (int off = 0; off < 4; off++) {
                int vaccinated_population = sl1.Count_Item_By_Age(off, c->GetName());
                int population = sl1.Count_Item_By_Age(off, c->GetName()) + sl2.Count_Item_By_Age(off, c->GetName());
                float percent = vaccinated_population / (float) population * 100;
                cout << c->GetKey() << " ";

                if (off == 0) {
                    cout << "[ 0-20] ";
                }
                if (off == 1) {
                    cout << "[20-40] ";
                }
                if (off == 2) {
                    cout << "[40-60] ";
                }
                if (off == 3) {
                    cout << "[60+  ] ";
                }

                cout << vaccinated_population << " " << population << " " << percent << "%" << endl;
            }

            processTreeForPopulationStatusByAge(tn->right, sl1, sl2);
        }
    }

    void processTreeForPopulationStatusByAge(Node * tn, SkipList & sl1, SkipList & sl2, string country) {
        if (tn != NULL) {
            processTreeForPopulationStatusByAge(tn->left, sl1, sl2, country);

            Country * c = dynamic_cast<Country*> (tn->data);

            if (c == NULL) {
                return;
            }

            if (c->GetKey() == country) {
                for (int off = 0; off < 4; off++) {
                    int vaccinated_population = sl1.Count_Item_By_Age(off, c->GetName());
                    int population = sl1.Count_Item_By_Age(off, c->GetName()) + sl2.Count_Item_By_Age(off, c->GetName());
                    float percent = vaccinated_population / (float) population * 100;
                    cout << c->GetKey() << " ";

                    if (off == 0) {
                        cout << "[ 0-20] ";
                    }
                    if (off == 1) {
                        cout << "[20-40] ";
                    }
                    if (off == 2) {
                        cout << "[40-60] ";
                    }
                    if (off == 3) {
                        cout << "[60+  ] ";
                    }

                    cout << vaccinated_population << " " << population << " " << percent << "%" << endl;
                }
            }

            processTreeForPopulationStatusByAge(tn->right, sl1, sl2, country);
        }
    }

    void processTreeForPopulationStatusByAge(Node * tn, SkipList & sl1, SkipList & sl2, string d1, string d2) {
        if (tn != NULL) {
            processTreeForPopulationStatusByAge(tn->left, sl1, sl2, d1, d2);

            Country * c = dynamic_cast<Country*> (tn->data);

            if (c == NULL) {
                return;
            }

            for (int off = 0; off < 4; off++) {
                int vaccinated_population = sl1.Count_Item_By_Age(off, c->GetName(), d1, d2);
                int population = sl1.Count_Item_By_Age(off, c->GetName()) + sl2.Count_Item_By_Age(off, c->GetName());
                float percent = vaccinated_population / (float) population * 100;
                cout << c->GetKey() << " ";

                if (off == 0) {
                    cout << "[ 0-20] ";
                }
                if (off == 1) {
                    cout << "[20-40] ";
                }
                if (off == 2) {
                    cout << "[40-60] ";
                }
                if (off == 3) {
                    cout << "[60+  ] ";
                }

                cout << vaccinated_population << " " << population << " " << percent << "%" << endl;
            }

            processTreeForPopulationStatusByAge(tn->right, sl1, sl2, d1, d2);
        }
    }

    void processTreeForPopulationStatusByAge(Node * tn, SkipList & sl1, SkipList & sl2, string d1, string d2, string country) {
        if (tn != NULL) {
            processTreeForPopulationStatusByAge(tn->left, sl1, sl2, d1, d2, country);

            Country * c = dynamic_cast<Country*> (tn->data);

            if (c == NULL) {
                return;
            }

            if (c->GetKey() == country) {
                for (int off = 0; off < 4; off++) {
                    int vaccinated_population = sl1.Count_Item_By_Age(off, c->GetName(), d1, d2);
                    int population = sl1.Count_Item_By_Age(off, c->GetName()) + sl2.Count_Item_By_Age(off, c->GetName());
                    float percent = vaccinated_population / (float) population * 100;
                    cout << c->GetKey() << " ";

                    if (off == 0) {
                        cout << "[ 0-20] ";
                    }
                    if (off == 1) {
                        cout << "[20-40] ";
                    }
                    if (off == 2) {
                        cout << "[40-60] ";
                    }
                    if (off == 3) {
                        cout << "[60+  ] ";
                    }

                    cout << vaccinated_population << " " << population << " " << percent << "%" << endl;
                }
            }

            processTreeForPopulationStatusByAge(tn->right, sl1, sl2, d1, d2, country);
        }
    }

    ///

    bool insertRec(Node * n, T * data) {
        const string key = data->GetKey();

        if (n != NULL) {
            const int x = n->key.compare(key);

            if (x > 0) {
                if (n->left != NULL) {
                    return insertRec(n->left, data);
                } else {
                    n->left = new Node(key, data);

#if(OBJECT_DENTRO_MESSAGES)
                    cout << "left[" << n->left << "]. Neo Dentro::Node me dimiourgo: " << key << "dimiourgithike" << endl;
#endif
                }
            } else if (x < 0) {
                if (n->right != NULL) {
                    insertRec(n->right, data);

                } else {
                    n->right = new Node(key, data);
#if(OBJECT_DENTRO_MESSAGES)
                    cout << "Right[" << n->right << "] Ena neo Dentro::Node me dimiourgo: " << key << "dimiourgithike " << endl;
#endif
                }
            } else if (x == 0) {
#if(OBJECT_DENTRO_MESSAGES)
                cout << "Node me dimiourgo: " << key << "iparxei idi! Lista::Insert post" << endl;
#endif
                return false;
            }
        } else {
            root = new Node(key, data);
#if(OBJECT_DENTRO_MESSAGES)
            cout < "Root[" << root << "] Ena neo Dentro::Node me dimiourgo: " << key << "dimiourgithike" << endl;
#endif
        }

        return true;
    }

    void insertRec(Node * n, Node * target) {
        const string key = target->key;

        if (n != NULL && target != NULL) {
            const int x = n->key.compare(key);

            if (x > 0) {
                if (n->left != NULL) {
                    insertRec(n->left, target);
                } else {
                    n->left = new Node(*target);
#if(OBJECT_DENTRO_MESSAGES)
                    cout << "Left[" << n->left << "] Ena neo Dentro::Node me dimiourgo: " << key << "dimiourgithike" << endl;
#endif
                }
            } else if (x < 0) {
                if (n->right != NULL) {
                    insertRec(n->right, target);

                } else {
                    n->right = new Node(*target);
#if(OBJECT_DENTRO_MESSAGES)
                    cout << "Right[" << n->right << "] Ena neo Dentro::Node me dimiourgo: " << key << "dimiourgithike " << endl;
#endif
                }
            } else if (x == 0) {
#if(OBJECT_DENTRO_MESSAGES)
                cout << "Node me dimiourgo " << key << " iparxei idi. [n->lista.append] gia " << target->lista.get_size() << " post " << endl;
#endif
            }
        }
    }

    void mergeRec(Node * target) {
        if (target != NULL) {
            mergeRec(target->left);
            mergeRec(target->right);
            insertRec(this->root, target);
        }
    }

    void diagrafi(Node * node) {
        if (node != NULL) {
            diagrafi(node->left);
            diagrafi(node->right);
            counter++;
            delete node->data;
            delete node;
        }
    }

    T * Anazitisi(Node *root, string key) {
        Node *temporary = root;

        while (temporary != NULL) {
            if (temporary->key == key) {
                //cout << "\n item found at vathos: " << vathos;
                return temporary->data;
            } else if (temporary->key > key) {
                temporary = temporary->left;
            } else {
                temporary = temporary->right;
            }
        }
        //cout << "\n item not found" ;
        return NULL;
    }
public:

    BinaryTree() : root(NULL) {
#if(OBJECT_DENTRO_MESSAGES)
        cout << "Dimiourgithike ena dentro" << endl;
#endif
    }

    ~BinaryTree() {
        counter = 0;
        diagrafi(root);
#if(OBJECT_DENTRO_MESSAGES)
        cout << "Diagrafike ena dentro" << endl;
#endif

        cout << "~BinaryTree, counter: " << counter << endl;
    }

    void enhance(const BinaryTree& tree) {
        mergeRec(tree.root);
    }

    void print() {
        counter = 0;
        Nodeprint(this->root);
        cout << endl;
        cout << "Counter: " << counter << endl;
    }

    void processTreeForVaccineStatus(string id) {
        int i = atoi(id.c_str());
        processTreeForVaccineStatus(this->root, i);
    }

    void processTreeForPopulationStatus(SkipList & sl1, SkipList & sl2) {
        processTreeForPopulationStatus(this->root, sl1, sl2);
    }

    void processTreeForPopulationStatus(SkipList & sl1, SkipList & sl2, string country) {
        processTreeForPopulationStatus(this->root, sl1, sl2, country);
    }

    void processTreeForPopulationStatus(SkipList & sl1, SkipList & sl2, string d1, string d2) {
        processTreeForPopulationStatus(this->root, sl1, sl2, d1, d2);
    }

    void processTreeForPopulationStatus(SkipList & sl1, SkipList & sl2, string d1, string d2, string country) {
        processTreeForPopulationStatus(this->root, sl1, sl2, d1, d2, country);
    }
    
    void processTreeForPopulationStatusByAge(SkipList & sl1, SkipList & sl2) {
        processTreeForPopulationStatusByAge(this->root, sl1, sl2);
    }

    void processTreeForPopulationStatusByAge(SkipList & sl1, SkipList & sl2, string country) {
        processTreeForPopulationStatusByAge(this->root, sl1, sl2, country);
    }

    void processTreeForPopulationStatusByAge(SkipList & sl1, SkipList & sl2, string d1, string d2) {
        processTreeForPopulationStatusByAge(this->root, sl1, sl2, d1, d2);
    }

    void processTreeForPopulationStatusByAge(SkipList & sl1, SkipList & sl2, string d1, string d2, string country) {
        processTreeForPopulationStatusByAge(this->root, sl1, sl2, d1, d2, country);
    }

    bool insert(T * c) {
        return this->insertRec(root, c);
    }

    T * search(string key) {
        return this->Anazitisi(root, key);
    }
};

#endif