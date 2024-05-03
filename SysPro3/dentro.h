#ifndef DENTRO_H
#define DENTRO_H
#include <unistd.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fcntl.h>
#include <dirent.h>
#include <cstring>

#include "Disease.hpp"
#include "Country.hpp"
#include "ChildInfo.h"
#include "readerwriter.h"
#include "File.h"

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
    int id;

    void Nodeprint(Node * n, ostream & out = std::cout) {
        if (n != NULL) {
            Nodeprint(n->left, out);
            n->data->print(out);
            counter++;
            Nodeprint(n->right, out);
        }
    }

    void processTreeToDeleteSockets(Node * tn) {
        if (tn != NULL) {
            processTreeToDeleteSockets(tn->left);

            ChildInfo * d = dynamic_cast<ChildInfo*> (tn->data);

            cout << "Closing " << d->getListenfd() << endl;
            cout << "Closing " << d->getClientfd() << endl;

            close(d->getListenfd());
            close(d->getClientfd());

            processTreeToDeleteSockets(tn->right);
        }
    }

    void processTreeToDistributeCountries(BinaryTree<ChildInfo> * children, Node * tn) {
        if (tn != NULL) {
            processTreeToDistributeCountries(children, tn->left);

            Country * d = dynamic_cast<Country*> (tn->data);

            stringstream ss;
            string key;
            ss << id;
            ss >> key;

            ChildInfo * info = dynamic_cast<ChildInfo*> (children->search(key));

            d->SetChildInfo(info);

            cout << "checking country: " << d->GetKey() << " with worker id: " << key << " " << children->GetCounter() << endl;

            if (id + 1 == children->GetCounter()) {
                id = 0;
            } else {
                id++;
            }

            processTreeToDistributeCountries(children, tn->right);
        }
    }

    void processTreeToSendCountries(BinaryTree<ChildInfo> * children, Node * tn) {
        if (tn != NULL) {
            processTreeToSendCountries(children, tn->left);

            Country * d = dynamic_cast<Country*> (tn->data);

            ChildInfo * info = d->GetChildInfo();

            cout << "Sending " << d->GetName() << " to " << info->GetKey() << " ... " << " socketfd: " << info->getClientfd() << endl;

            writer(ChildInfo::buffer, d->GetName().c_str(), ChildInfo::buffersize, d->GetName().length() + 1, info->getClientfd());


            processTreeToSendCountries(children, tn->right);
        }
    }

    void processTreeToSendCountries(BinaryTree<ChildInfo> * children, Node * tn, int i) {
        if (tn != NULL) {
            processTreeToSendCountries(children, tn->left, i);

            Country * d = dynamic_cast<Country*> (tn->data);

            ChildInfo * info = d->GetChildInfo();

            if (info->getID() == i) {
                cout << "Sending " << d->GetName() << " to " << info->GetKey() << " ... " << " southfd: " << info->getClientfd() << endl;

                writer(ChildInfo::buffer, d->GetName().c_str(), ChildInfo::buffersize, d->GetName().length() + 1, info->getClientfd());

            }

            processTreeToSendCountries(children, tn->right, i);
        }
    }

    void processTreeToSendDiseases(Node * tn, int northfd) {
        if (tn != NULL) {
            processTreeToSendDiseases(tn->left, northfd);

            Disease * d = dynamic_cast<Disease*> (tn->data);

            printf("Sending %s to north fd: %d \n", d->GetName().c_str(), northfd);

            writer(ChildInfo::buffer, d->GetName().c_str(), ChildInfo::buffersize, d->GetName().length() + 1, northfd);

            char * bf = (char*) d->getBloomFilter().getData();
            int size = BloomFilter::filtersize;

            writer(ChildInfo::buffer, bf, ChildInfo::buffersize, size, northfd);

            processTreeToSendDiseases(tn->right, northfd);
        }
    }

    string processTreeForVaccineStatus(Node * tn, int id) {
        if (tn != NULL) {
            string x = processTreeForVaccineStatus(tn->left, id);

            Disease * d = dynamic_cast<Disease*> (tn->data);

            if (d == NULL) {
                return "";
            }

            SkipListNode * sn_1 = d->getSkipList(true).Get_Item(id);
            SkipListNode * sn_2 = d->getSkipList(false).Get_Item(id);

            bool t1 = sn_1 != NULL;
            bool t2 = sn_2 != NULL;

            string y = "";

            if (t1) {
                //                cout << d->GetKey() << ": vaccinated at " << sn_1->date.get_str() << endl;
                y = d->GetKey() + ": vaccinated at " + " " + sn_1->date.get_str() + "\n";
            }

            if (t2) {
                //                cout << d->GetKey() << ": not vaccinated " << endl;
                y = d->GetKey() + ": not vaccinated " + "\n";
            }

            string z = processTreeForVaccineStatus(tn->right, id);

            string buf = "";
            buf += x;
            buf += y;
            buf += z;
            return buf;
        } else {
            return "";
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

    BinaryTree() : root(NULL), counter(0) {
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

    void print(ostream & out = std::cout) {
        counter = 0;
        Nodeprint(this->root, out);
        out << "Counter: " << counter << endl << endl;
    }

    string processTreeForVaccineStatus(string id) {
        int i = atoi(id.c_str());
        return processTreeForVaccineStatus(this->root, i);
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
        bool x = this->insertRec(root, c);
        if (x) {
            counter++;
        }
        return x;
    }

    T * search(string key) {
        return this->Anazitisi(root, key);
    }

    T * search(int key) {
        string k;
        stringstream ss;
        ss << key;
        ss >> k;

        return this->Anazitisi(root, k);
    }

    void processTreeToDeletePipes() {
        processTreeToDeleteSockets(this->root);
    }

    void processTreeToDistributeCountries(BinaryTree<ChildInfo> * children) {
        id = 0;
        processTreeToDistributeCountries(children, this->root);
    }

    void processTreeToSendCountries(BinaryTree<ChildInfo> * children, BinaryTree<Disease> & diseases, int specific_child) {
        // send
        processTreeToSendCountries(children, this->root, specific_child);

        int i = specific_child;

        ChildInfo * info = children->search(i);
        cout << "Closing: south fd: " << info->getClientfd() << endl;
        close(info->getClientfd());
        //            info->SetSouthfd(open(info->getSouthPipe().c_str(), O_WRONLY));

        cout << "Waiting for children to send bloom filters ... " << endl;

        char * msg = reader_ack(ChildInfo::buffer, ChildInfo::buffersize, info->getClientfd());

        delete [] msg;

        // receive viruses
        int counter = 0;
        char * virus;

        cout << "waiting for viruses from child " << i << " fd: " << info->getClientfd() << endl;

        while ((virus = reader(ChildInfo::buffer, ChildInfo::buffersize, info->getClientfd())) != NULL) {
            cout << "Parent:Virus received from child: " << virus << endl;
            counter++;

            string id = virus;

            char *bf = reader(ChildInfo::buffer, ChildInfo::buffersize, info->getClientfd());

            if (diseases.search(id) == NULL) {
                diseases.insert(new Disease(id, 30));
            }

            for (int i = 0; i < BloomFilter::filtersize; i++) {
                diseases.search(id)->getBloomFilter().getData()[i] |= bf[i];
            }

            delete [] bf;
            delete [] virus;
        }

        writer_ack(ChildInfo::buffer, ChildInfo::buffersize, info->getClientfd());

        cout << "*** Synch complete - PARENT ***\n";
    }

    void processTreeToSendCountriesAndReceiveFilters(BinaryTree<ChildInfo> * children, BinaryTree<Disease> & diseases) {


        cout << "Sending countries ... " << endl;

        processTreeToSendCountries(children, this->root);

        for (int i = 0; i < children->GetCounter(); i++) {
            ChildInfo * info = children->search(i);
            string eof = "eof";

            writer(ChildInfo::buffer, eof.c_str(), ChildInfo::buffersize, eof.length() + 1, info->getClientfd());
        }

        cout << "Waiting for children to send ack... " << endl;

        for (int i = 0; i < children->GetCounter(); i++) {
            ChildInfo * info = children->search(i);

            char * msg = reader_ack(ChildInfo::buffer, ChildInfo::buffersize, info->getClientfd());

            delete [] msg;
        }

        cout << "Waiting for children to send viruses... " << endl;

        // receive viruses

        for (int i = 0; i < children->GetCounter(); i++) {
            ChildInfo * info = children->search(i);
            int counter = 0;
            char * virus;

            cout << "waiting for viruses from child " << i << " fd: " << info->getClientfd() << endl;

            while ((virus = reader(ChildInfo::buffer, ChildInfo::buffersize, info->getClientfd())) != NULL) {
                if (string(virus) == "eof") {
                    break;
                }
                cout << "Parent:Virus received from child: " << virus << endl;
                counter++;

                string id = virus;

                char *bf = reader(ChildInfo::buffer, ChildInfo::buffersize, info->getClientfd());

                if (diseases.search(id) == NULL) {
                    diseases.insert(new Disease(id, 30));
                }

                for (int i = 0; i < BloomFilter::filtersize; i++) {
                    diseases.search(id)->getBloomFilter().getData()[i] |= bf[i];
                }

                delete [] bf;
                delete [] virus;
            }
            writer_ack(ChildInfo::buffer, ChildInfo::buffersize, info->getClientfd());
        }

        cout << "*** Synch complete - PARENT ***\n";
    }

    void processTreeToSendDiseases(int northfd) {

        processTreeToSendDiseases(this->root, northfd);
    }

    int GetCounter() const {
        return counter;
    }

    void processTreeToLoadCountries(class Session & session, BinaryTree<File> & files, Node * tn, string sourceDirectory) {
        void insertCitizenRecord(class Session & session, string id, string firstname, string lastname, string country, string age, string virus, bool flag);
        void insertCitizenRecord(class Session & session, string id, string firstname, string lastname, string country, string age, string virus, class Date d, bool flag);

        int counter = 0;

        if (tn != NULL) {
            processTreeToLoadCountries(session, files, tn->left, sourceDirectory);

            Country * c = (Country*) tn->data;

            string path = sourceDirectory + "/" + c->GetName();

            DIR *dp;
            struct dirent *dir;

            if ((dp = opendir(path.c_str())) == NULL) {
                perror("opendir");
                return;
            }

            while ((dir = readdir(dp)) != NULL) {
                if (dir->d_ino == 0 || dir->d_name[0] == '.' || (dir->d_name[0] == '.' || dir->d_name[1] == '.')) {
                    continue;
                }

                char * newname = new char[strlen(dir->d_name) + 2];
                strcpy(newname, dir->d_name);


                string sourceFile = path + "/" + newname;

                if (files.search(sourceFile)) {
                    continue;
                }

                fstream file;
                file.open(sourceFile.c_str(), ios::in);

                files.insert(new File(sourceFile));

                if (file.is_open()) {
                    string test, id, firstname, lastname, country, age, virus, a, date;
                    int counter = 0;
                    while (true) {
                        file >> id >> firstname >> lastname >> country >> age >> virus >> a;

                        if (file.eof()) {
                            break;
                        }

                        counter++;

                        date = "";

                        char buffer[100] = {0};
                        file.getline(buffer, sizeof (buffer), '\n');

                        char * temp = buffer;

                        while (*temp == ' ') {
                            temp++;
                        }

                        date = temp;


                        //                        cout << "Id = " << id << " Firsname = " << firstname << " Lastname = " << lastname << " country = " << country << " age = " << age << " virus = " << virus << " Vaccinated? = " << a;

                        if (a == "YES") {
                            //                            cout << " Date = " << date << endl;

                            Date d(date);

                            insertCitizenRecord(session, id, firstname, lastname, country, age, virus, d, true);
                        } else {
                            //                            cout << endl;

                            if (date != "") {
                                //                                cout << "Error in record: " << id << firstname << lastname << country << age << virus << a << endl;
                            } else {
                                insertCitizenRecord(session, id, firstname, lastname, country, age, virus, true);
                            }
                        }
                    }
                    file.close();

                    //                    cout << "Total lines processed: " << counter << endl;
                } else {
                    cout << "Error opening the file" << endl;
                }

                delete [] newname;
                newname = NULL;
            }
            closedir(dp);
            counter++;

            processTreeToLoadCountries(session, files, tn->right, sourceDirectory);
        }
    }

    void processTreeToLoadCountries(Session & session, BinaryTree<File> & files, string sourceDirectory) {
        processTreeToLoadCountries(session, files, this->root, sourceDirectory);
    }
};

#endif