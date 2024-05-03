OBJS	= BloomFilter.o datecmp.o date.o HashFunctions.o lista.o main.o Country.o Disease.o operations.o Session.o SkipList.o
SOURCE	= BloomFilter.cpp datecmp.cpp date.cpp HashFunctions.cpp lista.cpp main.cpp Country.cpp Disease.cpp operations.cpp Session.cpp SkipList.cpp
HEADER	= Citizen.hpp Country.h dentro.h Disease.h operations.h Session.h SkipList.h BloomFilter.h Country.hpp datecmp.h Date.h Disease.hpp HashFunctions.h lista.h
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

Country.o: Country.cpp
	$(CC) $(FLAGS) Country.cpp 

Disease.o: Disease.cpp
	$(CC) $(FLAGS) Disease.cpp 

operations.o: operations.cpp
	$(CC) $(FLAGS) operations.cpp 

Session.o: Session.cpp
	$(CC) $(FLAGS) Session.cpp 

SkipList.o: SkipList.cpp
	$(CC) $(FLAGS) SkipList.cpp 


clean:
	rm -f $(OBJS) $(OUT)
