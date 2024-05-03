#ifndef OPERATIONS_PARENT_H
#define OPERATIONS_PARENT_H

#include <string>

#include "SessionParent.h"

using namespace std;


void travelRequest(SessionParent & session, string id, string date, string countryFrom, string countryTo, string virus);

void travelStats(SessionParent & session, string virus, string date1, string date2);

void travelStats(SessionParent & session, string virus, string date1, string date2, string country);

void addVaccinationRecords(SessionParent & session, string country);

void refreshChildren(SessionParent & session, string country);

void searchVaccinationStatus(SessionParent & session, string id);

void stopChildren(SessionParent & session);


#endif /* OPERATIONS_H */

