#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <string>

#include "Session.h"

using namespace std;

string vaccineStatusBloom(Session & session, string id, string virus);

string vaccineStatus(Session & session, string id, string virus);

string vaccineStatus(Session & session, string id);

void populationStatus(Session & session, string country, string virus, string d1, string d2);

void populationStatus(Session & session, string country, string virus);

void populationStatus(Session & session, string virus, string d1, string d2);

void populationStatus(Session & session, string virus);

void popStatusByAge(Session & session, string country, string virus, string d1, string d2);

void popStatusByAge(Session & session, string country, string virus);

void popStatusByAge(Session & session, string virus, string d1, string d2);

void popStatusByAge(Session & session, string virus);

void insertCitizenRecord(Session & session, string id, string firstname, string lastname, string country, string age, string virus, bool flag);

void insertCitizenRecord(Session & session, string id, string firstname, string lastname, string country, string age, string virus, Date date, bool flag);

void vaccinateNow(Session & session, string id, string firstname, string lastname, string country, string age, string virus);

void listNonVaccinatedPersons(Session & session, string virus);


// TODO: add the other operations
#endif /* OPERATIONS_H */

