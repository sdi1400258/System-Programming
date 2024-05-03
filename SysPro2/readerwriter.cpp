#include <fcntl.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <malloc.h>

#include "readerwriter.h"
#include "readerwriter_all.h"

using namespace std;

void writer(char * buffer, const char * message, const int buffersize, const int messagesize, const int fd) {
    write(fd, &messagesize, sizeof (messagesize));


    if (messagesize < buffersize) {
        int code = 1;
        write_all(fd, (char*) &code, sizeof (code));
        write_all(fd, message, messagesize);
    }

    if (messagesize == buffersize) {
        int code = 2;
        write_all(fd, (char*) &code, sizeof (code));
        write_all(fd, message, buffersize);
    }

    if (messagesize > buffersize) {
        int code = 3;
        write_all(fd, (char*) &code, sizeof (code));

        int b = messagesize / buffersize;

        for (int i = 0; i < b; i++) {
            memcpy(buffer, message, buffersize);
            message = message + buffersize;
            write_all(fd, buffer, buffersize);
        }

        int r = messagesize % buffersize;

        if (r > 0) {
            write_all(fd, message, r);
        }
    }
}

char * reader(char * buffer, const int buffersize, const int fd) {
    int messagesize;
    int code;
    char * message;

    if (read(fd, &messagesize, sizeof (messagesize)) <= 0) {
        return 0;
    }    
    read_all(fd, (char*)&code, sizeof (code));

    message = new char[messagesize * sizeof (char)];
    char * message2 = message;

    if (code == 1) {
        read_all(fd, message, messagesize);
    }

    if (code == 2) {
        read_all(fd, message, buffersize);
    }

    if (code == 3) {
        read_all(fd, (char*)&code, sizeof (code));

        int b = messagesize / buffersize;

        for (int i = 0; i < b; i++) {
            memcpy(buffer, message2, buffersize);
            message2 = message2 + buffersize;
            read_all(fd, buffer, buffersize);
        }

        int r = messagesize % buffersize;

        if (r > 0) {
            read_all(fd, message2, r);
        }
    }

    return message;
}

void writer_ack(char * buffer, const int buffersize, const int fd) {
    const char * verifymsg = "verify";
    int messagesize = strlen(verifymsg) + 1;
    writer(buffer, verifymsg, buffersize, messagesize, fd);
}

void writer_int(char * buffer, const int fd) {
    int value = atoi(buffer);
    int messagesize = sizeof (int);
    write(fd, &value, messagesize);
}

int reader_int(char * buffer, const int fd) {
    int value;
    int messagesize = sizeof (int);
    read(fd, &value, messagesize);
    return value;
}

char * reader_ack(char * buffer, const int buffersize, const int fd) {
    return reader(buffer, buffersize, fd);
}