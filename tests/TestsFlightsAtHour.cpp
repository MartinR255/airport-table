// Copyright 2005, Google Inc.
// All rights reserved.


#include "../gtest/gtest.h"
#include "../FlightsAtHour.h"

using namespace ::testing;


//adding flights tests
TEST(TestListFlights, addingFlights1) {
    FlightsAtHour flightList;
    ASSERT_EQ(0, flightList.addFlight("15:35;Milan MXP;Ryanair;F10;FR214"));
    ASSERT_EQ(0, flightList.addFlight("15:10;Istanbul ISL;Turkish Airlines;F11;TK6387"));
}


TEST(TestListFlights, addingFlights2) {
    FlightsAtHour listOfFlights;

    listOfFlights.addFlight("06:10;Istanbul ISL;Turkish Airlines;F11;TK6387");
    listOfFlights.addFlight("06:50;Zurich;Austrian;F26;OS565");
    listOfFlights.addFlight("06:45;Warsaw;Austrian;F06;OS631");
    listOfFlights.addFlight("06:10;Stuttgart;Austrian;F03;OS257");
    listOfFlights.addFlight("06:25;Milan MXP;Austrian;F09;OS515");

    ASSERT_EQ(5, listOfFlights.getNumberOfFlights());
    ASSERT_EQ("06:10  Stuttgart  Austrian  F03  OS257  0\n"
              "06:10  Istanbul ISL  Turkish Airlines  F11  TK6387  0\n"
              "06:25  Milan MXP  Austrian  F09  OS515  0\n"
              "06:45  Warsaw  Austrian  F06  OS631  0\n"
              "06:50  Zurich  Austrian  F26  OS565  0", listOfFlights.getAllFlightsAtHour());
}


TEST(TestListFlights, addingFlights3) {
    FlightsAtHour listOfFlights;

    listOfFlights.addFlight("06:10;Istanbul ISL;Turkish Airlines;F11;TK6387");
    listOfFlights.addFlight("06:10;Istanbul ISL;Turkish Airlines;F11;TK6387");
    listOfFlights.addFlight("06:45;Warsaw;Austrian;F06;OS631");

    ASSERT_EQ(2, listOfFlights.getNumberOfFlights());
    ASSERT_EQ("06:10  Istanbul ISL  Turkish Airlines  F11  TK6387  0\n"
              "06:45  Warsaw  Austrian  F06  OS631  0", listOfFlights.getAllFlightsAtHour());
}

TEST(TestListFlights, addingMultipleIdenticalFlights) {
    Flight flight("06:10;Stuttgart;Austrian;F03;OS257");
    FlightsAtHour listOfFlights;

    listOfFlights.addFlight("06:10;Stuttgart;Austrian;F03;OS257");
    listOfFlights.addFlight("06:10;Stuttgart;Austrian;F03;OS257");
    listOfFlights.addFlight("06:10;Stuttgart;Austrian;F03;OS257");
    listOfFlights.addFlight("06:10;Stuttgart;Austrian;F03;OS257");
    listOfFlights.addFlight("06:10;Stuttgart;Austrian;F03;OS257");

    ASSERT_EQ(1, listOfFlights.getNumberOfFlights());
    ASSERT_EQ("06:10  Stuttgart  Austrian  F03  OS257  0", listOfFlights.getAllFlightsAtHour());
}


//deleting flights
TEST(TestListFlights, addingFlightAndDeletingFlight) {


    FlightsAtHour listOfFlights;

    listOfFlights.addFlight("06:10;Istanbul ISL;Turkish Airlines;F11;TK6387");
    listOfFlights.addFlight("06:45;Warsaw;Austrian;F06;OS631");

    ASSERT_EQ(2, listOfFlights.getNumberOfFlights());
    listOfFlights.removeFlight("TK6387");
    ASSERT_EQ("06:45  Warsaw  Austrian  F06  OS631  0", listOfFlights.getAllFlightsAtHour());
    ASSERT_EQ(1, listOfFlights.getNumberOfFlights());
}

TEST(TestListFlights, deleteFromEmptyFlightList) {
    FlightsAtHour listOfFlights;
    ASSERT_EQ(1, listOfFlights.removeFlight("TK6387"));
}


TEST(TestListFlights, RemoveAllFlights) {
    FlightsAtHour listOfFlights;

    listOfFlights.addFlight("06:10;Istanbul ISL;Turkish Airlines;F11;TK6387");
    listOfFlights.addFlight("06:45;Warsaw;Austrian;F06;OS631");

    ASSERT_EQ(2, listOfFlights.getNumberOfFlights());
    ASSERT_EQ(0, listOfFlights.removeAllFlights());
    ASSERT_EQ(0, listOfFlights.getNumberOfFlights());
}

TEST(TestListFlights, RemoveAllFlightsFromEmptyList) {
    FlightsAtHour listOfFlights;
    ASSERT_EQ(0, listOfFlights.getNumberOfFlights());
    ASSERT_EQ(1, listOfFlights.removeAllFlights());
    ASSERT_EQ(0, listOfFlights.getNumberOfFlights());
}



//find flights
TEST(TestListFlights, FindExistingFlight) {
    FlightsAtHour listOfFlights;
    listOfFlights.addFlight("06:10;Istanbul ISL;Turkish Airlines;F11;TK6387");
    listOfFlights.addFlight("06:45;Warsaw;Austrian;F06;OS631");

    ASSERT_EQ("06:45  Warsaw  Austrian  F06  OS631  0", listOfFlights.findFlight("OS631")->getFlightInfo());
    ASSERT_EQ("06:10  Istanbul ISL  Turkish Airlines  F11  TK6387  0", listOfFlights.findFlight("TK6387")->getFlightInfo());
}

TEST(TestListFlights, FindNotExistingFlight) {
    FlightsAtHour listOfFlights;
    listOfFlights.addFlight("06:10;Istanbul ISL;Turkish Airlines;F11;TK6387");
    listOfFlights.addFlight("06:45;Warsaw;Austrian;F06;OS631");

    ASSERT_NE("06:45  Warsaw  Austrian  F06  OS631  0", listOfFlights.findFlight("FR214")->getFlightInfo());
    ASSERT_EQ("00:00  NULL  NULL  NULL  NULL  0", listOfFlights.findFlight("FR214")->getFlightInfo());
}



TEST(TestListFlights, lowerCaseLocation) {
    FlightsAtHour flightList;
    ASSERT_EQ(0, flightList.addFlight("15:35;Milan MXP;Ryanair;F10;FR214"));
    ASSERT_EQ(0, flightList.addFlight("15:10;Istanbul ISL;Turkish Airlines;F11;TK6387"));
}

TEST(TestListFlights, testDelay) {
    FlightsAtHour flightList;

    ASSERT_EQ(0, flightList.addFlight("15:35;Milan MXP;Ryanair;F10;FR214"));
    ASSERT_EQ(0, flightList.addFlight("15:10;Istanbul ISL;Turkish Airlines;F11;TK6387"));

    flightList.addDelayToFlight("TK6387", "0:50");

    ASSERT_EQ("16:00  Istanbul ISL  Turkish Airlines  F11  TK6387  3\n"
            "15:35  Milan MXP  Ryanair  F10  FR214  0", flightList.getAllFlightsAtHour());
}