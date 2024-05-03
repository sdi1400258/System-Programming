
#include "Session.h"

#include <string>
#include <sstream>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstdio>
#include <cstring>
#include "dentro.h"
#include "Disease.hpp"
#include "Citizen.hpp"
#include "Country.hpp"
#include "operations.h"

using namespace std;

int Session::signo = 0;

void Session::log() {
    cout << "writing log " << endl;

    string mypid;

    stringstream ss;

    ss << getpid();

    ss >> mypid;

    string filename = "log_file." + mypid;

    ofstream fp(filename.c_str());

    countries.print(fp);

    fp << "TOTAL: " << accepted + rejected << endl;
    fp << "ACCEPTED: " << accepted << endl;
    fp << "REJECTED: " << rejected << endl;

    signo = 0;
}

void Session::loadFromSocket(string sourceDirectory, int clientfd) {
    char * country;
    int counter = 0;

    cout << "loading from " << sourceDirectory << endl;

    while ((country = reader(ChildInfo::buffer, ChildInfo::buffersize, clientfd)) != NULL) {
        if (string(country) == "eof") {
            break;
        }
        if (countries.search(country) == NULL) {
            Country * c = new Country(country);
            cout << "Received: " << c->GetName() << endl;
            countries.insert(c);

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

                            insertCitizenRecord(*this, id, firstname, lastname, country, age, virus, d, true);
                        } else {
                            //                            cout << endl;

                            if (date != "") {
                                //                                cout << "Error in record: " << id << firstname << lastname << country << age << virus << a << endl;
                            } else {
                                insertCitizenRecord(*this, id, firstname, lastname, country, age, virus, true);
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
        }
    }

    writer_ack(ChildInfo::buffer, ChildInfo::buffersize, clientfd);



    cout << "+++ client country reader complete +++ " << counter << "\n";


    // send diseases to parent

    diseases.processTreeToSendDiseases(clientfd);

    string eof = "eof";

    writer(ChildInfo::buffer, eof.c_str(), ChildInfo::buffersize, eof.length() + 1, clientfd);
}

void Session::loadFromBST(string sourceDirectory, int clientfd) {
    cout << "loading from " << sourceDirectory << endl;

    countries.processTreeToLoadCountries(*this, this->files, sourceDirectory);

    diseases.processTreeToSendDiseases(clientfd);
}