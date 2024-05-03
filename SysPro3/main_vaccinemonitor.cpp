#include <cstdlib>
#include <stdlib.h>
#include <iostream>
#include <signal.h>
#include <errno.h>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/socket.h>      /* sockets */
#include <netinet/in.h>      /* internet sockets */
#include <netdb.h>          /* gethostbyaddr */

#include "operations.h"
#include "dentro.h"
#include "Session.h"
#include "datevacc.h"

using namespace std;

static Session session;

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

void catchinterrupt(int signo) {
    printf("Child, Catching: signo=%d\n", signo);
    Session::signo = signo;
}

int main_child(int argc, const char** argv) {
    string sourceDirectory;
    string sourceFile;
    string execFile = "nocheck";

    string argv0 = string(argv[0]);

    if (argv0 != execFile && execFile != "nocheck") {
        cout << "Invalid executable name " << endl;
        cout << "Name found: " << argv0 << endl;
        return 0;
    }

    const int port = atoi(argv[2]);

    printf("I am the child process with ID: %lu, port: %d \n", (long) getpid(), port);

    int clientfd;

    /* Open the Socket.  We assume server has already created them.  */

    struct sockaddr_in server;
    struct sockaddr *serverptr = (struct sockaddr*) &server;
    struct hostent *rem;
    
    if ((clientfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        exit(clientfd);
    }
    
    if ((rem = gethostbyname("localhost")) == NULL) {
        herror("gethostbyname");
        exit(1);
    }
    
    server.sin_family = AF_INET; /* Internet domain */
    memcpy(&server.sin_addr, rem->h_addr, rem->h_length);
    server.sin_port = htons(port); /* Server port */
    
    if (connect(clientfd, serverptr, sizeof (server)) < 0) {   
        perror("connect");
        exit(1);
    }

    struct sigaction act;
    act.sa_restorer = 0;
    act.sa_flags = 0;
    act.sa_handler = catchinterrupt;
    sigfillset(&(act.sa_mask));

    sigaction(SIGINT, &act, NULL);
    sigaction(SIGQUIT, &act, NULL);

    ChildInfo::buffersize = reader_int(NULL, clientfd);

    BloomFilter::filtersize = reader_int(NULL, clientfd);

    ChildInfo::buffer = new char[ChildInfo::buffersize];

    sourceDirectory = reader(ChildInfo::buffer, ChildInfo::buffersize, clientfd);

    cout << "#### client: " << ChildInfo::buffersize << " - " << BloomFilter::filtersize << " - " << sourceDirectory << " " << clientfd << " " << clientfd << endl;

    cout << "blip blop \n";

    session.loadFromSocket(sourceDirectory, clientfd);

    // wait for parent to notify us that disease have been processed

    char * msg = reader_ack(ChildInfo::buffer, ChildInfo::buffersize, clientfd);

    delete [] msg;

    // process commands


    sigset_t set1;

    sigemptyset(&set1); // completely full set

    sigaddset(&set1, SIGINT);
    sigaddset(&set1, SIGQUIT); // a set minus INT & TSTP

    while (1) {

        sigprocmask(SIG_UNBLOCK, &set1, NULL); // disallow everything here!

        char * menu_str = reader(ChildInfo::buffer, ChildInfo::buffersize, clientfd);

        sigprocmask(SIG_BLOCK, &set1, NULL); // disallow everything here!

        if (menu_str == NULL && errno == EINTR && (Session::signo == SIGINT || Session::signo == SIGQUIT)) {
            session.log();
            continue;
        }

        string menu = menu_str;

        //        cout << "menu choice for child " << getpid() << " is " << menu << endl;

        if (menu == "exit" || menu == "/exit") {
            break;
        }

        if (menu == "travelRequest" || menu == "/travelRequest") {
            string id, date, countryFrom, countryTo, virus;

            id = reader(ChildInfo::buffer, ChildInfo::buffersize, clientfd);
            date = reader(ChildInfo::buffer, ChildInfo::buffersize, clientfd);
            countryFrom = reader(ChildInfo::buffer, ChildInfo::buffersize, clientfd);
            countryTo = reader(ChildInfo::buffer, ChildInfo::buffersize, clientfd);
            virus = reader(ChildInfo::buffer, ChildInfo::buffersize, clientfd);

            cout << "travel request id          = " << id << endl;
            cout << "travel request date        = " << date << endl;
            cout << "travel request countryFrom = " << countryFrom << endl;
            cout << "travel request countryTo   = " << countryTo << endl;
            cout << "travel request virus       = " << virus << endl;

            string ans1 = vaccineStatusBloom(session, id, virus);

            writer(ChildInfo::buffer, ans1.c_str(), ChildInfo::buffersize, ans1.length() + 1, clientfd);

            if (ans1 == "Maybe") {
                string ans2 = vaccineStatus(session, id, virus);

                writer(ChildInfo::buffer, ans2.c_str(), ChildInfo::buffersize, ans2.length() + 1, clientfd);

                if (!ans2.compare(0, 10, "Vaccinated")) {
                    string d = ans2.substr(14);
                    if (datevacc(d, date)) {
                        session.accepted++;
                    } else {
                        session.rejected++;
                    }
                } else {
                    session.rejected++;
                }
            } else {
                session.rejected++;
            }
        }

        if (menu == "searchVaccinationStatus" || menu == "/searchVaccinationStatus") {
            string id;

            id = reader(ChildInfo::buffer, ChildInfo::buffersize, clientfd);

            //            cout << "travel request id          = " << id << endl;

            string ans1 = vaccineStatus(session, id);

            writer(ChildInfo::buffer, ans1.c_str(), ChildInfo::buffersize, ans1.length() + 1, clientfd);
        }

        if (menu == "addVaccinationRecords" || menu == "/addVaccinationRecords") {
            if (clientfd > 0 && clientfd > 0) {
                session.loadFromBST(sourceDirectory, clientfd);

                string ans2 = "refresh_complete";

                writer(ChildInfo::buffer, ans2.c_str(), ChildInfo::buffersize, ans2.length() + 1, clientfd);
            }
        }
    }



    close(clientfd);
    close(clientfd);

    return 0;



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

    close(clientfd);
    
    delete [] ChildInfo::buffer;

    return 0;
}




