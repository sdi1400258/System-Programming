#ifndef DATE_H
#define DATE_H

#include <iostream>

#define DATE_STRINGBUFF 100 

#define DATE_FORMAT "%A, %d %B %Y"

extern const unsigned int day_secs;

using namespace std;

class Date {
    struct tm infotime;
    static unsigned int add_sec;
    char buffer[DATE_STRINGBUFF];
public:
    Date();
    Date(int);
    Date(string);

    void set(); // Set xronos

    void set(unsigned int); //set xrono me deuterolepta

    void set(const time_t&); //set sugkekrimeno xrono 

    void sec_set(const int);
    void min_set(const int);
    void hour_set(const int);
    void day_set(const int); // 0...30
    void mon_set(const int); // 1...12
    void weekday_set(const int);
    void yearday_set(const int); // 0...365
    void daylightsavingtime_set(const int);
    void year_set(const int);

    int get_sec() const;
    int get_min() const;
    int get_hour() const;
    int get_day() const;
    int get_mon() const;
    int get_weekday() const;
    int get_yearday() const;
    int get_year() const;
    int get_daylightsavingtime() const;
    const string get_str(const char * _format = DATE_FORMAT);
    void print();
};

#endif

