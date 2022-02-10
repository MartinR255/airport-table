#pragma once
#include <cstring>
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;


class Time {
    int minute = 0;
    int hour = 0;


    public:
        int getHour() const { return hour; };
        int getMinute() const { return minute; };
        std::string getTime() const;
        std::string setTime(int hr, int min) ;
        std::string setTime(const std::string &time);
        bool operator<(const Time &inputTime) const;
        void operator+=(const Time &addTime);
        void operator-=(const Time &subTime);
        std::string operator+(const Time &newTime) const;
};

std::string operator>>(std::istringstream &input, Time &time);