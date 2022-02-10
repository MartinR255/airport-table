#include "InformationTable.h"
#include <memory>


InformationTable::InformationTable(tableType type) {
    createTable(type);
}


int InformationTable::createTable (tableType t) {
    //chose file to read from
    std::string fileName;
    if (t == ARRIVALS) {
        fileName = "arrivals.txt";
        type = ARRIVALS;
    } else {
        fileName = "departures.txt";
        type = DEPARTURES;
    }

    //open file
    const std::string filePath = R"(E:\Prog\C++\Airport\utils\)" + fileName;
    std::fstream File;
    File.open(filePath, std::ios::in);

    if (!File) {
        cout << "Can not open file " << fileName << endl;
        return 1;
    }

    int flightTimeHour;
    std::string flightData, delimiter = ":";
    std::unique_ptr<FlightsAtHour> listPointer;

    //fetch data and put them into data structure;
    while (getline(File, flightData)) {
        flightTimeHour = stoi(flightData.substr(0, flightData.find(delimiter)));

        if (flightTimeHour >= 0 && flightTimeHour <= 23) {
            if (timeTable.find(flightTimeHour) == timeTable.end()) {
                listPointer = std::make_unique<FlightsAtHour>();
                timeTable.insert(
                        std::pair<int, std::unique_ptr<FlightsAtHour>>(flightTimeHour, listPointer.release()));
            }
            timeTable.at(flightTimeHour)->addFlight(flightData);
        }
    }
    File.close();
    return 0;
}


std::string InformationTable::getTable(int begin, int end, const std::string& location, const std::string& airline) {
    if (begin < 0 || end < 0 || begin > 23 || end > 23 || begin > end) {
        return "";
    }

    std::ostringstream flightTab;
    std::string flightsAtCertainHour = "";
    for (int position = begin; position <= end; position++) {
        auto iter = timeTable.find(position);
        if (iter != timeTable.end() && iter->second->getNumberOfFlights() > 0) {
            flightsAtCertainHour = timeTable.at(position)->getAllFlightsAtHour(location, airline);
            if (flightTab.tellp() != 0 && !flightsAtCertainHour.empty()) {
                flightTab << '\n';
            }
            flightTab << flightsAtCertainHour;
        }
    }
    return flightTab.str();
}


bool isNumber(const std::string& input) {
    if (input.empty()) {
        return false;
    }

    for (char character : input) {
        if (character > '9' || character < '0') {
            return false;
        }
    }
    return true;
}


int InformationTable::addToTable(const std::string& time, const std::string& location,
                                 const std::string& airline, const std::string& gate,
                                 const std::string& flightId) {

    std::string delimiter = ":";
    std::string hourString = time.substr(0, time.find(delimiter));
    if (isNumber(hourString) == false) {
        return 1;
    }

    int hour = stoi(hourString);
    std::ostringstream flightData;
    flightData << time << ";" << location << ";" << airline << ";" << gate << ";" << flightId;
    if (hour >= 0 && hour <= 23) {
        std::unique_ptr<FlightsAtHour> listPointer;
        if (timeTable.find(hour) == timeTable.end()) {
            listPointer = std::make_unique<FlightsAtHour>();
            timeTable.insert(
                    std::pair<int, std::unique_ptr<FlightsAtHour>>(hour, listPointer.release()));
        }
        return timeTable.at(hour)->addFlight(flightData.str());
    }
    return 1;
}


int InformationTable::removeFlightFromTable(const std::string& flightId, int hour) {
    int response;
    if (timeTable.find(hour) != timeTable.end()) {
        response = timeTable.at(hour).get()->removeFlight(flightId);
        if (response == 1) {
            return 1;
        }
        return 0;
    }
    //if hour does not exist in flight timetable search through
    // whole table for flight with flight id
    for (auto & iter : timeTable) {
        response = iter.second->removeFlight(flightId);
        if (response == 0) {
            return 0;
        }
    }
    return 1;
}


int InformationTable::emptyTable() {
    if (tableIsEmpty()) {
        return 1;
    }
    for (auto & iter : timeTable) {
        iter.second->removeAllFlights();
    }
    return 0;
}


unsigned int InformationTable::getNumberOfFlights() {
    unsigned int count = 0;
    for (auto & iter : timeTable) {
        count += iter.second->getNumberOfFlights();
    }

    return count;
}


int InformationTable::addDelayToFlight(const std::string& flightId, const std::string& time) {
    for (auto & iter : timeTable) {
        if (iter.second->addDelayToFlight(flightId, time) == 0) {
            return 0;
        }
    }
    return 1;
}


Flight* InformationTable::findFlight(const std::string& flightId) {
    for (auto & iter : timeTable) {
        auto flightInQueue = iter.second->findFlight(flightId);
        if (flightInQueue->getFlightId() != "NULL") {
            return flightInQueue;
        }
    }
    return nullptr;
}

