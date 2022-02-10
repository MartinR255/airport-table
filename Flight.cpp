#include "Flight.h"


Flight::Flight(const std::string& flightData) {
    if (checkIfValidData(flightData)) {
        std::istringstream streamData(flightData);
        char delimiter = ';';
        string substringData;
        int round = 0;

        while (getline(streamData, substringData, delimiter)) {
            switch(round) {
                case 0:
                    break;
                case 1:
                    location = correctionOfFlightLocation(substringData);
                    break;
                case 2:
                    airline = correctionOfName(substringData);
                    break;
                case 3:
                    gate = substringData;
                    break;
                default:
                    if (notInSpecialChars(substringData.at(substringData.size()-1)))
                        flightId = substringData;
                    else
                        flightId = substringData.substr(0, substringData.size()-1);
                    break;
            }
            round ++;
        }
    } else {
        flightTime.setTime("00:00");
    }
}


bool notInSpecialChars(char ch) {
    char specialChars[] = { '\r', '\n' };
    for (char specialChar : specialChars) {
        if (ch == specialChar) {
            return false;
        }
    }
    return true;
}

std::string correctionOfFlightLocation(const std::string& location) {
    std::string city, extraLetters, separator = " ";
    std::ostringstream result;
    city = location.substr(0, location.find(separator));
    extraLetters = location.substr(location.find(separator)+1, city.length());
    result << correctionOfName(city);

    if (city != extraLetters) {
        std::transform(extraLetters.begin(), extraLetters.end(), extraLetters.begin(),
                       [](unsigned char c) -> unsigned char { return std::toupper(c); });
        result << " " << extraLetters;
    }
    std::string text = result.str();
    return result.str();
}


std::string correctionOfName(const std::string& name) {
    std::string result, separator = " ";
    bool newWord = true;
    for (char character : name) {
        if (character == ' ') {
            result += character;
            newWord = true;
        } else if (newWord) {
            result += std::toupper(character);
            newWord = false;
        } else {
            result += std::tolower(character);
        }
    }
    return result;
}


bool  Flight::validTime(const std::string& time) {
    if (time.empty())
        return false;

    istringstream input(time);
    if ((input >> flightTime).empty()) {
        return true;
    }

    return false;
}


bool  Flight::onlyAlphabetChars(const std::string& data) {
    if (data.empty())
        return false;
    for (char character : data) {
        if (character < 'a' && character > 'Z' || character > 'z' || character < 'A'
        && character != ' ') {
            return false;
        }
    }
    return true;
}


bool  Flight::validGate(const std::string& gate) {
    if (gate.empty() || gate.length() > 3)
        return false;
    return true;
}


bool  Flight::validId(const std::string& id) {
    if (id.empty() || id.length() < 5)
        return false;

    string strLetter;
    for (char letter : id.substr(0, 2)) {
        strLetter = letter;
        if (letter == ' ' || !onlyAlphabetChars(strLetter))
            return false;
    }

    for (char num : id.substr(2, id.length()-1)) {
        if ((num < '0' || num > '9') && notInSpecialChars(num))
            return false;
    }
    return true;
}


bool Flight::checkIfValidData(const std::string& data) {
    if (data.empty())
        return false;

    std::istringstream streamData(data);
    char delimiter = ';';
    string substringData;
    int position = 0;
    while (getline(streamData, substringData, delimiter)) {
        validTime(substringData);
        if (position == 0 && !validTime(substringData)) {
            return false;
        }
        else if ((position == 1 || position == 2) && !onlyAlphabetChars(substringData)) {
            return false;
        }
        else if (position == 3 && !validGate(substringData)) {
            return false;
        }
        else if (position == 4 && !validId(substringData)) {
            return false;
        }
        position ++;
    }
    return true;
}


std::string Flight::getFlightInfo(bool showTimeWithDelay) {
    ostringstream output;
    if (showTimeWithDelay) {
        output << getFlightTimeWithDelay() << "  ";
    } else {
        output << getFlightTime() << "  ";
    }
    output << getLocation() << "  ";
    output << getAirline() << "  ";
    output << getGate() << "  ";
    output << getFlightId() << "  ";
    output << getStatus();
    return output.str();
}

FlightStages Flight::setStatus(FlightStages s) {
    status = s;
    return status;
}


FlightStages Flight::addDelayToFlight(Time &dTime) {
    delayTime.setTime(delayTime + dTime);
    if (delayTime.getHour() >= 10 && delayTime.getMinute() > 0) {
        delayTime.setTime("00:00");
        return setStatus(CANCELLED);
    }
    return setStatus(DELAYED);
}


std::string Flight::getFlightTimeWithDelay() {
    return flightTime + delayTime;
}