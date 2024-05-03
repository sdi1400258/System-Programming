

#include <iostream>
#include <string>
#include <signal.h>
//#include "Date.h"
#include "Citizen.hpp"
#include "operations_parent.h"
#include "datevacc.h"
#include "TravelRequestList.h"
#include "datecmp.h"

using namespace std;

void travelRequest(SessionParent & session, string id, string date, string countryFrom, string countryTo, string virus) {
    if ((session.diseases.search(virus) == NULL)) {
        cout << "Rejected by parent because of Disease not found \n ";
        session.rejected++;
        return;
    }

    if ((session.countries.search(countryFrom)) == NULL) {
        cout << "Rejected by parent because of Country not found \n ";
        session.rejected++;
        return;
    }

    Disease * c;

    if ((c = session.diseases.search(virus)) == NULL) {
        cout << "Rejected by parent because of Disease not found \n";
        session.rejected++;
        return;
    } else {
        bool result = c->getBloomFilter().test(id);

        bool accepted = false;

        if (result == false) {
            cout << "Rejected by parent because of bloom filter: No" << endl;
            session.rejected++;
        } else {
            cout << "Parent bloom filter: Maybe " << endl;

            Country * country = (Country*) session.countries.search(countryFrom);

            string key = country->GetChildInfo()->GetKey();
            int southfd = country->GetChildInfo()->getClientfd();
            int northfd = country->GetChildInfo()->getClientfd();

            cout << "Worker info for " << countryFrom << " : " << key << endl;

            string menu = "travelRequest";

            writer(ChildInfo::buffer, menu.c_str(), ChildInfo::buffersize, menu.length() + 1, southfd);
            writer(ChildInfo::buffer, id.c_str(), ChildInfo::buffersize, id.length() + 1, southfd);
            writer(ChildInfo::buffer, date.c_str(), ChildInfo::buffersize, date.length() + 1, southfd);
            writer(ChildInfo::buffer, countryFrom.c_str(), ChildInfo::buffersize, countryFrom.length() + 1, southfd);
            writer(ChildInfo::buffer, countryTo.c_str(), ChildInfo::buffersize, countryTo.length() + 1, southfd);
            writer(ChildInfo::buffer, virus.c_str(), ChildInfo::buffersize, virus.length() + 1, southfd);

            string ans1 = reader(ChildInfo::buffer, ChildInfo::buffersize, northfd);

            if (ans1 != "Maybe") {
                cout << "Rejected by child because of: " << ans1 << endl;
                session.rejected++;
            } else {
                cout << "Child bloom filter: Maybe " << endl;

                string ans2 = reader(ChildInfo::buffer, ChildInfo::buffersize, northfd);

                if (!ans2.compare(0, 10, "Vaccinated")) {
                    string d = ans2.substr(14);
                    if (datevacc(d, date)) {
                        cout << "Accepted by child: " << ans2 << endl;
                        session.accepted++;
                        accepted = true;
                    } else {
                        cout << "Rejected by child: " << ans2 << endl;
                        session.rejected++;
                    }
                } else {
                    cout << "Rejected by child because of: " << ans2 << endl;
                    session.rejected++;
                }
            }
        }

        TravelRequest * item = new TravelRequest();
        item->virus = virus;
        item->date = date;
        item->countryTo = countryTo;
        item->accepted = accepted;
        session.books.Add_Item_Telos_TravelRequestLists(item);
    }

}

void travelStats(SessionParent & session, string virus, string date1, string date2) {
    if ((session.diseases.search(virus) == NULL)) {
        cout << "Disease not found \n ";
        return;
    }

    TravelRequest * req = session.books.Get_TravelRequestList_protos();

    int accepted = 0;
    int rejected = 0;

    while (req != NULL) {

        if (datecmp(req->date, date1, date2) && req->virus == virus) {
            if (req->accepted) {
                accepted++;
            } else {
                rejected++;
            }
        }

        req = session.books.get_TravelRequestList_epomenos();
    }

    cout << "Accepted: " << accepted << endl;
    cout << "Rejected: " << rejected << endl;
    cout << "Total   : " << accepted + rejected << endl;

}

void travelStats(SessionParent & session, string virus, string date1, string date2, string country) {

    if ((session.diseases.search(virus) == NULL)) {
        cout << "Disease not found \n ";
        return;
    }

    if ((session.countries.search(country)) == NULL) {
        cout << "Country not found \n ";
        return;
    }

    TravelRequest * req = session.books.Get_TravelRequestList_protos();

    int accepted = 0;
    int rejected = 0;

    while (req != NULL) {
        if (datecmp(req->date, date1, date2) && req->virus == virus && req->countryTo == country) {
            if (req->accepted) {
                accepted++;
            } else {
                rejected++;
            }
        }

        req = session.books.get_TravelRequestList_epomenos();
    }



    cout << "Accepted: " << accepted << endl;
    cout << "Rejected: " << rejected << endl;
    cout << "Total   : " << accepted + rejected << endl;


}

void addVaccinationRecords(SessionParent & session, string countryFrom) {

    if ((session.countries.search(countryFrom)) == NULL) {
        cout << "Country not found \n";
        return;
    }

    Country * country = (Country*) session.countries.search(countryFrom);

    string key = country->GetChildInfo()->GetKey();
    pid_t pid = ChildInfo::pids[country->GetChildInfo()->getID()];

    cout << "Worker info for " << countryFrom << " : " << key << endl;

    kill(pid, SIGUSR1);

    ChildInfo * info = country->GetChildInfo();
    int counter = 0;
    char * virus;

    BinaryTree<Disease> & diseases = session.diseases;

    cout << "waiting for viruses from child " << country->GetChildInfo()->getID() << " fd: " << info->getClientfd() << endl;

    while ((virus = reader(ChildInfo::buffer, ChildInfo::buffersize, info->getClientfd())) != NULL && strcmp(virus, "refresh_complete") != 0) {
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

    cout << "*** Synch complete - PARENT ***\n";

}

void refreshChildren(SessionParent & session, string countryFrom) {

    if ((session.countries.search(countryFrom)) == NULL) {
        cout << "Country not found \n ";
        return;
    }

    Country * country = (Country*) session.countries.search(countryFrom);

    string key = country->GetChildInfo()->GetKey();
    pid_t pid = ChildInfo::pids[country->GetChildInfo()->getID()];

    cout << "Worker info for " << countryFrom << " : " << key << endl;

    kill(pid, SIGINT);
}

void searchVaccinationStatus(SessionParent & session, string id) {

    for (int j = 0; j < session.children.GetCounter(); j++) {
        ChildInfo * info = session.children.search(j);

        string menu = "searchVaccinationStatus";

        writer(ChildInfo::buffer, menu.c_str(), ChildInfo::buffersize, menu.length() + 1, info->getClientfd());
        writer(ChildInfo::buffer, id.c_str(), ChildInfo::buffersize, id.length() + 1, info->getClientfd());
    }

    for (int j = 0; j < session.children.GetCounter(); j++) {
        ChildInfo * info = session.children.search(j);

        string ans1 = reader(ChildInfo::buffer, ChildInfo::buffersize, info->getClientfd());
        
        if (ans1 != "Citizen not found \n") {
            cout << ans1 << endl;
        }
    }
}

void stopChildren(SessionParent & session) {
    for (int j = 0; j < session.children.GetCounter(); j++) {
        ChildInfo * info = session.children.search(j);

        string menu = "exit";

        writer(ChildInfo::buffer, menu.c_str(), ChildInfo::buffersize, menu.length() + 1, info->getClientfd());
    }
}



//
//void vaccineStatusBloom(Session & session, string id, string virus) {
//    //    if (session.citizens.search(id) == NULL) {
//    //        cout << "Citizen not found \n";
//    //        return;
//    //    }
//
//    Disease * c;
//
//    if ((c = session.diseases.search(virus)) == NULL) {
//        cout << "Disease not found \n";
//        return;
//    } else {
//        bool result = c->getBloomFilter().test(id);
//
//        if (result == true) {
//            cout << "Maybe " << endl;
//        } else {
//            cout << "No" << endl;
//        }
//    }
//}
//
//void vaccineStatus(Session & session, string id, string virus) {
//    if (session.citizens.search(id) == NULL) {
//        cout << "Citizen not found \n";
//        return;
//    }
//
//    Disease * c;
//
//    if ((c = session.diseases.search(virus)) == NULL) {
//        cout << "Disease not found \n";
//        return;
//    } else {
//        SkipListNode * tmp = c->getSkipList(true).Get_Item(atoi(id.c_str()));
//
//        if (tmp == NULL) {
//            cout << "Not vaccinated " << endl;
//        } else {
//            cout << "Vaccinated at " << tmp->date.get_str() << endl;
//        }
//    }
//}
//
//void vaccineStatus(Session & session, string id) {
//    if (session.citizens.search(id) == NULL) {
//        cout << "Citizen not found \n";
//        return;
//    }
//
//    session.diseases.processTreeForVaccineStatus(id);
//}
//
//void populationStatus(Session & session, string country, string virus, string d1, string d2) {
//    Disease * c;
//
//    if ((c = session.diseases.search(virus)) == NULL) {
//        cout << "Disease not found \n";
//        return;
//    } else {
//        SkipList & sl1 = c->getSkipList(true);
//        SkipList & sl2 = c->getSkipList(false);
//
//        session.countries.processTreeForPopulationStatus(sl1, sl2, d1, d2, country);
//    }
//
//}
//
//void populationStatus(Session & session, string virus, string d1, string d2) {
//    Disease * c;
//
//    if ((c = session.diseases.search(virus)) == NULL) {
//        cout << "Disease not found \n";
//        return;
//    } else {
//        SkipList & sl1 = c->getSkipList(true);
//        SkipList & sl2 = c->getSkipList(false);
//
//        session.countries.processTreeForPopulationStatus(sl1, sl2, d1, d2);
//    }
//}
//
//void populationStatus(Session & session, string country, string virus) {
//    Disease * c;
//
//    if ((c = session.diseases.search(virus)) == NULL) {
//        cout << "Disease not found \n";
//        return;
//    } else {
//        SkipList & sl1 = c->getSkipList(true);
//        SkipList & sl2 = c->getSkipList(false);
//
//        session.countries.processTreeForPopulationStatus(sl1, sl2, country);
//    }
//}
//
//void populationStatus(Session & session, string virus) {
//    Disease * c;
//
//    if ((c = session.diseases.search(virus)) == NULL) {
//        cout << "Disease not found \n";
//        return;
//    } else {
//        SkipList & sl1 = c->getSkipList(true);
//        SkipList & sl2 = c->getSkipList(false);
//
//        session.countries.processTreeForPopulationStatus(sl1, sl2);
//    }
//}
//
//void popStatusByAge(Session & session, string country, string virus, string d1, string d2) {
//    Disease * c;
//
//    if ((c = session.diseases.search(virus)) == NULL) {
//        cout << "Disease not found \n";
//        return;
//    } else {
//        SkipList & sl1 = c->getSkipList(true);
//        SkipList & sl2 = c->getSkipList(false);
//
//        session.countries.processTreeForPopulationStatusByAge(sl1, sl2, d1, d2, country);
//    }
//}
//
//void popStatusByAge(Session & session, string virus, string d1, string d2) {
//    Disease * c;
//
//    if ((c = session.diseases.search(virus)) == NULL) {
//        cout << "Disease not found \n";
//        return;
//    } else {
//        SkipList & sl1 = c->getSkipList(true);
//        SkipList & sl2 = c->getSkipList(false);
//
//        session.countries.processTreeForPopulationStatusByAge(sl1, sl2, d1, d2);
//    }
//}
//
//void popStatusByAge(Session & session, string country, string virus) {
//    Disease * c;
//
//    if ((c = session.diseases.search(virus)) == NULL) {
//        cout << "Disease not found \n";
//        return;
//    } else {
//        SkipList & sl1 = c->getSkipList(true);
//        SkipList & sl2 = c->getSkipList(false);
//
//        session.countries.processTreeForPopulationStatusByAge(sl1, sl2, country);
//    }
//}
//
//void popStatusByAge(Session & session, string virus) {
//    Disease * c;
//
//    if ((c = session.diseases.search(virus)) == NULL) {
//        cout << "Disease not found \n";
//        return;
//    } else {
//        SkipList & sl1 = c->getSkipList(true);
//        SkipList & sl2 = c->getSkipList(false);
//
//        session.countries.processTreeForPopulationStatusByAge(sl1, sl2);
//    }
//}
//
//void insertCitizenRecord(Session & session, string id, string firstname, string lastname, string country, string age, string virus, bool flag) {
//    int tautotita = atoi(id.c_str());
//    int ilikia = atoi(age.c_str());
//
//    if (session.citizens.search(id) == NULL) {
//        Citizen * c = new Citizen(tautotita, firstname, lastname, country, ilikia);
//        session.citizens.insert(c);
//    }
//
//    if (session.countries.search(country) == NULL) {
//        Country * c = new Country(country);
//        session.countries.insert(c);
//    }
//
//    Citizen * citizen = session.citizens.search(id);
//
//    Disease * c;
//
//    if ((c = session.diseases.search(virus)) == NULL) {
//        Disease * c = new Disease(virus);
//        session.diseases.insert(c);
//
//        c->getSkipList(false).Add_Item(citizen);
//    } else {
//
//        if (c->getSkipList(false).Get_Item(citizen->GetTautotita()) != NULL) {
//            cout << "Already not vaccinated \n";
//        } else {
//            if (c->getSkipList(true).Get_Item(citizen->GetTautotita()) != NULL) {
//                cout << "Already vaccinated \n";
//            } else {
//                c->getSkipList(false).Add_Item(citizen);
//            }
//        }
//    }
//
//    int off = ilikia / 20;
//
//    if (off > 3) {
//        off = 3;
//    }
//}
//
//void insertCitizenRecord(Session & session, string id, string firstname, string lastname, string country, string age, string virus, Date d, bool flag) {
//    int tautotita = atoi(id.c_str());
//    int ilikia = atoi(age.c_str());
//
//    if (session.citizens.search(id) == NULL) {
//        Citizen * c = new Citizen(tautotita, firstname, lastname, country, ilikia);
//        session.citizens.insert(c);
//    }
//
//    Citizen * citizen = session.citizens.search(id);
//    Disease * c;
//
//    if (citizen->GetKey() != id || citizen->GetFirstname() != firstname || citizen->GetLastname() != lastname || citizen->GetCountry() != country || citizen->GetAge() != atoi(age.c_str())) {
//        cout << "incompatible data" << endl;
//        return;
//    }
//
//    if ((c = session.diseases.search(virus)) == NULL) {
//        Disease * c = new Disease(virus);
//        session.diseases.insert(c);
//
//        c->getBloomFilter().add(id);
//        c->getSkipList(true).Add_Item(citizen, d);
//    } else {
//        c->getBloomFilter().add(id);
//
//        if (c->getSkipList(true).Get_Item(citizen->GetTautotita()) != NULL) {
//            cout << "Already vaccinated \n";
//        } else {
//            if (c->getSkipList(false).Get_Item(citizen->GetTautotita()) != NULL) {
//                if (flag == false) {
//                    c->getSkipList(true).Add_Item(citizen, d);
//                    c->getSkipList(false).Remove_Item(citizen->GetTautotita());
//                } else {
//                    cout << "Already not vaccinated \n";
//                }
//            } else {
//                c->getSkipList(true).Add_Item(citizen, d);
//                c->getSkipList(false).Remove_Item(citizen->GetTautotita());
//            }
//        }
//    }
//
//    if (session.countries.search(country) == NULL) {
//        Country * c = new Country(country);
//        session.countries.insert(c);
//    }
//
//    int off = ilikia / 20;
//
//    if (off > 3) {
//        off = 3;
//    }
//}
//
//void vaccinateNow(Session & session, string id, string firstname, string lastname, string country, string age, string virus) {
//    Date date;
//    
//    insertCitizenRecord(session, id, firstname, lastname, country, age, virus, date, false);
//}
//
//void listNonVaccinatedPersons(Session & session, string virus) {
//    Disease * c;
//
//    if ((c = session.diseases.search(virus)) == NULL) {
//        cout << "Disease not found \n";
//        return;
//    } else {
//        c->getSkipList(false).Print();
//    }
//}
