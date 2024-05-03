

#include <iostream>
#include <string>
#include <signal.h>
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
            int southfd = country->GetChildInfo()->GetSouthfd();
            int northfd = country->GetChildInfo()->GetNorthfd();

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

    cout << "waiting for viruses from child " << country->GetChildInfo()->getID() << " fd: " << info->GetNorthfd() << endl;

    while ((virus = reader(ChildInfo::buffer, ChildInfo::buffersize, info->GetNorthfd())) != NULL && strcmp(virus, "refresh_complete") != 0) {
        cout << "Parent:Virus received from child: " << virus << endl;
        counter++;

        string id = virus;

        char *bf = reader(ChildInfo::buffer, ChildInfo::buffersize, info->GetNorthfd());

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

        writer(ChildInfo::buffer, menu.c_str(), ChildInfo::buffersize, menu.length() + 1, info->GetSouthfd());
        writer(ChildInfo::buffer, id.c_str(), ChildInfo::buffersize, id.length() + 1, info->GetSouthfd());
    }

    for (int j = 0; j < session.children.GetCounter(); j++) {
        ChildInfo * info = session.children.search(j);

        string ans1 = reader(ChildInfo::buffer, ChildInfo::buffersize, info->GetNorthfd());
        
        if (ans1 != "Citizen not found \n") {
            cout << ans1 << endl;
        }
    }
}
