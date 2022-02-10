// Copyright 2005, Google Inc.
// All rights reserved.

#include <iostream>
#include "../gtest/gtest.h"
#include "../Flight.h"

using namespace ::testing;


//airline names and destination names tests
TEST(TestFlight, validAirlineName1) {
    Flight flight("");
    ASSERT_TRUE(flight.onlyAlphabetChars("Ryanair"));
}

TEST(TestFlight, validAirlineName2) {
    Flight flight("");
    ASSERT_TRUE(flight.onlyAlphabetChars("Turkish Airlines"));
}

TEST(TestFlight, invalidAirlineName1) {
    Flight flight("");
    ASSERT_FALSE(flight.onlyAlphabetChars("Turkish1 Airlines"));
}

TEST(TestFlight, invalidAirlineName2) {
    Flight flight("");
    ASSERT_FALSE(flight.onlyAlphabetChars(""));
}


//check if flight input is correct tests
TEST(TestFlight, addValidFlight) {
    Flight flight("");
    std::string input = "17:45;Milan MXP;Ryanair;F10;FR214";
    ASSERT_TRUE(flight.checkIfValidData(input));
}

TEST(TestFlight, addNothing) {
    Flight flight("");
    ASSERT_FALSE(flight.checkIfValidData(""));
}

TEST(TestFlight, shorterInput1) {
    Flight flight("");
    std::string input = "17:45;Milan MXP;F10;FR214";
    ASSERT_FALSE(flight.checkIfValidData(input));
}

TEST(TestFlight, shorterInput2) {
    Flight flight("");
    std::string input = "17:45;Milan MXP;;F10;FR214";
    ASSERT_FALSE(flight.checkIfValidData(input));
}

TEST(TestFlight, wrongData) {
    Flight flight("");
    std::string input = "24:45;Milan MXP;Ryanair;F10;FR214";
    ASSERT_FALSE(flight.checkIfValidData(input));
}

TEST(TestFlight, onlySeparators) {
    Flight flight("");
    std::string input = ";;;;";
    ASSERT_FALSE(flight.checkIfValidData(input));
}



TEST(TestFlight, WrongFlightInput1) {
    Flight flight("24:45;Milan MXP;Ryanair;F10;FR214");
    ASSERT_NE("24:45  Milan MXP  Ryanair  F10  FR214  0", flight.getFlightInfo());
    ASSERT_EQ("00:00  NULL  NULL  NULL  NULL  0", flight.getFlightInfo());
}

TEST(TestFlight, WrongFlightInput2) {
    Flight flight("12:45;Milan55 MXP;Ryanair;F10;FR214");
    ASSERT_EQ("00:00  NULL  NULL  NULL  NULL  0", flight.getFlightInfo());
}

TEST(TestFlight, WrongFlightInput3) {
    Flight flight("12:45;Milan MXP;Ryanair 12;F10;FR214");
    ASSERT_EQ("00:00  NULL  NULL  NULL  NULL  0", flight.getFlightInfo());
}

TEST(TestFlight, WrongFlightInput4) {
    Flight flight("12:45;Milan MXP;Ryanair;F10250;FR214");
    ASSERT_EQ("00:00  NULL  NULL  NULL  NULL  0", flight.getFlightInfo());
}

TEST(TestFlight, WrongFlightInput5) {
    Flight flight("12:45;Milan MXP;Ryanair;F10;FRA214");
    ASSERT_EQ("00:00  NULL  NULL  NULL  NULL  0", flight.getFlightInfo());
}

TEST(TestFlight, FlightInfo1) {
    Flight flight("17:45;Milan MXP;Ryanair;F10;FR214");
    ASSERT_EQ("17:45  Milan MXP  Ryanair  F10  FR214  0", flight.getFlightInfo());
}

TEST(TestFlight, FlightInfo2) {
    Flight flight("09:05;Stuttgart;Austrian;F03;OS187");
    ASSERT_EQ("09:05  Stuttgart  Austrian  F03  OS187  0", flight.getFlightInfo());
}


TEST(TestFlight, statusValid) {
    Flight flight("09:05;Stuttgart;Austrian;F03;OS187");
    ASSERT_EQ(SCHEDULED, flight.getStatus());
}

TEST(TestFlight, statusNotValid) {
    Flight flight("09:05;Stuttgart;Austrian;F03;OS187");
    ASSERT_NE(DELAYED, flight.getStatus());
}

TEST(TestFlight, statusChange) {
    Flight flight("09:05;Stuttgart;Austrian;F03;OS187");
    flight.setStatus(BOARDING);
    ASSERT_EQ(BOARDING, flight.getStatus());
    flight.setStatus(CANCELLED);
    ASSERT_EQ(CANCELLED, flight.getStatus());
}

TEST(TestFlight, InvalidTimeOfFlight1) {
    Flight flight("24:45;Milan MXP;Ryanair;F10;FR214");
    ASSERT_NE("00:00  Milan MXP  Ryanair  F10  FR214  0", flight.getFlightInfo());
}

TEST(TestFlight, InvalidTimeOfFlight2) {
    Flight flight("24:45;Milan MXP;Ryanair;F10;FR214");
    ASSERT_EQ("00:00  NULL  NULL  NULL  NULL  0", flight.getFlightInfo());
}

TEST (TestFlight, delayFlight1) {
    Flight flight("00:00;Milan MXP;Ryanair;F10;FR214");
    ASSERT_EQ("00:00  Milan MXP  Ryanair  F10  FR214  0", flight.getFlightInfo());

    Time time;
    istringstream input("2:45");
    input >> time;
    ASSERT_EQ(3, flight.addDelayToFlight(time));
    ASSERT_EQ("02:45", flight.getFlightTimeWithDelay());
    ASSERT_EQ("00:00  Milan MXP  Ryanair  F10  FR214  3", flight.getFlightInfo());
}

TEST (TestFlight, delayFlight2) {
    Flight flight("00:00;Milan MXP;Ryanair;F10;FR214");
    Time time;
    istringstream input("12:00");
    input >> time;
    ASSERT_EQ(3, flight.addDelayToFlight(time));
    ASSERT_EQ("12:00", flight.getFlightTimeWithDelay());
    ASSERT_EQ("00:00  Milan MXP  Ryanair  F10  FR214  3", flight.getFlightInfo());
}

TEST (TestFlight, cancelledFlight1) {
    Flight flight("02:30;Milan MXP;Ryanair;F10;FR214");
    Time time;
    istringstream input("12:20");
    input >> time;
    ASSERT_EQ(4, flight.addDelayToFlight(time));
    ASSERT_EQ("02:30", flight.getFlightTimeWithDelay());
    ASSERT_EQ(CANCELLED, flight.getStatus());
    ASSERT_EQ("02:30  Milan MXP  Ryanair  F10  FR214  4", flight.getFlightInfo(true));
}

TEST (TestFlight, delayTimeShown) {
    Flight flight("00:00;Milan MXP;Ryanair;F10;FR214");
    Time time;
    istringstream input("2:45");
    input >> time;
    ASSERT_EQ(3, flight.addDelayToFlight(time));
    ASSERT_EQ("02:45", flight.getFlightTimeWithDelay());
    ASSERT_EQ("02:45  Milan MXP  Ryanair  F10  FR214  3", flight.getFlightInfo(true));
}

TEST (TestFlight, createEmptyFlight) {
    Flight flight;
    ASSERT_EQ("00:00  NULL  NULL  NULL  NULL  0", flight.getFlightInfo());
}

TEST (TestFlight, ultimateFlightCreationTest) {
    Flight flight("15:10;Istanbul ISL;Turkish Airlines;F11;TK6387");
    ASSERT_EQ("15:10  Istanbul ISL  Turkish Airlines  F11  TK6387  0", flight.getFlightInfo());
    ASSERT_EQ("15:10  Istanbul ISL  Turkish Airlines  F11  TK6387  0", flight.getFlightInfo(true));

    flight.setStatus(BOARDING);
    ASSERT_EQ("15:10  Istanbul ISL  Turkish Airlines  F11  TK6387  1", flight.getFlightInfo());

    Time time1;
    istringstream input1("02:20");
    input1 >> time1;
    flight.addDelayToFlight(time1);
    ASSERT_EQ("17:30  Istanbul ISL  Turkish Airlines  F11  TK6387  3", flight.getFlightInfo(true));

    Time time2;
    istringstream input2("00:40");
    input2 >> time2;
    flight.addDelayToFlight(time2);
    ASSERT_EQ("18:10  Istanbul ISL  Turkish Airlines  F11  TK6387  3", flight.getFlightInfo(true));

    Time time3;
    istringstream input3("07:20");
    input3 >> time3;
    flight.addDelayToFlight(time3);
    ASSERT_EQ("15:10  Istanbul ISL  Turkish Airlines  F11  TK6387  4", flight.getFlightInfo(true));
    ASSERT_EQ(CANCELLED, flight.getStatus());
}

TEST(TestFlight, lowerCaseLocation) {
    Flight flight1("12:45;milan MXP;Ryanair;F10;FR214");
    ASSERT_EQ("12:45  Milan MXP  Ryanair  F10  FR214  0", flight1.getFlightInfo());

    Flight flight2("15:10;istanbul isl;Turkish Airlines;F11;TK6387");
    ASSERT_EQ("15:10  Istanbul ISL  Turkish Airlines  F11  TK6387  0", flight2.getFlightInfo());

    Flight flight3("09:05;stuttgart;Austrian;F03;OS187");
    ASSERT_EQ("09:05  Stuttgart  Austrian  F03  OS187  0", flight3.getFlightInfo());
}

TEST(TestFlight, lowerCaseAirline) {
    Flight flight1("15:10;istanbul isl;turkish airlines;F11;TK6387");
    ASSERT_EQ("15:10  Istanbul ISL  Turkish Airlines  F11  TK6387  0", flight1.getFlightInfo());

    Flight flight2("09:05;stuttgart;austrian;F03;OS187");
    ASSERT_EQ("09:05  Stuttgart  Austrian  F03  OS187  0", flight2.getFlightInfo());
}