// Copyright 2005, Google Inc.
// All rights reserved.


#include "../gtest/gtest.h"
#include "../Time.h"

using namespace ::testing;


TEST(TimeTests, ValidTimeSet1) {
    Time time;
    istringstream input("10:45");
    ASSERT_EQ("", input >> time);
}

TEST(TimeTests, ValidTimeSet2) {
    Time time;
    istringstream input("00:15");
    ASSERT_EQ("", input >> time);
}

TEST(TimeTests, InvalidTimeSetHour1) {
    Time time;
    istringstream input("-1:35");
    ASSERT_EQ("Hour out of limits", input >> time);
}

TEST(TimeTests, InvalidTimeSetHour2) {
    Time time;
    istringstream input("24:35");
    ASSERT_EQ("Hour out of limits", input >> time);
}

TEST(TimeTests, ValidTimeSetMinute1) {
    Time time;
    istringstream input("17:60");
    ASSERT_EQ("Minute out of limits", input >> time);
}

TEST(TimeTests, ValidTimeSetMinute2) {
    Time time;
    istringstream input("17:-1");
    ASSERT_EQ("Minute out of limits", input >> time);
}

TEST(TimeTests, InvalidFormat1) {
    Time time;
    istringstream input("15 55");
    ASSERT_EQ("Time has wrong format", input >> time);
    ASSERT_EQ("00:00", time.getTime());
}

TEST(TimeTests, InvalidFormat2) {
    Time time;
    istringstream input("1555");
    ASSERT_EQ("Time has wrong format", input >> time);
    ASSERT_EQ("00:00", time.getTime());
}

TEST(TimeTests, InvalidFormat3) {
    Time time;
    istringstream input("15-55");
    ASSERT_EQ("Time has wrong format", input >> time);
    ASSERT_EQ("00:00", time.getTime());
}

TEST(TimeTests, GetTime) {
    Time time1;
    time1.setTime(9, 15);
    ASSERT_EQ("09:15", time1.getTime());

    Time time2;
    ASSERT_EQ("00:00", time2.getTime());
}

TEST(TimeTests, TimeComparison1) {
    Time time1;
    time1.setTime(9, 15);

    Time time2;
    time2.setTime(9, 20);
    ASSERT_TRUE(time1 < time2);
}

TEST(TimeTests, TimeComparison2) {
    Time time1;
    time1.setTime(9, 15);

    ASSERT_FALSE(time1 < time1);
}

TEST(TimeTests, TimeComparison3) {
    Time time1;
    time1.setTime(17, 00);

    Time time2;
    time2.setTime(11, 15);
    ASSERT_FALSE(time1 < time2);
}

TEST(TimeTests, AddToTime) {
    Time time1;
    time1.setTime(10, 00);

    Time time2;
    time2.setTime(2, 30);
    time1 += time2;
    ASSERT_EQ("12:30", time1.getTime());
}

TEST(TimeTests, AddToTimeWithOverflowHours) {
    Time time1;
    time1.setTime(18, 00);

    Time time2;
    time2.setTime(6, 30);
    time1 += time2;
    ASSERT_EQ("00:30", time1.getTime());
}

TEST(TimeTests, AddToTimeWithOverflowMinutes) {
    Time time1;
    time1.setTime(17, 55);

    Time time2;
    time2.setTime(1, 20);
    time1 += time2;
    ASSERT_EQ("19:15", time1.getTime());
}

TEST(TimeTests, AddToTimeWithOverflow) {
    Time time1;
    time1.setTime(19, 35);

    Time time2;
    time2.setTime(6, 50);
    time1 += time2;
    ASSERT_EQ("02:25", time1.getTime());
}

TEST(TimeTests, SubtrackFromTime) {
    Time time1;
    time1.setTime(5, 25);

    Time time2;
    time2.setTime(2, 30);
    time1 -= time2;
    ASSERT_EQ("02:55", time1.getTime());
}

TEST(TimeTests, SubtrackFromTimeWithOverflowHours) {
    Time time1;
    time1.setTime(3, 45);

    Time time2;
    time2.setTime(6, 30);
    time1 -= time2;
    ASSERT_EQ("21:15", time1.getTime());
}

TEST(TimeTests, SubtrackFromTimeWithOverflowMinutes) {
    Time time1;
    time1.setTime(11, 15);

    Time time2;
    time2.setTime(1, 25);
    time1 -= time2;
    ASSERT_EQ("09:50", time1.getTime());
}

TEST(TimeTests, SubtrackFromTimeWithOverflow) {
    Time time1;
    time1.setTime(1, 30);

    Time time2;
    time2.setTime(8, 50);
    time1 -= time2;
    ASSERT_EQ("16:40", time1.getTime());
}

TEST(TimeTests, NotOnlyNumbersInTime1) {
    Time time;
    istringstream input("1a:45");
    ASSERT_EQ("Time has wrong format", input >> time);
}

TEST(TimeTests, NotOnlyNumbersInTime2) {
    Time time;
    istringstream input("ab:cd");
    ASSERT_EQ("Time has wrong format", input >> time);
}

TEST(TimeTests, addTwoTimes) {
    Time time1;
    time1.setTime(1, 10);

    Time time2;
    time2.setTime(8, 50);
    ASSERT_EQ("10:00", time1 + time2);
}

TEST(TimeTests, shortInputValidTime) {
    Time time;
    istringstream input("2:1");
    ASSERT_EQ("", input >> time);
    ASSERT_EQ("02:01", time.getTime());
}

TEST(TimeTests, longInputTime) {
    Time time;
    istringstream input("000002:0000001");
    ASSERT_EQ("", input >> time);
    ASSERT_EQ("02:01", time.getTime());
}