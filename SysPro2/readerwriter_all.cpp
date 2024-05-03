#include <unistd.h>
#include <fcntl.h>
#include "readerwriter_all.h"


int write_all(int fd, const char*buff, size_t size) {
    size_t sent;
    ssize_t n;
    
    for (sent = 0; sent < size; sent += n) {
        if ((n = write(fd, buff + sent, size - sent)) == -1) {
            return-1;
        }
    }
    return sent;
}

int read_all(int fd, char*buff, size_t size) {
    size_t sent;
    ssize_t n;
    for (sent = 0; sent < size; sent += n) {
        if ((n = read(fd, buff + sent, size - sent)) == -1) {
            return-1;
        }
    }
    return sent;
}