OBJS	= BloomFilter.o ChildInfo.o date.o datecmp.o datevacc.o File.o HashFunctions.o lista.o main_travelmonitor.o main_vaccinemonitor.o operations.o operations_parent.o readerwriter.o readerwriter_all.o Session.o SessionParent.o SkipList.o TravelRequestList.o
SOURCE	= BloomFilter.cpp ChildInfo.cpp date.cpp datecmp.cpp datevacc.cpp File.cpp HashFunctions.cpp lista.cpp main_travelmonitor.cpp main_vaccinemonitor.cpp operations.cpp operations_parent.cpp readerwriter.cpp readerwriter_all.cpp Session.cpp SessionParent.cpp SkipList.cpp TravelRequestList.cpp
HEADER	= BloomFilter.h ChildInfo.h Citizen.hpp Country.hpp Date.h datecmp.h datevacc.h dentro.h Disease.hpp File.h HashFunctions.h lista.h operations.h operations_parent.h readerwriter.h readerwriter_all.h Session.h SessionParent.h SkipList.h TravelRequest.hpp TravelRequestList.h
OUT	= travelMonitor
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

BloomFilter.o: BloomFilter.cpp
	$(CC) $(FLAGS) BloomFilter.cpp -std=c++11

ChildInfo.o: ChildInfo.cpp
	$(CC) $(FLAGS) ChildInfo.cpp -std=c++11

date.o: date.cpp
	$(CC) $(FLAGS) date.cpp -std=c++11

datecmp.o: datecmp.cpp
	$(CC) $(FLAGS) datecmp.cpp -std=c++11

datevacc.o: datevacc.cpp
	$(CC) $(FLAGS) datevacc.cpp -std=c++11

File.o: File.cpp
	$(CC) $(FLAGS) File.cpp -std=c++11

HashFunctions.o: HashFunctions.cpp
	$(CC) $(FLAGS) HashFunctions.cpp -std=c++11

lista.o: lista.cpp
	$(CC) $(FLAGS) lista.cpp -std=c++11

main_travelmonitor.o: main_travelmonitor.cpp
	$(CC) $(FLAGS) main_travelmonitor.cpp -std=c++11

main_vaccinemonitor.o: main_vaccinemonitor.cpp
	$(CC) $(FLAGS) main_vaccinemonitor.cpp -std=c++11

operations.o: operations.cpp
	$(CC) $(FLAGS) operations.cpp -std=c++11

operations_parent.o: operations_parent.cpp
	$(CC) $(FLAGS) operations_parent.cpp -std=c++11

readerwriter.o: readerwriter.cpp
	$(CC) $(FLAGS) readerwriter.cpp -std=c++11

readerwriter_all.o: readerwriter_all.cpp
	$(CC) $(FLAGS) readerwriter_all.cpp -std=c++11

Session.o: Session.cpp
	$(CC) $(FLAGS) Session.cpp -std=c++11

SessionParent.o: SessionParent.cpp
	$(CC) $(FLAGS) SessionParent.cpp -std=c++11

SkipList.o: SkipList.cpp
	$(CC) $(FLAGS) SkipList.cpp -std=c++11

TravelRequestList.o: TravelRequestList.cpp
	$(CC) $(FLAGS) TravelRequestList.cpp -std=c++11


clean:
	rm -f $(OBJS) $(OUT)
