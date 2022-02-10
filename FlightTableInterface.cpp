#include "FlightTableInterface.h"


FlightTableInterface::FlightTableInterface() {
    tableArrivals = std::make_unique<InformationTable>(ARRIVALS);
    tableDepartures = std::make_unique<InformationTable>(DEPARTURES);
    fetchUserData();
}

FlightTableInterface::~FlightTableInterface() {
    tableArrivals.release();
    tableDepartures.release();
}


int FlightTableInterface::fetchUserData() {
    //open file
    const std::string filePath = R"(E:\Prog\C++\Airport\utils\passwd.txt)";
    std::fstream File;
    File.open(filePath, std::ios::in);

    if (!File) {
        cout << "Can not open passwd file " << endl;
        return 1;
    }

    std::string userData, passwd, delimiter = ":";

    //fetch data and put them into data structure;
    while (getline(File, userData)) {
        //check if string end with some special characters (\r, \n, ...) and cut them of
        passwd = userData.substr(userData.find(delimiter) + 1, userData.length());
        if (notInSpecialChars(passwd.at(passwd.size() - 1)) == false)
            passwd = passwd.substr(0, passwd.size() - 1);

        userDataStructure.insert(std::pair<std::string, std::string>(
                userData.substr(0, userData.find(delimiter)), passwd));
    }
    return 0;
}


bool FlightTableInterface::validLoginData(const std::string& name, const std::string& passwd) {
    for (auto &data : userDataStructure) {
        if (data.first == name && data.second == passwd) {
            return true;
        }
    }
    return false;
}


int FlightTableInterface::logIn(const std::string& name, const std::string& passwd) {
    if (loggedIn() || validLoginData(name, passwd) == false) {
        return 1;
    }
    inSystem = true;
    return 0;
}


int FlightTableInterface::logOut() {
    if (loggedIn() == false) {
        return 1;
    }
    inSystem = false;
    return 0;
}


std::string subString(const std::string &text, int element, char del) {
    std::string sub_text= "";
    int count = 1;
    for (char character : text){
        if (character == del) {
            if (count == element) {
                break;
            }
            count++;
            sub_text = "";
            continue;
        }
        sub_text += character;
    }
    if (count < element) return "";
    return sub_text;
}


char findSeparator(const std::string& text) {
    for (char ch : text) {
        if (ch == '=') {
            return ch;
        }
    }
    return '1';
}


int formTime(const std::string& time) {
    int result = -1;
    if (time.length() == 1 || time.length() == 2 && isNumber(time)) {
        result = stoi(time);
    }
    return result;
}


std::string FlightTableInterface::getTable(tableType type, const std::string& filters) {
    //filters example "time=00:00-10:00;location=Stuttgart;airline=Turkish Airlines"
    std::string filterArg1, filterArg2, currentFilters, location = "", airline = "";
    bool meetCriteria = true;
    char separator = ';', filterSeparator = '=';
    int position = 1, beginTime = 0, endTime = 23;

    while (true) {
        currentFilters = subString(filters, position, separator);
        filterSeparator = findSeparator(currentFilters);

        if (filterSeparator != '1') {
            filterArg1 = subString(currentFilters, 1, filterSeparator);
            filterArg2 = subString(currentFilters, 2, filterSeparator);

            if (filterArg1 == "time") {
                beginTime = formTime(subString(filterArg2, 1, '-'));
                if (beginTime == -1) {
                    beginTime = 0;
                }
                endTime = formTime(subString(filterArg2, 2, '-'));
                if (endTime == -1) {
                    endTime = 23;
                }
            } else if (filterArg1 == "location" ) {
                location = correctionOfFlightLocation(filterArg2);
            } else if (filterArg1 == "airline" ) {
                airline = correctionOfName(filterArg2);
            }
        }

        if (currentFilters.empty() || meetCriteria == false) {
            break;
        }
        position++;
    }

    if (type == ARRIVALS) {
        return tableArrivals->getTable(beginTime, endTime, location, airline);
    }
    return tableDepartures->getTable(beginTime, endTime, location, airline);
}


int FlightTableInterface::addToTable(tableType type, const std::string& time, const std::string& location,
               const std::string& airline, const std::string& gate, const std::string& flightId) {
    if (loggedIn()) {
        if (type == ARRIVALS) {
            return tableArrivals->addToTable(time, location, airline, gate, flightId);
        } else {
            return tableDepartures->addToTable(time, location, airline, gate, flightId);
        }
    }
    return 1;
}


int FlightTableInterface::removeFlightFromTable(tableType type, const std::string& flightId, int hour) {
    if (loggedIn()) {
        if (type == ARRIVALS) {
            return tableArrivals->removeFlightFromTable(flightId, hour);
        } else {
            return tableDepartures->removeFlightFromTable(flightId, hour);
        }
    }
    return 1;
}


int FlightTableInterface::emptyTable(tableType type) {
    if (loggedIn()) {
        if (type == ARRIVALS) {
            return tableArrivals->emptyTable();
        } else {
            return tableDepartures->emptyTable();
        }
    }
    return 1;
}


int FlightTableInterface::resetTables() {
    if (loggedIn()) {
        emptyTable(ARRIVALS);
        emptyTable(DEPARTURES);
        tableArrivals = std::make_unique<InformationTable>(ARRIVALS);
        tableDepartures = std::make_unique<InformationTable>(DEPARTURES);
        return 0;
    }
    return 1;
}


int FlightTableInterface::getNumberOfFlights(tableType type) {
    if (type == ARRIVALS) {
        return tableArrivals->getNumberOfFlights();
    }
    return tableDepartures->getNumberOfFlights();
}


int FlightTableInterface::setFlightDelay(tableType type, const std::string& flightId, const std::string& time) {
    if (loggedIn()) {
        if (type == ARRIVALS) {
            return tableArrivals->addDelayToFlight(flightId, time);
        }
        return tableDepartures->addDelayToFlight(flightId, time);
    }
    return 1;
}


std::string FlightTableInterface::findFlight(tableType type, const std::string& flightId) {
    std::ostringstream result;
    Flight* flight;
    if (type == ARRIVALS) {
        flight = tableArrivals->findFlight(flightId);
        if (flight != nullptr) {
            result << flight->getFlightInfo();
        }
    } else if (type == DEPARTURES) {
        flight = tableDepartures->findFlight(flightId);
        if (flight != nullptr) {
            result << flight->getFlightInfo();
        }
    }

    return result.str();
}