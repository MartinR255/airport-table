// Copyright 2005, Google Inc.
// All rights reserved.


#include "../gtest/gtest.h"
#include "../FlightTableInterface.h"

using namespace ::testing;

TEST(TestFlightInterface, addingValidFlights) {
    FlightTableInterface table;

    table.logIn("admin", "admin123");
    table.addToTable(ARRIVALS, "2:20", "Zurich", "Austrian", "F26", "OS464");

    ASSERT_EQ("02:20  Zurich  Austrian  F26  OS464  0\n"
              "04:35  Stuttgart  Austrian  F03  OS257  0\n"
              "08:15  Milan MXP  Ryanair  D10  FR111  0\n"
              "11:05  Rome FCO  Ryanair  G36  FR1741  0\n"
              "13:15  London STN  Ryanair  G21  FR4318  0\n"
              "13:40  Istanbul ISL  Turkish Airlines  F11  TK6217  0\n"
              "16:00  Warsaw  Austrian  F06  OS435  0\n"
              "16:10  Milan MXP  Austrian  F09  OS120  0\n"
              "21:10  Zurich  Austrian  F26  OS464  0", table.getTable(ARRIVALS, ""));

    table.addToTable(DEPARTURES, "15:20", "Dubai", "Emirates", "G26", "EM464");

    ASSERT_EQ("06:45  Warsaw  Austrian  F06  OS631  0\n"
              "09:05  Stuttgart  Austrian  F03  OS187  0\n"
              "13:15  London STN  Ryanair  G21  FR7364  0\n"
              "15:10  Istanbul ISL  Turkish Airlines  F11  TK6387  0\n"
              "15:20  Dubai  Emirates  G26  EM464  0\n"
              "17:45  Milan MXP  Ryanair  F10  FR214  0\n"
              "17:50  Milan MXP  Austrian  F09  OS515  0\n"
              "19:30  Rome FCO  Ryanair  F36  FR7191  0\n"
              "20:50  Zurich  Austrian  F26  OS565  0", table.getTable(DEPARTURES));
}

TEST(TestFlightInterface, addingInvalidFlights) {
    FlightTableInterface table;

    table.logIn("admin", "admin123");
    ASSERT_EQ(1, table.addToTable(ARRIVALS, "24:20", "Zurich", "Austrian", "F26", "OS464"));

    ASSERT_EQ("04:35  Stuttgart  Austrian  F03  OS257  0\n"
              "08:15  Milan MXP  Ryanair  D10  FR111  0\n"
              "11:05  Rome FCO  Ryanair  G36  FR1741  0\n"
              "13:15  London STN  Ryanair  G21  FR4318  0\n"
              "13:40  Istanbul ISL  Turkish Airlines  F11  TK6217  0\n"
              "16:00  Warsaw  Austrian  F06  OS435  0\n"
              "16:10  Milan MXP  Austrian  F09  OS120  0\n"
              "21:10  Zurich  Austrian  F26  OS464  0", table.getTable(ARRIVALS, ""));

    ASSERT_EQ(1, table.addToTable(DEPARTURES, "15:20", "Dubai", "Emirates", "G2612", "EM464"));

    ASSERT_EQ("06:45  Warsaw  Austrian  F06  OS631  0\n"
              "09:05  Stuttgart  Austrian  F03  OS187  0\n"
              "13:15  London STN  Ryanair  G21  FR7364  0\n"
              "15:10  Istanbul ISL  Turkish Airlines  F11  TK6387  0\n"
              "17:45  Milan MXP  Ryanair  F10  FR214  0\n"
              "17:50  Milan MXP  Austrian  F09  OS515  0\n"
              "19:30  Rome FCO  Ryanair  F36  FR7191  0\n"
              "20:50  Zurich  Austrian  F26  OS565  0", table.getTable(DEPARTURES));
}

TEST(TestFlightInterface, removingFlights) {
    FlightTableInterface table;

    ASSERT_EQ("04:35  Stuttgart  Austrian  F03  OS257  0\n"
              "08:15  Milan MXP  Ryanair  D10  FR111  0\n"
              "11:05  Rome FCO  Ryanair  G36  FR1741  0\n"
              "13:15  London STN  Ryanair  G21  FR4318  0\n"
              "13:40  Istanbul ISL  Turkish Airlines  F11  TK6217  0\n"
              "16:00  Warsaw  Austrian  F06  OS435  0\n"
              "16:10  Milan MXP  Austrian  F09  OS120  0\n"
              "21:10  Zurich  Austrian  F26  OS464  0", table.getTable(ARRIVALS, ""));

    table.logIn("admin", "admin123");
    ASSERT_EQ(0, table.removeFlightFromTable(ARRIVALS, "OS257"));
    ASSERT_EQ(0,table.removeFlightFromTable(ARRIVALS, "OS435"));
    ASSERT_EQ(0,table.removeFlightFromTable(ARRIVALS, "FR4318"));

    ASSERT_EQ("08:15  Milan MXP  Ryanair  D10  FR111  0\n"
              "11:05  Rome FCO  Ryanair  G36  FR1741  0\n"
              "13:40  Istanbul ISL  Turkish Airlines  F11  TK6217  0\n"
              "16:10  Milan MXP  Austrian  F09  OS120  0\n"
              "21:10  Zurich  Austrian  F26  OS464  0", table.getTable(ARRIVALS, ""));


    ASSERT_EQ("06:45  Warsaw  Austrian  F06  OS631  0\n"
              "09:05  Stuttgart  Austrian  F03  OS187  0\n"
              "13:15  London STN  Ryanair  G21  FR7364  0\n"
              "15:10  Istanbul ISL  Turkish Airlines  F11  TK6387  0\n"
              "17:45  Milan MXP  Ryanair  F10  FR214  0\n"
              "17:50  Milan MXP  Austrian  F09  OS515  0\n"
              "19:30  Rome FCO  Ryanair  F36  FR7191  0\n"
              "20:50  Zurich  Austrian  F26  OS565  0", table.getTable(DEPARTURES));

    ASSERT_EQ(0,table.removeFlightFromTable(DEPARTURES, "OS631"));
    ASSERT_EQ(0,table.removeFlightFromTable(DEPARTURES, "OS187"));
    ASSERT_EQ(0,table.removeFlightFromTable(DEPARTURES, "FR7364"));

    ASSERT_EQ("15:10  Istanbul ISL  Turkish Airlines  F11  TK6387  0\n"
              "17:45  Milan MXP  Ryanair  F10  FR214  0\n"
              "17:50  Milan MXP  Austrian  F09  OS515  0\n"
              "19:30  Rome FCO  Ryanair  F36  FR7191  0\n"
              "20:50  Zurich  Austrian  F26  OS565  0", table.getTable(DEPARTURES));

    ASSERT_EQ("", table.getTable(DEPARTURES, "time=0-13"));
}

TEST(TestFlightInterface, testRestartTables) {
    FlightTableInterface table;

    table.logIn("admin", "admin123");
    table.addToTable(ARRIVALS, "2:20", "Zurich", "Austrian", "F26", "OS464");

    ASSERT_EQ("02:20  Zurich  Austrian  F26  OS464  0\n"
              "04:35  Stuttgart  Austrian  F03  OS257  0\n"
              "08:15  Milan MXP  Ryanair  D10  FR111  0\n"
              "11:05  Rome FCO  Ryanair  G36  FR1741  0\n"
              "13:15  London STN  Ryanair  G21  FR4318  0\n"
              "13:40  Istanbul ISL  Turkish Airlines  F11  TK6217  0\n"
              "16:00  Warsaw  Austrian  F06  OS435  0\n"
              "16:10  Milan MXP  Austrian  F09  OS120  0\n"
              "21:10  Zurich  Austrian  F26  OS464  0", table.getTable(ARRIVALS, ""));

    table.resetTables();

    ASSERT_EQ("04:35  Stuttgart  Austrian  F03  OS257  0\n"
              "08:15  Milan MXP  Ryanair  D10  FR111  0\n"
              "11:05  Rome FCO  Ryanair  G36  FR1741  0\n"
              "13:15  London STN  Ryanair  G21  FR4318  0\n"
              "13:40  Istanbul ISL  Turkish Airlines  F11  TK6217  0\n"
              "16:00  Warsaw  Austrian  F06  OS435  0\n"
              "16:10  Milan MXP  Austrian  F09  OS120  0\n"
              "21:10  Zurich  Austrian  F26  OS464  0", table.getTable(ARRIVALS, ""));
}

TEST(TestFlightInterface, getFilteredTableWithOneFilter) {
    FlightTableInterface table;

    ASSERT_EQ("04:35  Stuttgart  Austrian  F03  OS257  0\n"
              "08:15  Milan MXP  Ryanair  D10  FR111  0", table.getTable(ARRIVALS, "time=0-10"));

    ASSERT_EQ("08:15  Milan MXP  Ryanair  D10  FR111  0\n"
              "16:10  Milan MXP  Austrian  F09  OS120  0", table.getTable(ARRIVALS, "location=milan mxp"));

    ASSERT_EQ("08:15  Milan MXP  Ryanair  D10  FR111  0\n"
              "11:05  Rome FCO  Ryanair  G36  FR1741  0\n"
              "13:15  London STN  Ryanair  G21  FR4318  0", table.getTable(ARRIVALS, "airline=ryanair"));
}

TEST(TestFlightInterface, getFilteredTable) {
    FlightTableInterface table;

    ASSERT_EQ("16:00  Warsaw  Austrian  F06  OS435  0\n"
              "16:10  Milan MXP  Austrian  F09  OS120  0\n"
              "21:10  Zurich  Austrian  F26  OS464  0", table.getTable(ARRIVALS, "time=16-23;airline=austrian"));

    ASSERT_EQ("16:00  Warsaw  Austrian  F06  OS435  0\n"
              "16:10  Milan MXP  Austrian  F09  OS120  0\n"
              "21:10  Zurich  Austrian  F26  OS464  0", table.getTable(ARRIVALS, "time=16;airline=austrian"));
}

TEST(TestFlightInterface, wrongFilterTests) {
    FlightTableInterface table;

    ASSERT_EQ("", table.getTable(ARRIVALS, "time=16-24;airline=austrian"));

    ASSERT_EQ("", table.getTable(ARRIVALS, "time=16;airline=austrian12"));

    ASSERT_EQ("", table.getTable(ARRIVALS, "time=16-23;airline=austrian;location=Los Angeles"));
}

TEST(TestFlightInterface, wrongFilterSyntaxTest) {
    FlightTableInterface table;

    ASSERT_EQ("04:35  Stuttgart  Austrian  F03  OS257  0\n"
              "08:15  Milan MXP  Ryanair  D10  FR111  0\n"
              "11:05  Rome FCO  Ryanair  G36  FR1741  0\n"
              "13:15  London STN  Ryanair  G21  FR4318  0\n"
              "13:40  Istanbul ISL  Turkish Airlines  F11  TK6217  0\n"
              "16:00  Warsaw  Austrian  F06  OS435  0\n"
              "16:10  Milan MXP  Austrian  F09  OS120  0\n"
              "21:10  Zurich  Austrian  F26  OS464  0", table.getTable(ARRIVALS, ";;;"));

    ASSERT_EQ("04:35  Stuttgart  Austrian  F03  OS257  0\n"
              "08:15  Milan MXP  Ryanair  D10  FR111  0\n"
              "11:05  Rome FCO  Ryanair  G36  FR1741  0\n"
              "13:15  London STN  Ryanair  G21  FR4318  0\n"
              "13:40  Istanbul ISL  Turkish Airlines  F11  TK6217  0\n"
              "16:00  Warsaw  Austrian  F06  OS435  0\n"
              "16:10  Milan MXP  Austrian  F09  OS120  0\n"
              "21:10  Zurich  Austrian  F26  OS464  0", table.getTable(ARRIVALS, "      "));

    ASSERT_EQ("04:35  Stuttgart  Austrian  F03  OS257  0\n"
              "08:15  Milan MXP  Ryanair  D10  FR111  0\n"
              "11:05  Rome FCO  Ryanair  G36  FR1741  0\n"
              "13:15  London STN  Ryanair  G21  FR4318  0\n"
              "13:40  Istanbul ISL  Turkish Airlines  F11  TK6217  0\n"
              "16:00  Warsaw  Austrian  F06  OS435  0\n"
              "16:10  Milan MXP  Austrian  F09  OS120  0\n"
              "21:10  Zurich  Austrian  F26  OS464  0", table.getTable(ARRIVALS, "time;location;airline"));

    ASSERT_EQ("04:35  Stuttgart  Austrian  F03  OS257  0\n"
              "08:15  Milan MXP  Ryanair  D10  FR111  0\n"
              "11:05  Rome FCO  Ryanair  G36  FR1741  0\n"
              "13:15  London STN  Ryanair  G21  FR4318  0\n"
              "13:40  Istanbul ISL  Turkish Airlines  F11  TK6217  0\n"
              "16:00  Warsaw  Austrian  F06  OS435  0\n"
              "16:10  Milan MXP  Austrian  F09  OS120  0\n"
              "21:10  Zurich  Austrian  F26  OS464  0", table.getTable(ARRIVALS, "time=;location=;airline="));

    ASSERT_EQ("04:35  Stuttgart  Austrian  F03  OS257  0\n"
              "08:15  Milan MXP  Ryanair  D10  FR111  0\n"
              "11:05  Rome FCO  Ryanair  G36  FR1741  0\n"
              "13:15  London STN  Ryanair  G21  FR4318  0\n"
              "13:40  Istanbul ISL  Turkish Airlines  F11  TK6217  0\n"
              "16:00  Warsaw  Austrian  F06  OS435  0\n"
              "16:10  Milan MXP  Austrian  F09  OS120  0\n"
              "21:10  Zurich  Austrian  F26  OS464  0", table.getTable(ARRIVALS, "time=aa-bb;location=;airline="));
}

TEST(TestFlightInterface, empryTableTest) {
    FlightTableInterface table;

    table.logIn("admin", "admin123");
    ASSERT_EQ("04:35  Stuttgart  Austrian  F03  OS257  0\n"
              "08:15  Milan MXP  Ryanair  D10  FR111  0\n"
              "11:05  Rome FCO  Ryanair  G36  FR1741  0\n"
              "13:15  London STN  Ryanair  G21  FR4318  0\n"
              "13:40  Istanbul ISL  Turkish Airlines  F11  TK6217  0\n"
              "16:00  Warsaw  Austrian  F06  OS435  0\n"
              "16:10  Milan MXP  Austrian  F09  OS120  0\n"
              "21:10  Zurich  Austrian  F26  OS464  0", table.getTable(ARRIVALS));

    ASSERT_EQ(0, table.emptyTable(ARRIVALS));
    ASSERT_EQ(1, table.emptyTable(ARRIVALS));
    ASSERT_EQ("", table.getTable(ARRIVALS));
}



//login tests
TEST (TestFlightInterface, loginTesting1) {
    FlightTableInterface table;

    ASSERT_EQ("04:35  Stuttgart  Austrian  F03  OS257  0\n"
              "08:15  Milan MXP  Ryanair  D10  FR111  0", table.getTable(ARRIVALS, "time=0-8"));


    ASSERT_EQ(1, table.addToTable(ARRIVALS, "2:20", "Zurich", "Austrian", "F26", "OS464"));
    ASSERT_EQ("04:35  Stuttgart  Austrian  F03  OS257  0\n"
              "08:15  Milan MXP  Ryanair  D10  FR111  0", table.getTable(ARRIVALS, "time=0-8"));

    table.logIn("admin", "admin123");
    ASSERT_EQ(0, table.addToTable(ARRIVALS, "2:20", "Zurich", "Austrian", "F26", "OS464"));
    table.logOut();

    ASSERT_EQ("02:20  Zurich  Austrian  F26  OS464  0\n"
              "04:35  Stuttgart  Austrian  F03  OS257  0\n"
              "08:15  Milan MXP  Ryanair  D10  FR111  0", table.getTable(ARRIVALS, "time=0-8"));
}

TEST (TestFlightInterface, loginTesting2) {
    FlightTableInterface table;

    ASSERT_EQ(1, table.logIn("tomas45", "123tomas"));
    ASSERT_FALSE(table.loggedIn());

    ASSERT_EQ(0, table.logIn("tomas45", "tomas123"));
    ASSERT_TRUE(table.loggedIn());

    ASSERT_EQ(1, table.logIn("tomas45", "tomas123"));

    ASSERT_EQ(0, table.logOut());
    ASSERT_EQ(1, table.logOut());
}


TEST (TestFlightInterface, emptyTableWithoutRights) {
    FlightTableInterface table;
    table.logIn("admin", "admin123");;

    ASSERT_EQ("04:35  Stuttgart  Austrian  F03  OS257  0\n"
              "08:15  Milan MXP  Ryanair  D10  FR111  0\n"
              "11:05  Rome FCO  Ryanair  G36  FR1741  0\n"
              "13:15  London STN  Ryanair  G21  FR4318  0\n"
              "13:40  Istanbul ISL  Turkish Airlines  F11  TK6217  0\n"
              "16:00  Warsaw  Austrian  F06  OS435  0\n"
              "16:10  Milan MXP  Austrian  F09  OS120  0\n"
              "21:10  Zurich  Austrian  F26  OS464  0", table.getTable(ARRIVALS));

    ASSERT_EQ(8, table.getNumberOfFlights(ARRIVALS));
    table.logOut();

    ASSERT_EQ(1, table.emptyTable(ARRIVALS));
    ASSERT_EQ("04:35  Stuttgart  Austrian  F03  OS257  0\n"
              "08:15  Milan MXP  Ryanair  D10  FR111  0\n"
              "11:05  Rome FCO  Ryanair  G36  FR1741  0\n"
              "13:15  London STN  Ryanair  G21  FR4318  0\n"
              "13:40  Istanbul ISL  Turkish Airlines  F11  TK6217  0\n"
              "16:00  Warsaw  Austrian  F06  OS435  0\n"
              "16:10  Milan MXP  Austrian  F09  OS120  0\n"
              "21:10  Zurich  Austrian  F26  OS464  0", table.getTable(ARRIVALS));
}

TEST (TestFlightInterface, emptyTableWithRights) {
    FlightTableInterface table;
    table.logIn("admin", "admin123");

    ASSERT_EQ("04:35  Stuttgart  Austrian  F03  OS257  0\n"
              "08:15  Milan MXP  Ryanair  D10  FR111  0\n"
              "11:05  Rome FCO  Ryanair  G36  FR1741  0\n"
              "13:15  London STN  Ryanair  G21  FR4318  0\n"
              "13:40  Istanbul ISL  Turkish Airlines  F11  TK6217  0\n"
              "16:00  Warsaw  Austrian  F06  OS435  0\n"
              "16:10  Milan MXP  Austrian  F09  OS120  0\n"
              "21:10  Zurich  Austrian  F26  OS464  0", table.getTable(ARRIVALS));

    ASSERT_EQ(8, table.getNumberOfFlights(ARRIVALS));
    ASSERT_EQ(0, table.emptyTable(ARRIVALS));
    ASSERT_EQ("", table.getTable(ARRIVALS));
    table.logOut();
}

TEST (TestFlightInterface, removeExistingFlightWithoutRights) {
    FlightTableInterface table;

    ASSERT_EQ("04:35  Stuttgart  Austrian  F03  OS257  0\n"
              "08:15  Milan MXP  Ryanair  D10  FR111  0", table.getTable(ARRIVALS, "time=0-8"));

    ASSERT_EQ(1, table.removeFlightFromTable(ARRIVALS, "OS257", 4));
    ASSERT_EQ("04:35  Stuttgart  Austrian  F03  OS257  0\n"
              "08:15  Milan MXP  Ryanair  D10  FR111  0", table.getTable(ARRIVALS, "time=0-8"));

    table.logIn("martin33", "martin123");
    ASSERT_EQ(0, table.removeFlightFromTable(ARRIVALS, "OS257", 4));
    ASSERT_EQ(1, table.removeFlightFromTable(ARRIVALS, "OS257", 4));
    ASSERT_EQ(1, table.removeFlightFromTable(ARRIVALS, "OS257"));
    ASSERT_EQ("08:15  Milan MXP  Ryanair  D10  FR111  0", table.getTable(ARRIVALS, "time=0-8"));
}

TEST (TestFlightInterface, findFlight) {
    FlightTableInterface table;

    ASSERT_EQ("04:35  Stuttgart  Austrian  F03  OS257  0", table.findFlight(ARRIVALS, "OS257"));
    ASSERT_EQ("", table.findFlight(ARRIVALS, "OS222"));
}


//tests delay
TEST (TestFlightInterface, setFiveHourDelayToFlight) {
    FlightTableInterface table;

    table.logIn("admin", "admin123");
    table.addToTable(ARRIVALS, "2:20", "Zurich", "Austrian", "F26", "OS464");


    ASSERT_EQ("02:20  Zurich  Austrian  F26  OS464  0\n"
              "04:35  Stuttgart  Austrian  F03  OS257  0\n"
              "08:15  Milan MXP  Ryanair  D10  FR111  0", table.getTable(ARRIVALS, "time=0-8"));

    ASSERT_EQ(0, table.setFlightDelay(ARRIVALS, "OS464","5:00"));
    ASSERT_EQ(1, table.setFlightDelay(ARRIVALS, "OS444","5:00"));


    ASSERT_EQ("07:20  Zurich  Austrian  F26  OS464  3\n"
              "04:35  Stuttgart  Austrian  F03  OS257  0\n"
              "08:15  Milan MXP  Ryanair  D10  FR111  0", table.getTable(ARRIVALS, "time=0-8"));
    table.logOut();
}

TEST (TestFlightInterface, setTwelveHourDelayToFlight) {
    FlightTableInterface table;

    table.logIn("admin", "admin123");
    table.addToTable(ARRIVALS, "2:20", "Zurich", "Austrian", "F26", "OS464");


    ASSERT_EQ("02:20  Zurich  Austrian  F26  OS464  0\n"
              "04:35  Stuttgart  Austrian  F03  OS257  0\n"
              "08:15  Milan MXP  Ryanair  D10  FR111  0", table.getTable(ARRIVALS, "time=0-8"));

    ASSERT_EQ(0, table.setFlightDelay(ARRIVALS, "OS464","10:30"));
    ASSERT_EQ(0, table.setFlightDelay(ARRIVALS, "OS257","11:30"));
    ASSERT_EQ(0, table.setFlightDelay(ARRIVALS, "FR111","12:30"));

    ASSERT_EQ(1, table.setFlightDelay(ARRIVALS, "OS257","11:30"));


    ASSERT_EQ("02:20  Zurich  Austrian  F26  OS464  4\n"
              "04:35  Stuttgart  Austrian  F03  OS257  4\n"
              "08:15  Milan MXP  Ryanair  D10  FR111  4", table.getTable(ARRIVALS, "time=0-8"));
    table.logOut();
}

TEST (TestFlightInterface, tryToBreakFindFlight) {
    FlightTableInterface table;

    ASSERT_EQ("04:35  Stuttgart  Austrian  F03  OS257  0\n"
              "08:15  Milan MXP  Ryanair  D10  FR111  0\n"
              "11:05  Rome FCO  Ryanair  G36  FR1741  0\n"
              "13:15  London STN  Ryanair  G21  FR4318  0\n"
              "13:40  Istanbul ISL  Turkish Airlines  F11  TK6217  0\n"
              "16:00  Warsaw  Austrian  F06  OS435  0\n"
              "16:10  Milan MXP  Austrian  F09  OS120  0\n"
              "21:10  Zurich  Austrian  F26  OS464  0", table.getTable(ARRIVALS));

    ASSERT_EQ("", table.findFlight(ARRIVALS, "81238812"));
    ASSERT_EQ("", table.findFlight(ARRIVALS, "        "));
    ASSERT_EQ("", table.findFlight(ARRIVALS, "@#$%^&*"));
    ASSERT_EQ("", table.findFlight(ARRIVALS, "OS257a"));

    ASSERT_EQ("04:35  Stuttgart  Austrian  F03  OS257  0", table.findFlight(ARRIVALS, "OS257"));
}

TEST (TestFlightInterface, breakingAddFlight) {
    FlightTableInterface table;

    ASSERT_EQ("04:35  Stuttgart  Austrian  F03  OS257  0\n"
              "08:15  Milan MXP  Ryanair  D10  FR111  0\n"
              "11:05  Rome FCO  Ryanair  G36  FR1741  0\n"
              "13:15  London STN  Ryanair  G21  FR4318  0\n"
              "13:40  Istanbul ISL  Turkish Airlines  F11  TK6217  0\n"
              "16:00  Warsaw  Austrian  F06  OS435  0\n"
              "16:10  Milan MXP  Austrian  F09  OS120  0\n"
              "21:10  Zurich  Austrian  F26  OS464  0", table.getTable(ARRIVALS));

    table.logIn("admin", "admin123");
    ASSERT_EQ(1, table.addToTable(ARRIVALS, "23122:20321321", "Zurich", "Austrian", "F26", "OS464"));
    ASSERT_EQ(1, table.addToTable(ARRIVALS, "2:20", "Zurich!@#$%^&", "Austrian", "F26", "OS464"));
    ASSERT_EQ(1, table.addToTable(ARRIVALS, "2:20", "Zurich", "1Austrian", "F26", "OS464"));
    ASSERT_EQ(1, table.addToTable(ARRIVALS, "2:20", "Zurich", "Austrian", "F262312312", "OS464"));
    ASSERT_EQ(1, table.addToTable(ARRIVALS, "2:20", "Zurich", "Austrian", "AF26", "OS464as"));
    ASSERT_EQ(1, table.addToTable(ARRIVALS, "", "", "", "", ""));


    ASSERT_EQ("04:35  Stuttgart  Austrian  F03  OS257  0\n"
              "08:15  Milan MXP  Ryanair  D10  FR111  0\n"
              "11:05  Rome FCO  Ryanair  G36  FR1741  0\n"
              "13:15  London STN  Ryanair  G21  FR4318  0\n"
              "13:40  Istanbul ISL  Turkish Airlines  F11  TK6217  0\n"
              "16:00  Warsaw  Austrian  F06  OS435  0\n"
              "16:10  Milan MXP  Austrian  F09  OS120  0\n"
              "21:10  Zurich  Austrian  F26  OS464  0", table.getTable(ARRIVALS));
}
