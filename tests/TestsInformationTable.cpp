// Copyright 2005, Google Inc.
// All rights reserved.


#include "../gtest/gtest.h"
#include "../InformationTable.h"

using namespace ::testing;

TEST (TestInformationTable, createTableArrivals) {
    InformationTable table(ARRIVALS);

    ASSERT_EQ(ARRIVALS, table.getTableType());
    ASSERT_EQ("04:35  Stuttgart  Austrian  F03  OS257  0\n"
              "08:15  Milan MXP  Ryanair  D10  FR111  0", table.getTable(0, 10));

    ASSERT_EQ("08:15  Milan MXP  Ryanair  D10  FR111  0", table.getTable(8, 8));

    ASSERT_EQ("04:35  Stuttgart  Austrian  F03  OS257  0\n"
              "08:15  Milan MXP  Ryanair  D10  FR111  0\n"
              "11:05  Rome FCO  Ryanair  G36  FR1741  0\n"
              "13:15  London STN  Ryanair  G21  FR4318  0\n"
              "13:40  Istanbul ISL  Turkish Airlines  F11  TK6217  0\n"
              "16:00  Warsaw  Austrian  F06  OS435  0\n"
              "16:10  Milan MXP  Austrian  F09  OS120  0\n"
              "21:10  Zurich  Austrian  F26  OS464  0", table.getTable());
}

TEST (TestInformationTable, createTableDepartures) {
    InformationTable table(DEPARTURES);

    ASSERT_EQ(DEPARTURES, table.getTableType());
    ASSERT_EQ("06:45  Warsaw  Austrian  F06  OS631  0\n"
              "09:05  Stuttgart  Austrian  F03  OS187  0\n"
              "13:15  London STN  Ryanair  G21  FR7364  0\n"
              "15:10  Istanbul ISL  Turkish Airlines  F11  TK6387  0\n"
              "17:45  Milan MXP  Ryanair  F10  FR214  0\n"
              "17:50  Milan MXP  Austrian  F09  OS515  0\n"
              "19:30  Rome FCO  Ryanair  F36  FR7191  0\n"
              "20:50  Zurich  Austrian  F26  OS565  0", table.getTable());
}

TEST (TestInformationTable, addValidFlight) {
    InformationTable table(ARRIVALS);

    ASSERT_EQ("04:35  Stuttgart  Austrian  F03  OS257  0\n"
              "08:15  Milan MXP  Ryanair  D10  FR111  0", table.getTable(0, 10));

    table.addToTable("2:20", "Zurich", "Austrian", "F26", "OS464");

    ASSERT_EQ("02:20  Zurich  Austrian  F26  OS464  0\n"
              "04:35  Stuttgart  Austrian  F03  OS257  0\n"
              "08:15  Milan MXP  Ryanair  D10  FR111  0", table.getTable(0, 10));
}

TEST (TestInformationTable, addTotalMessIfPossible) {
    InformationTable table(ARRIVALS);

    ASSERT_EQ("04:35  Stuttgart  Austrian  F03  OS257  0\n"
              "08:15  Milan MXP  Ryanair  D10  FR111  0", table.getTable(0, 10));

    table.addToTable("021324:202391", "zurich", "Austrian 123", "F2631", "OS464");

    ASSERT_EQ("04:35  Stuttgart  Austrian  F03  OS257  0\n"
              "08:15  Milan MXP  Ryanair  D10  FR111  0\n"
              "11:05  Rome FCO  Ryanair  G36  FR1741  0\n"
              "13:15  London STN  Ryanair  G21  FR4318  0\n"
              "13:40  Istanbul ISL  Turkish Airlines  F11  TK6217  0\n"
              "16:00  Warsaw  Austrian  F06  OS435  0\n"
              "16:10  Milan MXP  Austrian  F09  OS120  0\n"
              "21:10  Zurich  Austrian  F26  OS464  0", table.getTable());
}

TEST (TestInformationTable, tryToAddTotalMessyTime) {
    InformationTable table(ARRIVALS);

    ASSERT_EQ("04:35  Stuttgart  Austrian  F03  OS257  0\n"
              "08:15  Milan MXP  Ryanair  D10  FR111  0", table.getTable(0, 10));

    table.addToTable("021324:202391", "Zurich", "Austrian", "F26", "OS464");

    ASSERT_EQ("04:35  Stuttgart  Austrian  F03  OS257  0\n"
              "08:15  Milan MXP  Ryanair  D10  FR111  0\n"
              "11:05  Rome FCO  Ryanair  G36  FR1741  0\n"
              "13:15  London STN  Ryanair  G21  FR4318  0\n"
              "13:40  Istanbul ISL  Turkish Airlines  F11  TK6217  0\n"
              "16:00  Warsaw  Austrian  F06  OS435  0\n"
              "16:10  Milan MXP  Austrian  F09  OS120  0\n"
              "21:10  Zurich  Austrian  F26  OS464  0", table.getTable());
}

TEST (TestInformationTable, addInvalidHourOfFlight) {
    InformationTable table(ARRIVALS);

    ASSERT_EQ("04:35  Stuttgart  Austrian  F03  OS257  0\n"
              "08:15  Milan MXP  Ryanair  D10  FR111  0", table.getTable(0, 10));

    table.addToTable("", "Zurich", "Austrian", "F26", "OS464");

    ASSERT_EQ("04:35  Stuttgart  Austrian  F03  OS257  0\n"
              "08:15  Milan MXP  Ryanair  D10  FR111  0", table.getTable(0, 10));
}

TEST (TestInformationTable, removeExistingFlight) {
    InformationTable table(ARRIVALS);

    ASSERT_EQ("04:35  Stuttgart  Austrian  F03  OS257  0\n"
              "08:15  Milan MXP  Ryanair  D10  FR111  0", table.getTable(0, 10));

    ASSERT_EQ(0, table.removeFlightFromTable("OS257", 4));

    ASSERT_EQ("08:15  Milan MXP  Ryanair  D10  FR111  0", table.getTable(0, 10));
}

TEST (TestInformationTable, removeNonExistingFlight) {
    InformationTable table(ARRIVALS);

    ASSERT_EQ("04:35  Stuttgart  Austrian  F03  OS257  0\n"
              "08:15  Milan MXP  Ryanair  D10  FR111  0", table.getTable(0, 10));

    ASSERT_EQ(1, table.removeFlightFromTable("FR257", 4));

    ASSERT_EQ("04:35  Stuttgart  Austrian  F03  OS257  0\n"
              "08:15  Milan MXP  Ryanair  D10  FR111  0", table.getTable(0, 10));
}

TEST (TestInformationTable, removeExistingFlightButHourInputIsInvalid) {
    InformationTable table(ARRIVALS);

    ASSERT_EQ("04:35  Stuttgart  Austrian  F03  OS257  0\n"
              "08:15  Milan MXP  Ryanair  D10  FR111  0\n"
              "11:05  Rome FCO  Ryanair  G36  FR1741  0\n"
              "13:15  London STN  Ryanair  G21  FR4318  0\n"
              "13:40  Istanbul ISL  Turkish Airlines  F11  TK6217  0", table.getTable(0, 13));

    ASSERT_EQ(0, table.removeFlightFromTable("FR4318", 5));

    ASSERT_EQ("04:35  Stuttgart  Austrian  F03  OS257  0\n"
              "08:15  Milan MXP  Ryanair  D10  FR111  0\n"
              "11:05  Rome FCO  Ryanair  G36  FR1741  0\n"
              "13:40  Istanbul ISL  Turkish Airlines  F11  TK6217  0", table.getTable(0, 13));

    ASSERT_EQ(1, table.removeFlightFromTable("TK6218"));
    ASSERT_EQ(0, table.removeFlightFromTable("TK6217"));

    ASSERT_EQ("04:35  Stuttgart  Austrian  F03  OS257  0\n"
              "08:15  Milan MXP  Ryanair  D10  FR111  0\n"
              "11:05  Rome FCO  Ryanair  G36  FR1741  0", table.getTable(0, 13));
}

TEST (TestInformationTable, removeExistingFlightMultipleTimesWithWrongTimeInput) {
    InformationTable table(ARRIVALS);

    ASSERT_EQ("04:35  Stuttgart  Austrian  F03  OS257  0\n"
              "08:15  Milan MXP  Ryanair  D10  FR111  0", table.getTable(0, 10));

    ASSERT_EQ(0, table.removeFlightFromTable("OS257", -10));
    ASSERT_EQ(1, table.removeFlightFromTable("OS257", -10));
    ASSERT_EQ(1, table.removeFlightFromTable("OS257", 4));

    ASSERT_EQ("08:15  Milan MXP  Ryanair  D10  FR111  0", table.getTable(0, 10));
}

TEST (TestInformationTable, emptyTableWithFlights) {
    InformationTable table(ARRIVALS);

    ASSERT_EQ("04:35  Stuttgart  Austrian  F03  OS257  0\n"
              "08:15  Milan MXP  Ryanair  D10  FR111  0\n"
              "11:05  Rome FCO  Ryanair  G36  FR1741  0\n"
              "13:15  London STN  Ryanair  G21  FR4318  0\n"
              "13:40  Istanbul ISL  Turkish Airlines  F11  TK6217  0\n"
              "16:00  Warsaw  Austrian  F06  OS435  0\n"
              "16:10  Milan MXP  Austrian  F09  OS120  0\n"
              "21:10  Zurich  Austrian  F26  OS464  0", table.getTable());

    ASSERT_EQ(8, table.getNumberOfFlights());
    ASSERT_EQ(0, table.emptyTable());
    ASSERT_EQ("", table.getTable());
}

TEST (TestInformationTable, emptyTableWithNoFlights) {
    InformationTable table(ARRIVALS);

    ASSERT_EQ("04:35  Stuttgart  Austrian  F03  OS257  0\n"
              "08:15  Milan MXP  Ryanair  D10  FR111  0\n"
              "11:05  Rome FCO  Ryanair  G36  FR1741  0\n"
              "13:15  London STN  Ryanair  G21  FR4318  0\n"
              "13:40  Istanbul ISL  Turkish Airlines  F11  TK6217  0\n"
              "16:00  Warsaw  Austrian  F06  OS435  0\n"
              "16:10  Milan MXP  Austrian  F09  OS120  0\n"
              "21:10  Zurich  Austrian  F26  OS464  0", table.getTable());

    ASSERT_EQ(8, table.getNumberOfFlights());
    ASSERT_EQ(0, table.emptyTable());
    ASSERT_EQ("", table.getTable());
    ASSERT_EQ(0, table.getNumberOfFlights());
    ASSERT_EQ(1, table.removeFlightFromTable("isadjasiodj"));
    
    ASSERT_EQ(1, table.emptyTable());
    ASSERT_EQ("", table.getTable());
    ASSERT_EQ(0, table.getNumberOfFlights());
}

TEST (TestInformationTable, findFlightsInTable) {
    InformationTable table(ARRIVALS);

    ASSERT_EQ("21:10  Zurich  Austrian  F26  OS464  0",
              table.findFlight("OS464")->getFlightInfo());

    ASSERT_EQ(nullptr,table.findFlight("OS444"));
}


TEST (TestInformationTable, addDelayToFlights) {
    InformationTable table(ARRIVALS);

    ASSERT_EQ("04:35  Stuttgart  Austrian  F03  OS257  0\n"
              "08:15  Milan MXP  Ryanair  D10  FR111  0\n"
              "11:05  Rome FCO  Ryanair  G36  FR1741  0\n"
              "13:15  London STN  Ryanair  G21  FR4318  0\n"
              "13:40  Istanbul ISL  Turkish Airlines  F11  TK6217  0\n"
              "16:00  Warsaw  Austrian  F06  OS435  0\n"
              "16:10  Milan MXP  Austrian  F09  OS120  0\n"
              "21:10  Zurich  Austrian  F26  OS464  0", table.getTable());

    ASSERT_EQ(0, table.addDelayToFlight("TK6217", "0:20"));
    ASSERT_EQ(0, table.addDelayToFlight("OS464", "12:20"));
    ASSERT_EQ(0, table.addDelayToFlight("FR111", "3:20"));

    ASSERT_EQ("04:35  Stuttgart  Austrian  F03  OS257  0\n"
              "11:35  Milan MXP  Ryanair  D10  FR111  3\n"
              "11:05  Rome FCO  Ryanair  G36  FR1741  0\n"
              "13:15  London STN  Ryanair  G21  FR4318  0\n"
              "14:00  Istanbul ISL  Turkish Airlines  F11  TK6217  3\n"
              "16:00  Warsaw  Austrian  F06  OS435  0\n"
              "16:10  Milan MXP  Austrian  F09  OS120  0\n"
              "21:10  Zurich  Austrian  F26  OS464  4", table.getTable());


    ASSERT_EQ(0, table.addDelayToFlight("TK6217", "10:00"));
    ASSERT_EQ(1, table.addDelayToFlight("FR4318", "24:00"));

    ASSERT_EQ("04:35  Stuttgart  Austrian  F03  OS257  0\n"
              "11:35  Milan MXP  Ryanair  D10  FR111  3\n"
              "11:05  Rome FCO  Ryanair  G36  FR1741  0\n"
              "13:15  London STN  Ryanair  G21  FR4318  0\n"
              "13:40  Istanbul ISL  Turkish Airlines  F11  TK6217  4\n"
              "16:00  Warsaw  Austrian  F06  OS435  0\n"
              "16:10  Milan MXP  Austrian  F09  OS120  0\n"
              "21:10  Zurich  Austrian  F26  OS464  4", table.getTable());

}
