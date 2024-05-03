#ifndef CHILDINFO_H
#define CHILDINFO_H

#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
#include <cstdlib>
#include <sys/socket.h>      /* sockets */
#include <netinet/in.h>      /* internet sockets */
#include <netdb.h>          /* gethostbyaddr */

using namespace std;

class ChildInfo {
private:
    int id;
    int listenfd, clientfd;
    int port;
public:
    static pid_t * pids;
    static char * buffer;
    static int buffersize;

    ChildInfo(int id) : id(id), listenfd(-1), clientfd(-1) {
        port = rand() % 1000 + (40000 + 1000 * id);
    }

    inline int getID() const {
        return id;
    }

    inline string GetKey() const {
        string str;
        stringstream ss;
        ss << id;
        ss >> str;
        return str;
    }

    inline string GetPortAsString() const {
        string str;
        stringstream ss;
        ss << port;
        ss >> str;
        return str;
    }

    inline string GetName() const {
        string str;
        stringstream ss;
        ss << id;
        ss >> str;
        return str;
    }

    inline void print(ostream & out = std::cout) const {
        out << "Child info: " << id << ":" << " " << listenfd << " " << clientfd << endl;
    }

    inline int getClientfd() const {
        return clientfd;
    }

    inline void setClientfd(int clientfd) {
        this->clientfd = clientfd;
    }

    inline int getListenfd() const {
        return listenfd;
    }

    inline void setListenfd(int listenfd) {
        this->listenfd = listenfd;
    }

    inline void createSocket() {
        struct sockaddr_in server;

        if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            perror("socket");
            exit(listenfd);
        }

        server.sin_family = AF_INET; /* Internet domain */
        server.sin_addr.s_addr = htonl(INADDR_ANY);
        server.sin_port = htons(port); /* The given port */

        if (bind(listenfd, (struct sockaddr *) &server, sizeof (server)) < 0) {
            perror("bind");
            exit(1);
        }

        if (listen(listenfd, 25) < 0) {
            perror("listen");
            exit(1);
        }
    }

    int getPort() const {
        return port;
    }

};

#endif /* CHILDINFO_H */

