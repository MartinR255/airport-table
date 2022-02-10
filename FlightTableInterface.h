#pragma once
#include "InformationTable.h"

class FlightTableInterface {
    std::unique_ptr<InformationTable> tableArrivals;
    std::unique_ptr<InformationTable> tableDepartures;

    //login
    bool inSystem = false; //if we want to add flight to table we must have rights to do so
    std::map<std::string, std::string> userDataStructure;
    int fetchUserData();
    bool validLoginData(const std::string& name, const std::string& passwd);

    public:
        FlightTableInterface();
        ~FlightTableInterface();
        int addToTable(tableType type, const std::string& time, const std::string& location,
                       const std::string& airline, const std::string& gate, const std::string& flightId);
        int removeFlightFromTable(tableType type, const std::string& flightId, int hour=-1);
        int emptyTable(tableType type) ;
        int resetTables();
        int setFlightDelay(tableType type, const std::string& flightId, const std::string& time);


        //getters
        std::string getTable(tableType type, const std::string& filters = "");
        int getNumberOfFlights(tableType type);
        std::string findFlight(tableType type, const std::string& flightId);


        int logIn(const std::string& name, const std::string& passwd);
        int logOut();
        bool loggedIn() const { return inSystem; };
};