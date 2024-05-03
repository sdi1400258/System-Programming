
#ifndef READERWRITER_H
#define READERWRITER_H

void writer(char * buffer, const char * message, const int buffersize, const int messagesize, const int fd);

char * reader(char * buffer, const int buffersize, const int fd);


void writer_ack(char * buffer, const int buffersize, const int fd);

char * reader_ack(char * buffer, const int buffersize, const int fd);

void writer_int(char * buffer, const int fd);

int reader_int(char * buffer, const int fd);
#endif /* READERWRITER_H */

