#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <signal.h>
#include <dirent.h>
#include <cstdlib>
#include <stdlib.h>
#include <iostream>
#include <fcntl.h>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>

#include "operations.h"
#include "dentro.h"
#include "Session.h"
#include "SessionParent.h"
#include "operations_parent.h"

using namespace std;

static int numMonitors;
static SessionParent session;

// "${OUTPUT_PATH}" -m 4 -b 2000 -s 1000 -i data_small -c 100  -t 3

int main_child(int argc, const char** argv);

void catchinterruptForParent(int signo) {
    printf("\nCatching: signo=%d\n", signo);
    int status = 0;

    for (int i = 0; i < numMonitors; i++) {
        kill(ChildInfo::pids[i], SIGKILL);
    }

    for (int i = 0; i < numMonitors; i++) {
        while ((waitpid(-1, &status, WNOHANG)) == 0) {
            printf("Still waiting for a child to return\n");
            sleep(1);
        }
    }

    session.children.processTreeToDeletePipes();

    delete [] ChildInfo::pids;

    cout << "Main exit via signal" << endl;

    exit(0);
}

void displayMenuForParent() {
    cout << "WELCOME" << endl << endl;
    cout << "Press [ /travelRequest citizenID date countryFrom CountryTo virusName ] to check if a citizen is vaccinated and allowed to travel !" << endl;
    cout << "Press [ /travelStats virusName date1 date2 ] to check Total Requests for traveling, accepted and rejected Requests too!" << endl;
    cout << "Press [ /travelStats virusName date1 date2 country ] to check Total Requests for traveling for a specific country, accepted and rejected Requests too!" << endl;
    cout << "Press [ /addVaccinationRecords country ] to add a country file for processing !" << endl;
    cout << "Press [ /searchVaccinationStatus citizenID ] to check the vaccination status of this citizen !" << endl;
    cout << "Press [ /exit ] to exit !" << endl << endl;
    cout << "Type  [ /menu ] to print menu again !  " << endl;
}

int main(int argc, char** argv) {
    string sourceDirectory;
    string execFile = "nocheck";
    int b = 256;
    int buffer_size;
    int c, t;
    string argv0 = string(argv[0]);

    if (argv0 != execFile && execFile != "nocheck") {
        cout << "Invalid executable name " << endl;
        cout << "Name found: " << argv0 << endl;
        return 0;
    } else {
        srand(time(0));
    }

    for (int i = 1; i < argc; i++) {
        string argvi = string(argv[i]);

        if (argvi == "-m") {
            continue;
        } else if (argvi == "-b") {
            continue;
        } else if (argvi == "-s") {
            continue;
        } else if (argvi == "-i") {
            continue;
        } else if (argvi == "-c") {
            continue;
        } else if (argvi == "-t") {
            continue;
        } else {
            if (i % 2 == 1) {
                cout << "Syntax error, please try again with correct flags!" << endl;
                return 0;
            } else {
                string flag = string(argv[i - 1]);
                string value = string(argv[i]);

                if (flag == "-m") {
                    numMonitors = atoi(value.c_str());
                } else if (flag == "-b") {
                    buffer_size = atoi(value.c_str());
                } else if (flag == "-s") {
                    b = atoi(value.c_str());
                    BloomFilter::filtersize = b;
                } else if (flag == "-c") {
                    c = atoi(value.c_str());
                } else if (flag == "-t") {
                    t = atoi(value.c_str());
                } else if (flag == "-i") {
                    sourceDirectory = value;
                }
            }
        }
    }

    cout << "Source directory: " << sourceDirectory << endl;
    cout << "Bloom filter size: " << b << endl;
    cout << "Buffer size: " << buffer_size << endl;
    cout << "Threads: " << t << endl;
    cout << "Prod&cons size: " << c << endl;

    DIR *dp;
    struct dirent *dir;

    if ((dp = opendir(sourceDirectory.c_str())) == NULL) {
        perror("opendir");
        return 0;
    }

    while ((dir = readdir(dp)) != NULL) {
        if (dir->d_ino == 0 || dir->d_name[0] == '.' || (dir->d_name[0] == '.' || dir->d_name[1] == '.')) {
            continue;
        }

        char * newname = (char *) malloc(strlen(dir->d_name) + 2);
        strcpy(newname, dir->d_name);

        session.countries.insert(new Country(newname));

        free(newname);
        newname = NULL;
    }
    closedir(dp);


    ChildInfo::pids = new pid_t[numMonitors];
    ChildInfo::buffer = new char[buffer_size];
    ChildInfo::buffersize = buffer_size;

    for (int i = 0; i < numMonitors; i++) {
        ChildInfo * info = new ChildInfo(i);

        info->createSocket();

        session.children.insert(info);

        pid_t childpid;

        childpid = fork();

        if (childpid == -1) {
            perror("Failed to fork");
            return 1;
        }

        if (childpid == 0) {
            printf("I am the child process with ID: %lu \n", (long) getpid());

            const char * port = info->GetPortAsString().c_str();

            const char ** argv = new const char*[4];

            argv[0] = "nocheck";
            argv[1] = "-p";
            argv[2] = port;
            argv[3] = NULL;

            main_child(argc, argv);

            exit(0);
        } else {
            ChildInfo::pids[i] = childpid;

            struct sockaddr_in client;
            socklen_t clientlen = sizeof (client);

            int clientfd;
            
            cout << "Waiting for connection with child: " << i << endl;

            if ((clientfd = accept(info->getListenfd(), (struct sockaddr *) &client, &clientlen)) < 0) {
                perror("accept");
                exit(clientfd);
            }
            
            info->setClientfd(clientfd);

            stringstream ss1;
            ss1 << ChildInfo::buffersize;
            string out1;
            ss1 >> out1;

            strcpy(ChildInfo::buffer, out1.c_str());

            writer_int(ChildInfo::buffer, clientfd);


            stringstream ss2;
            ss2 << BloomFilter::filtersize;
            string out2;
            ss2 >> out2;

            strcpy(ChildInfo::buffer, out2.c_str());

            writer_int(ChildInfo::buffer, clientfd);

            writer(ChildInfo::buffer, sourceDirectory.c_str(), ChildInfo::buffersize, sourceDirectory.length() + 1, clientfd);


            printf("I am the parent process with ID: %lu, created child with pid: %d \n", (long) getpid(), childpid);
        }
    }

    session.countries.processTreeToDistributeCountries(&session.children);

    session.countries.processTreeToSendCountriesAndReceiveFilters(&session.children, session.diseases);


    //    session.countries.print();

    cout << "************************************************* \n";
    session.children.print();

    session.diseases.print();
    cout << "************************************************* \n";

    struct sigaction act;
    act.sa_restorer = 0;
    act.sa_flags = 0;
    act.sa_handler = catchinterruptForParent;
    sigfillset(&(act.sa_mask));

    sigaction(SIGINT, &act, NULL);
    sigaction(SIGQUIT, &act, NULL);

    sigset_t set1;

    sigemptyset(&set1); // completely full set

    sigaddset(&set1, SIGINT);
    sigaddset(&set1, SIGQUIT); // a set minus INT & TSTP

    displayMenuForParent();


    while (true) {
        //        break;
        // detect command and run proper operation method
        cout << "Press a command to run: ";

        string menu;

        sigprocmask(SIG_UNBLOCK, &set1, NULL);

        cin >> menu;

        sigprocmask(SIG_BLOCK, &set1, NULL); // disallow everything here!

        if (menu == "exit" || menu == "/exit") {
            break;
        }

        if (menu == "/menu" || menu == "") {
            displayMenuForParent();
        }

        if (menu == "/travelRequest" || menu == "travelRequest") {
            string id, date, countryFrom, countryTo, virus;

            cin >> id >> date >> countryFrom >> countryTo >> virus;
            travelRequest(session, id, date, countryFrom, countryTo, virus);

        }
        if (menu == "/travelStats" || menu == "travelStats") {
            string virus, date1, date2, country;
            char postfix;

            cin >> virus >> date1 >> date2;

            postfix = getchar();

            cout << "POSTFIX: " << (int) postfix << endl;
            if (postfix == '\n') {
                travelStats(session, virus, date1, date2);
            } else {
                cin >> country;
                travelStats(session, virus, date1, date2, country);
            }
        }
        if (menu == "/addVaccinationRecords" || menu == "addVaccinationRecords") {
            string country;
            cin >> country;
            addVaccinationRecords(session, country);
        }

        if (menu == "/log" || menu == "log") {
            string country;
            cin >> country;
            refreshChildren(session, country);
            usleep(30000);
        }

        if (menu == "/searchVaccinationStatus" || menu == "searchVaccinationStatus") {
            string id;
            cin >> id;
            searchVaccinationStatus(session, id);
        }
    }

    int status = 0;

    stopChildren(session);

    for (int i = 0; i < numMonitors; i++) {
        while ((waitpid(-1, &status, 0)) == 0) {
            printf("child exited\n");
        }
    }

    session.children.processTreeToDeletePipes();

    delete [] ChildInfo::pids;
    delete [] ChildInfo::buffer;

    cout << "Main exit " << endl;

    return 0;
}




