#pragma once
#include "FlightsAtHour.h"


enum tableType {ARRIVALS, DEPARTURES};
bool isNumber(const std::string& input);


class InformationTable {
    tableType type; //departures or arrivals
    std::map<int, std::unique_ptr<FlightsAtHour>> timeTable;


    public:
        InformationTable() = default;
        InformationTable(tableType type);
        ~InformationTable() { emptyTable(); };


        int createTable (tableType t);
        int addToTable(const std::string& time, const std::string& location, const std::string& airline,
                       const std::string& gate, const std::string& flightId);
        int removeFlightFromTable(const std::string& flightId, int hour=-1);
        int emptyTable();
        int addDelayToFlight(const std::string& flightId, const std::string& time);


        //getters
        std::string getTable(int begin = 0, int end = 23, const std::string& location = "",
                             const std::string& airline = "");
        unsigned int getNumberOfFlights();
        tableType getTableType() { return type; };
        bool tableIsEmpty() { return (getNumberOfFlights() == 0) ? true : false; };
        Flight* findFlight(const std::string& flightId);

};


