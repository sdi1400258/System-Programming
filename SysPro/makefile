OBJS	= BloomFilter.o datecmp.o date.o HashFunctions.o lista.o main.o operations.o SkipList.o
SOURCE	= BloomFilter.cpp datecmp.cpp date.cpp HashFunctions.cpp lista.cpp main.cpp operations.cpp SkipList.cpp
HEADER	= Citizen.hpp dentro.h operations.h Session.h SkipList.h BloomFilter.h datecmp.h Date.h HashFunctions.h lista.h
OUT	= diseaseMonitor
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

BloomFilter.o: BloomFilter.cpp
	$(CC) $(FLAGS) BloomFilter.cpp 

datecmp.o: datecmp.cpp
	$(CC) $(FLAGS) datecmp.cpp 

date.o: date.cpp
	$(CC) $(FLAGS) date.cpp 

HashFunctions.o: HashFunctions.cpp
	$(CC) $(FLAGS) HashFunctions.cpp 

lista.o: lista.cpp
	$(CC) $(FLAGS) lista.cpp 

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp 

operations.o: operations.cpp
	$(CC) $(FLAGS) operations.cpp 

SkipList.o: SkipList.cpp
	$(CC) $(FLAGS) SkipList.cpp 


clean:
	rm -f $(OBJS) $(OUT)
