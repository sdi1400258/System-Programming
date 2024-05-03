#include <ctime>
#include <sstream>

#include "Date.h"

const unsigned int day_secs = 86400;

unsigned int Date::add_sec = 0;

Date::Date() : infotime({}) {
    // current date/time based on current system
    time_t now = time(0);

    tm *ltm = localtime(&now);

    stringstream ss;

    if (ltm->tm_mday < 10) {
        ss << "0" << ltm->tm_mday << "-";
    } else if (ltm->tm_mday > 10) {
        ss << ltm->tm_mday << "-";
    }
    if ((1 + ltm->tm_mon) < 10) {
        ss << "0" << 1 + ltm->tm_mon << "-";
    } else if ((1 + ltm->tm_mon) > 10) {
        ss << 1 + ltm->tm_mon << "-";
    }
    ss << 1900 + ltm->tm_year;

    string date1 = ss.str();

    string day1 = date1.substr(0, 2); // DD-MM-YYYY
    string month1 = date1.substr(3, 2);
    string year1 = date1.substr(6, 4);

    int iday = atoi(day1.c_str());
    int imonth = atoi(month1.c_str());
    int iyear = atoi(year1.c_str());

    day_set(iday);
    mon_set(imonth);
    year_set(iyear);
}

Date::Date(int _s = 0) : infotime({}) {
    add_sec += _s;
    set(add_sec);
}

Date::Date(string date1) : infotime({}) { // DD/MM/YYYY
    string day1 = date1.substr(0, 2); // DD-MM-YYYY
    string month1 = date1.substr(3, 2);
    string year1 = date1.substr(6, 4);

    int iday = atoi(day1.c_str());
    int imonth = atoi(month1.c_str());
    int iyear = atoi(year1.c_str());

    day_set(iday);
    mon_set(imonth);
    year_set(iyear);
}

//Set xrono

void Date::set() {
    time_t unix_time;
    time(&unix_time);
    infotime = *localtime(&unix_time);
}

//set xronos ++ deuterolepta

void Date::set(unsigned int s) {
    time_t unix_time;
    time(&unix_time);
    unix_time += s;
    infotime = *localtime(&unix_time);
}

//set xronos 

void Date::set(const time_t& t) {
    infotime = *localtime(&t);
}

void Date::sec_set(const int x) {
    infotime.tm_sec = x;
}

void Date::min_set(const int x) {
    infotime.tm_min = x;
}

void Date::hour_set(const int x) {
    infotime.tm_hour = x;
}

void Date::day_set(const int x) {
    infotime.tm_mday = x;
}

void Date::mon_set(const int x) {
    infotime.tm_mon = x - 1;
}

void Date::weekday_set(const int x) {
    infotime.tm_wday = x;
}

void Date::year_set(const int x) {
    infotime.tm_year = x - 1900;
}

void Date::yearday_set(const int x) {
    infotime.tm_yday = x;
}

void Date::daylightsavingtime_set(const int x) {
    infotime.tm_isdst = x;
}

int Date::get_sec() const {
    return infotime.tm_sec;
}

int Date::get_min() const {
    return infotime.tm_min;
}

int Date::get_hour() const {
    return infotime.tm_hour;
}

int Date::get_day() const {
    return infotime.tm_mday;
}

int Date::get_mon() const {
    return infotime.tm_mon;
}

int Date::get_weekday() const {
    return infotime.tm_wday;
}

int Date::get_yearday() const {
    return infotime.tm_yday;
}

int Date::get_year() const {
    return infotime.tm_year;
}

int Date::get_daylightsavingtime() const {
    return infotime.tm_isdst;
}

const string Date::get_str(const char * format) {
    strftime(buffer, DATE_STRINGBUFF, format, &infotime);
    return buffer;
}

void Date::print() {

}