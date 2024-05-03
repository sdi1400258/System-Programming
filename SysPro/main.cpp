#include <cstdlib>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>

#include "operations.h"
#include "dentro.h"
#include "Session.h"

using namespace std;

// ./diseaseMonitor -c test.txt -b 256

void displayMenu() {
    // ask user for a command
    cout << "WELCOME" << endl;
    cout << "Press 10 to check if this citizen has been vaccinated to this virus(Bloom Filter) - /vaccineStatusBloom ID virusName " << endl;
    cout << "Press 20 to check if this citizen has been vaccinated to this virus (skip list) - /vaccineStatus ID virusName" << endl;
    cout << "Press 30 to check if this citizen has been vaccinated at all viruses (skip list) - /vaccineStatus ID" << endl;
    cout << "Press 41 to check population status about a virus during 2 dates for country - /populationStatus country virusName date1 date2" << endl;
    cout << "Press 42 to check population status about a virus during 2 dates - /populationStatus virusName date1 date2" << endl;
    cout << "Press 43 to check population status about a virus - /populationStatus virusName " << endl;
    cout << "Press 44 to check population status about a virus for a country - /populationStatus country virusName " << endl;
    cout << "Press 51 to check population status about a virus during 2 dates sorted by ages for country - /popStatusByAge country virusName date1 date2" << endl;
    cout << "Press 52 to check population status about a virus during 2 dates sorted by ages - /popStatusByAge virusName date1 date2" << endl;
    cout << "Press 53 to check population status about a virus sorted by ages - /popStatusByAge virusName " << endl;
    cout << "Press 54 to check population status about a virus sorted by ages for a country - /popStatusByAge country virusName " << endl;
    cout << "Press 60 to insert a Citizen to the vaccination programm - /insertCitizenRecord ID firstName lastName country age virusName YES/NO [date]" << endl;
    cout << "Press 70 to vaccinate now a citizen - /vaccinateNow ID firstName lastName country age virusName" << endl;
    cout << "Press 80 to check which citizens hasn't been vaccinated to this virus - /listnonVaccinatedPersons virusName" << endl;
    cout << "Type menu , to print menu again !  " << endl;
    cout << "Press 90 to exit - /exit " << endl;
}

int datecmp(string date3, string date1, string date2);

int main(int argc, char** argv) {
    string sourceFile = "small.txt";
    string execFile = "nocheck";
    int b = 256;

    string argv0 = string(argv[0]);

    if (argv0 != execFile && execFile != "nocheck") {
        cout << "Invalid executable name " << endl;
        cout << "Name found: " << argv0 << endl;
        return 0;
    }

    for (int i = 1; i < argc; i++) {
        string argvi = string(argv[i]);

        if (argvi == "-c") {
            continue;
        } else if (argvi == "-b") {
            continue;
        } else {
            if (i % 2 == 1) {
                cout << "Syntax error, please try again with correct flags!" << endl;
                return 0;
            } else {
                string flag = string(argv[i - 1]);
                string value = string(argv[i]);

                if (flag == "-c") {
                    sourceFile = value;
                } else if (flag == "-b") {
                    b = atoi(value.c_str());
                    BloomFilter::filtersize = b;
                }
            }
        }
    }

    cout << "Source file: " << sourceFile << endl;
    cout << "Bloom filter size: " << b << endl;

    fstream file;
    file.open(sourceFile.c_str(), ios::in);

    Session session;


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
            
            char buffer[100] = { 0 };
            file.getline(buffer, sizeof(buffer), '\n');
            
            char * temp = buffer;
            
            while (*temp == ' ') {
                temp++;
            }
            
            date = temp;
            

            cout << "Id = " << id << " Firsname = " << firstname << " Lastname = " << lastname << " country = " << country << " age = " << age << " virus = " << virus << " Vaccinated? = " << a;
            if (a == "YES") {
                cout << " Date = " << date << endl;

                Date d(date);

                insertCitizenRecord(session, id, firstname, lastname, country, age, virus, d, true);
            } else {
                cout << endl;
                
                if (date != "") {
                    cout << "Error in record: " << id << firstname << lastname << country << age << virus << a << endl;
                } else {
                    insertCitizenRecord(session, id, firstname, lastname, country, age, virus, true);
                }
            }
        }
        file.close();

        cout << "Total lines processed: " << counter << endl;
    } else {
        cout << "Error opening the file" << endl;
    }

    session.citizens.print();
    session.diseases.print();

    displayMenu();

    while (true) {
        // detect command and run proper operation method
        cout << "Press a number or anything else to run the command directly: ";

        string menu;
        cin >> menu;

        int choice = atoi(menu.c_str());
        if (choice == 90) {
            break;
        } else if (choice <= 0) { // lexicographical analysis
            if (menu == "exit" || menu == "/exit") {
                break;
            }

            if (menu == "menu" || menu == "") {
                displayMenu();
            }

            if (menu == "vaccineStatusBloom" || menu == "/vaccineStatusBloom") {
                string id, virus;

                cin >> id >> virus;

                vaccineStatusBloom(session, id, virus);
            }
            if (menu == "vaccineStatus" || menu == "/vaccineStatus") {
                string id;
                string virus;
                char postfix;

                cin >> id;

                postfix = getchar();

                cout << "POSTFIX: " << (int) postfix << endl;

                if (postfix == '\n') {
                    vaccineStatus(session, id);
                } else {
                    cin >> virus;
                    vaccineStatus(session, id, virus);
                }
            }

            if (menu == "populationStatus" || menu == "/populationStatus") { // tokenization (TODO)
                char parameters[5000] = {0};
                cin.getline(parameters, sizeof (parameters));

                char * token[4] = {0};

                for (int i = 0; i < 4; i++) {
                    if (i == 0) {
                        token[i] = strtok(parameters, " ");
                    } else {
                        token[i] = strtok(NULL, " ");
                    }
                }
                
                if (token[0] != NULL && token[1] != NULL && token[2] != NULL && token[3] != NULL) {
                    populationStatus(session, token[0], token[1], token[2], token[3]);
                } else if (token[0] != NULL && token[1] != NULL && token[2] != NULL) {
                    populationStatus(session, token[0], token[1], token[2]);
                } else if (token[0] != NULL && token[1] != NULL) {
                    populationStatus(session, token[0], token[1]);
                } else if (token[0] != NULL) {
                    populationStatus(session, token[0]);

                }
            }

            if (menu == "popStatusByAge" || menu == "/popStatusByAge") {
                char parameters[5000] = {0};
                cin.getline(parameters, sizeof (parameters));

                char * token[4] = {0};

                for (int i = 0; i < 4; i++) {
                    if (i == 0) {
                        token[i] = strtok(parameters, " ");
                    } else {
                        token[i] = strtok(NULL, " ");
                    }
                }

                if (token[0] != NULL && token[1] != NULL && token[2] != NULL && token[3] != NULL) {
                    popStatusByAge(session, token[0], token[1], token[2], token[3]);

                } else if (token[0] != NULL && token[1] != NULL && token[2] != NULL) {
                    popStatusByAge(session, token[0], token[1], token[2]);

                } else if (token[0] != NULL && token[1] != NULL) {
                    popStatusByAge(session, token[0], token[1]);

                } else if (token[0] != NULL) {
                    popStatusByAge(session, token[0]);

                }
            }

            if (menu == "listNonVaccinatedPersons" || menu == "/listNonVaccinatedPersons" || menu == "list-nonVaccinated-Persons" || menu == "/list-nonVaccinated-Persons") {
                string virus;

                cin >> virus;

                listNonVaccinatedPersons(session, virus);
            }

            if (menu == "vaccinateNow" || menu == "/vaccinateNow") {
                string id, firstname, lastname, country, age, virus;

                cin >> id >> firstname >> lastname >> country >> age >> virus;

                vaccinateNow(session, id, firstname, lastname, country, age, virus);
            }

            if (menu == "insertCitizenRecord" || menu == "/insertCitizenRecord") {
                string id, firstname, lastname, country, age, virus, yesno, date;

                cin >> id >> firstname >> lastname >> country >> age >> virus >> yesno;

                if (yesno == "YES") {
                    cin >> date;

                    Date d(date);

                    insertCitizenRecord(session, id, firstname, lastname, country, age, virus, d, false);
                } else {
                    insertCitizenRecord(session, id, firstname, lastname, country, age, virus, false);
                }
            }

        } else { // arithmetic analysis
            if (choice == 10) {
                string id, virus;

                cout << "Type the id and the virus: ";
                cin >> id >> virus;

                vaccineStatusBloom(session, id, virus);
            }
            if (choice == 20) {
                string id, virus;

                cout << "Type the id and the virus: ";
                cin >> id >> virus;

                vaccineStatus(session, id, virus);
            }
            if (choice == 30) {
                string id;

                cout << "Type the id: ";

                cin >> id;

                vaccineStatus(session, id);
            }
            if (choice == 41) {
                string country, virus, date1, date2;

                cout << "Type the country, the virus and the dates: ";

                cin >> country >> virus >> date1 >> date2;

                populationStatus(session, country, virus, date1, date2);
            }

            if (choice == 42) {
                string virus, date1, date2;

                cout << "Type the virus and the dates: ";

                cin >> virus >> date1 >> date2;

                populationStatus(session, virus, date1, date2);
            }

            if (choice == 43) {
                string virus;

                cout << "Type the virus :";

                cin >> virus;

                populationStatus(session, virus);
            }

            if (choice == 44) {
                string country, virus;

                cout << "Type the country the virus :";

                cin >> country >> virus;

                populationStatus(session, country, virus);
            }

            if (choice == 51) {
                string country, virus, date1, date2;

                cout << "Type the country, the virus and the dates: ";

                cin >> country >> virus >> date1 >> date2;

                popStatusByAge(session, country, virus, date1, date2);
            }

            if (choice == 52) {
                string virus, date1, date2;

                cout << "Type the virus and the dates: ";

                cin >> virus >> date1 >> date2;

                popStatusByAge(session, virus, date1, date2);
            }

            if (choice == 53) {
                string virus;

                cout << "Type the virus : ";

                cin >> virus;


                popStatusByAge(session, virus);
            }

            if (choice == 54) {
                string country, virus;

                cout << "Type the country and the virus : ";

                cin >> country >> virus;


                popStatusByAge(session, country, virus);
            }

            if (choice == 60) {
                string id, firstname, lastname, country, age, virus, yesno, date;

                cin >> id >> firstname >> lastname >> country >> age >> virus >> yesno;

                if (yesno == "YES") {
                    cin >> date;
                    insertCitizenRecord(session, id, firstname, lastname, country, age, virus, date, false);
                } else {
                    insertCitizenRecord(session, id, firstname, lastname, country, age, virus, false);
                }
            }
            if (choice == 70) {
                string id, firstname, lastname, country, age, virus;

                cin >> id >> firstname >> lastname >> country >> age >> virus;

                vaccinateNow(session, id, firstname, lastname, country, age, virus);
            }
            if (choice == 80) {
                string virus;

                cout << "Type the virus: ";
                cin >> virus;

                listNonVaccinatedPersons(session, virus);
            }
        }
    }

    return 0;
}




