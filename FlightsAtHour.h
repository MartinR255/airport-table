#pragma once
#include "Flight.h"
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <memory>


class FlightsAtHour {
    std::map<std::string, std::unique_ptr<Flight>> listOfFlights;

    public:
        ~FlightsAtHour() { removeAllFlights(); };
        int addFlight(const std::string& flightData);
        int removeFlight(const std::string& flightId);
        int removeAllFlights();
        int addDelayToFlight(const std::string& flightId, const std::string& time);


        Flight* findFlight(const std::string& flightId);
        string getAllFlightsAtHour(const std::string& location = "", const std::string& airline = "");
        unsigned long getNumberOfFlights() const { return listOfFlights.size(); };
        std::vector<Flight*> sortFlightsByTime(); //bucket sort algorithm; returns sorted vector of all flights
};



