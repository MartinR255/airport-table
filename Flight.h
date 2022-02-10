#pragma once
#include <fstream>
#include <algorithm>
#include "Time.h"

//using std::string;
using namespace std;

enum FlightStages { SCHEDULED, BOARDING, CHECK_IN, DELAYED, CANCELLED, TAKE_OFF, LANDED, ON_TIME};
bool notInSpecialChars(char ch);
std::string correctionOfFlightLocation(const std::string& location);
std::string correctionOfName(const std::string& name);

class Flight {

    Time flightTime;
    Time delayTime;
    std::string location = "NULL";
    std::string flightId = "NULL";
    std::string gate = "NULL";
    std::string airline= "NULL";
    FlightStages status = SCHEDULED;


    public:
        explicit Flight(const string& flightData);
        Flight() = default;


        //getter methods
        std::string getLocation() { return location; };
        std::string getFlightId() const { return flightId; } ;
        std::string getGate() { return gate; };
        std::string getAirline() { return airline; };
        FlightStages getStatus() { return status; };
        std::string getFlightInfo(bool showTimeWithDelay = false);
        std::string getFlightTimeWithDelay();
        std::string getFlightTime() { return flightTime.getTime(); };


        //validation methods
        bool checkIfValidData(const std::string& data);
        bool validTime(const std::string& time);
        static bool onlyAlphabetChars(const std::string& data);
        bool validGate(const std::string& gate);
        bool validId(const std::string& id);


        //setter methods
        FlightStages setStatus(FlightStages s); //change current status of flight
        FlightStages addDelayToFlight(Time &dTime);
};


