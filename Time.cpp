#include "Time.h"

std::string Time::setTime(int hr, int min) {
    if (hr < 0 || hr > 23) {
        return "Hour out of limits";
    }

    if (min < 0 || min > 59) {
        return "Minute out of limits";
    }
    hour = hr;
    minute = min;
    return "";
}


std::string Time::setTime(const std::string &time) {
    std::istringstream input(time);
    return input >> *this;
}


std::string Time::getTime() const {
    std::ostringstream time;
    time << std::setw(2) << std::setfill('0') << getHour() << ":";
    time << std::setw(2) << std::setfill('0') << getMinute();
    return time.str();
}


bool Time::operator<(const Time &inputTime) const {
    if (getHour() < inputTime.getHour()) {
        return true;
    }
    if (getHour() == inputTime.getHour()) {
        if (getMinute() < inputTime.getMinute()) {
            return true;
        }
    }
    return false;
}


void Time::operator+=(const Time &addTime) {
    int newTimeHour, newTimeMinute;

    std::string resultOfAddition = this->operator+(addTime);
    newTimeHour = stoi(resultOfAddition.substr(0, 2));
    newTimeMinute = stoi(resultOfAddition.substr(3, resultOfAddition.length()-1));

    setTime(newTimeHour, newTimeMinute);
}


void Time::operator-=(const Time &subTime) {
    int currentTimeHour = getHour();
    int currentTimeMinute = getMinute();

    currentTimeHour -= subTime.getHour();
    currentTimeMinute -= subTime.getMinute();

    if (currentTimeMinute < 0) {
        currentTimeHour -= 1;
        currentTimeMinute = 60 + currentTimeMinute;
    }
    if (currentTimeHour < 0) {
        currentTimeHour = 24 + currentTimeHour;
    }

    setTime(currentTimeHour, currentTimeMinute);
}


std::string Time::operator+(const Time &newTime) const {
    std::ostringstream finalTime;
    unsigned int currentTimeHour = getHour();
    unsigned int currentTimeMinute = getMinute();

    currentTimeMinute += newTime.getMinute();
    currentTimeHour += newTime.getHour() +  currentTimeMinute / 60;

    if (currentTimeHour >= 24) {
        currentTimeHour = currentTimeHour % 24;
    }

    if (currentTimeMinute >= 60) {
        currentTimeMinute = currentTimeMinute % 60;
    }

    finalTime << std::setw(2) << std::setfill('0') << currentTimeHour << ":";
    finalTime << std::setw(2) << std::setfill('0') << currentTimeMinute;
    return finalTime.str();
}


std::string operator>>(std::istringstream &input, Time &time) {
    char delimiter;
    int hour, minute;
    if (input >> hour >> delimiter) {
        if (delimiter != ':') {
            return "Time has wrong format";
        }
        if (input >> minute) {
            return time.setTime(hour, minute);
        }
    }
    return "Time has wrong format";
}