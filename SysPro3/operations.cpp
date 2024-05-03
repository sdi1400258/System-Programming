

#include <iostream>
#include <string>
//#include "Date.h"
#include "Citizen.hpp"
#include "operations.h"

using namespace std;

string vaccineStatusBloom(Session & session, string id, string virus) {
    //    if (session.citizens.search(id) == NULL) {
    //        cout << "Citizen not found \n";
    //        return;
    //    }

    Disease * c;

    if ((c = session.diseases.search(virus)) == NULL) {
        return "Disease not found \n";
    } else {
        bool result = c->getBloomFilter().test(id);

        if (result == true) {
            return "Maybe";
        } else {
            return "No";
        }
    }
}

string vaccineStatus(Session & session, string id, string virus) {
    if (session.citizens.search(id) == NULL) {
        return "Citizen not found \n";
    }

    Disease * c;

    if ((c = session.diseases.search(virus)) == NULL) {
        return "Disease not found \n";
    } else {
        SkipListNode * tmp = c->getSkipList(true).Get_Item(atoi(id.c_str()));

        if (tmp == NULL) {
            cout << "Not vaccinated " << endl;
            return "Not vaccinated ";
        } else {
            //            cout << "Vaccinated at " << tmp->date.get_str() << endl;
            return "Vaccinated at " + tmp->date.get_str("%d-%m-%Y");
        }
    }
}

string vaccineStatus(Session & session, string id) {
    if (session.citizens.search(id) == NULL) {
        return "Citizen not found \n";
    } else {
        Citizen * citizen = session.citizens.search(id);

        string buf = "";

        buf += citizen->GetKey() + " " + citizen->GetFirstname() + " " + citizen->GetLastname() + " " + citizen->GetCountry() + "\n";
        buf += "AGE: " + citizen->GetAgeAsString() + "\n";

        buf += session.diseases.processTreeForVaccineStatus(id);

        return buf;
    }
}

void populationStatus(Session & session, string country, string virus, string d1, string d2) {
    Disease * c;

    if ((c = session.diseases.search(virus)) == NULL) {
        cout << "Disease not found \n";
        return;
    } else {
        SkipList & sl1 = c->getSkipList(true);
        SkipList & sl2 = c->getSkipList(false);

        session.countries.processTreeForPopulationStatus(sl1, sl2, d1, d2, country);
    }

}

void populationStatus(Session & session, string virus, string d1, string d2) {
    Disease * c;

    if ((c = session.diseases.search(virus)) == NULL) {
        cout << "Disease not found \n";
        return;
    } else {
        SkipList & sl1 = c->getSkipList(true);
        SkipList & sl2 = c->getSkipList(false);

        session.countries.processTreeForPopulationStatus(sl1, sl2, d1, d2);
    }
}

void populationStatus(Session & session, string country, string virus) {
    Disease * c;

    if ((c = session.diseases.search(virus)) == NULL) {
        cout << "Disease not found \n";
        return;
    } else {
        SkipList & sl1 = c->getSkipList(true);
        SkipList & sl2 = c->getSkipList(false);

        session.countries.processTreeForPopulationStatus(sl1, sl2, country);
    }
}

void populationStatus(Session & session, string virus) {
    Disease * c;

    if ((c = session.diseases.search(virus)) == NULL) {
        cout << "Disease not found \n";
        return;
    } else {
        SkipList & sl1 = c->getSkipList(true);
        SkipList & sl2 = c->getSkipList(false);

        session.countries.processTreeForPopulationStatus(sl1, sl2);
    }
}

void popStatusByAge(Session & session, string country, string virus, string d1, string d2) {
    Disease * c;

    if ((c = session.diseases.search(virus)) == NULL) {
        cout << "Disease not found \n";
        return;
    } else {
        SkipList & sl1 = c->getSkipList(true);
        SkipList & sl2 = c->getSkipList(false);

        session.countries.processTreeForPopulationStatusByAge(sl1, sl2, d1, d2, country);
    }
}

void popStatusByAge(Session & session, string virus, string d1, string d2) {
    Disease * c;

    if ((c = session.diseases.search(virus)) == NULL) {
        cout << "Disease not found \n";
        return;
    } else {
        SkipList & sl1 = c->getSkipList(true);
        SkipList & sl2 = c->getSkipList(false);

        session.countries.processTreeForPopulationStatusByAge(sl1, sl2, d1, d2);
    }
}

void popStatusByAge(Session & session, string country, string virus) {
    Disease * c;

    if ((c = session.diseases.search(virus)) == NULL) {
        cout << "Disease not found \n";
        return;
    } else {
        SkipList & sl1 = c->getSkipList(true);
        SkipList & sl2 = c->getSkipList(false);

        session.countries.processTreeForPopulationStatusByAge(sl1, sl2, country);
    }
}

void popStatusByAge(Session & session, string virus) {
    Disease * c;

    if ((c = session.diseases.search(virus)) == NULL) {
        cout << "Disease not found \n";
        return;
    } else {
        SkipList & sl1 = c->getSkipList(true);
        SkipList & sl2 = c->getSkipList(false);

        session.countries.processTreeForPopulationStatusByAge(sl1, sl2);
    }
}

void insertCitizenRecord(Session & session, string id, string firstname, string lastname, string country, string age, string virus, bool flag) {
    int tautotita = atoi(id.c_str());
    int ilikia = atoi(age.c_str());

    if (session.citizens.search(id) == NULL) {
        Citizen * c = new Citizen(tautotita, firstname, lastname, country, ilikia);
        session.citizens.insert(c);
    }

    if (session.countries.search(country) == NULL) {
        Country * c = new Country(country);
        session.countries.insert(c);
    }

    Citizen * citizen = session.citizens.search(id);

    Disease * c;

    if ((c = session.diseases.search(virus)) == NULL) {
        Disease * c = new Disease(virus);
        session.diseases.insert(c);

        c->getSkipList(false).Add_Item(citizen);
    } else {

        if (c->getSkipList(false).Get_Item(citizen->GetTautotita()) != NULL) {
            cout << "Already not vaccinated \n";
        } else {
            if (c->getSkipList(true).Get_Item(citizen->GetTautotita()) != NULL) {
                cout << "Already vaccinated \n";
            } else {
                c->getSkipList(false).Add_Item(citizen);
            }
        }
    }

    int off = ilikia / 20;

    if (off > 3) {
        off = 3;
    }
}

void insertCitizenRecord(Session & session, string id, string firstname, string lastname, string country, string age, string virus, Date d, bool flag) {
    int tautotita = atoi(id.c_str());
    int ilikia = atoi(age.c_str());

    if (session.citizens.search(id) == NULL) {
        Citizen * c = new Citizen(tautotita, firstname, lastname, country, ilikia);
        session.citizens.insert(c);
    }

    Citizen * citizen = session.citizens.search(id);
    Disease * c;

    if (citizen->GetKey() != id || citizen->GetFirstname() != firstname || citizen->GetLastname() != lastname || citizen->GetCountry() != country || citizen->GetAge() != atoi(age.c_str())) {
        cout << "incompatible data" << endl;
        return;
    }

    if ((c = session.diseases.search(virus)) == NULL) {
        Disease * c = new Disease(virus);
        session.diseases.insert(c);

        c->getBloomFilter().add(id);
        c->getSkipList(true).Add_Item(citizen, d);
    } else {
        c->getBloomFilter().add(id);

        if (c->getSkipList(true).Get_Item(citizen->GetTautotita()) != NULL) {
            cout << "Already vaccinated \n";
        } else {
            if (c->getSkipList(false).Get_Item(citizen->GetTautotita()) != NULL) {
                if (flag == false) {
                    c->getSkipList(true).Add_Item(citizen, d);
                    c->getSkipList(false).Remove_Item(citizen->GetTautotita());
                } else {
                    cout << "Already not vaccinated \n";
                }
            } else {
                c->getSkipList(true).Add_Item(citizen, d);
                c->getSkipList(false).Remove_Item(citizen->GetTautotita());
            }
        }
    }

    if (session.countries.search(country) == NULL) {
        Country * c = new Country(country);
        session.countries.insert(c);
    }

    int off = ilikia / 20;

    if (off > 3) {
        off = 3;
    }
}

void vaccinateNow(Session & session, string id, string firstname, string lastname, string country, string age, string virus) {
    Date date;

    insertCitizenRecord(session, id, firstname, lastname, country, age, virus, date, false);
}

void listNonVaccinatedPersons(Session & session, string virus) {
    Disease * c;

    if ((c = session.diseases.search(virus)) == NULL) {
        cout << "Disease not found \n";
        return;
    } else {
        c->getSkipList(false).Print();
    }
}
