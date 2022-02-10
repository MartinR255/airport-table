#include "FlightsAtHour.h"


int FlightsAtHour::addFlight(const std::string& flightData) {
    std::unique_ptr<Flight> flight;
    flight = std::make_unique<Flight>(flightData);

    if (flight->getFlightId() == "NULL") {
        return 1;
    }

    if (listOfFlights.find(flight->getFlightId()) == listOfFlights.end()) {
        listOfFlights.insert(std::pair<std::string, std::unique_ptr<Flight>>(flight->getFlightId(), flight.get()));
        flight.release();
        return 0;
    }
    flight.release();
    return 1;
}


int FlightsAtHour::removeFlight(const std::string& flightId) {
    if (getNumberOfFlights() > 0 && listOfFlights.find(flightId) != listOfFlights.end()) {
        listOfFlights.at(flightId).release();
        listOfFlights.erase(flightId);
        return 0;
    }
    return 1;
}


int FlightsAtHour::removeAllFlights() {
    if (getNumberOfFlights() > 0) {
        for (auto & listOfFlight : listOfFlights) {
            listOfFlight.second.release();
        }
        listOfFlights.clear();
        return 0;
    }
    return 1;
}


Flight* FlightsAtHour::findFlight(const std::string& flightId) {
    std::map<std::string, std::unique_ptr<Flight>>::iterator iter = listOfFlights.find(flightId);

    if (iter == listOfFlights.end()) {
        std::unique_ptr<Flight> emptyFlight;
        emptyFlight = std::make_unique<Flight>();
        return emptyFlight.release();
    }
    return iter->second.get();
}


std::vector<Flight*> FlightsAtHour::sortFlightsByTime() {
    std::vector<std::vector<Flight *>> buckets(60);
    std::map<std::string, std::unique_ptr<Flight>>::iterator currentFlight = listOfFlights.begin();

    for (; currentFlight != listOfFlights.end(); ++currentFlight) {
        std::string flightTime = currentFlight->second->getFlightTime();
        int minute = stoi(flightTime.substr(3, flightTime.length()-1));
        buckets.at(minute).push_back(currentFlight->second.get());
    }

    std::vector<Flight *> result;
    auto currentBucket = buckets.begin();
    for (; currentBucket != buckets.end(); ++currentBucket) {
        if (!currentBucket->empty()) {
            auto flight = currentBucket->begin();
            for (; flight != currentBucket->end(); ++flight) {
                result.push_back(*flight);
            }
        }
    }
    return result;
}


string FlightsAtHour::getAllFlightsAtHour(const std::string& location, const std::string& airline) {
    std::ostringstream output;
    std::vector<Flight *> sortedFlightsList = sortFlightsByTime();
    std::string currentFlightLocation, currentFlightAirline;

    for (auto & currentPos : sortedFlightsList) {
        currentFlightLocation = (*currentPos).getLocation();
        currentFlightAirline = (*currentPos).getAirline();
        if (currentFlightLocation == location && currentFlightAirline == airline ||
            location.empty() && currentFlightAirline == airline  ||
            currentFlightLocation == location && airline.empty() ||
            location.empty() && airline.empty()) {

            if (output.tellp() != 0) {
                output << '\n';
            }
            output << (*currentPos).getFlightInfo(true);
        }
    }
    return output.str();
}


int FlightsAtHour::addDelayToFlight(const std::string &flightId, const std::string& time) {
    auto flight = listOfFlights.find(flightId);
    if (listOfFlights.find(flightId) != listOfFlights.end() && flight->second->getStatus() != CANCELLED) {
        std::unique_ptr<Time> dTime;
        dTime = std::make_unique<Time>();
        istringstream input(time);

        if ((input >> *dTime).empty()) {
            flight->second->addDelayToFlight(*dTime.release());
            return 0;
        }
        dTime.release();
        return 1;
    }
    return 1;
}
