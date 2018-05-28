#include "catch.hpp"

#include "../TimeStamp.hpp"

using namespace std;

TEST_CASE("Conversion of m_time to seconds")
{
  auto sut1 = TimeStamp::Create(20180520, 100530);
  auto second1 = sut1->ConvertTimeToSecond();

  auto sut2 = TimeStamp::Create(20180520, 101530); // +10 minutes
  auto second2 = sut2->ConvertTimeToSecond();
  
  REQUIRE(second1 == 36330);
  REQUIRE(second2 == 36930);
  REQUIRE(second2-second1 == 600);
}

TEST_CASE("Conversion of seconds to time")
{
  REQUIRE(TimeStamp::ConvertSecondToTime(40876) == 112116);
  REQUIRE(TimeStamp::ConvertSecondToTime(40816) == 112016); // +1 minute
  REQUIRE(TimeStamp::ConvertSecondToTime(-403939) == -1);
}

TEST_CASE("Comparison of two times")
{
  auto sut1 = TimeStamp::Create(20180520, 100530);
  auto sut2 = TimeStamp::Create(20180520, 100530); // same time
  auto sut3 = TimeStamp::Create(20180520, 101130); // +10 minutes
  auto sut4 = TimeStamp::Create(20180520, 120529); // +1h59m59
  
  REQUIRE(TimeStamp::CompareTime(sut1,sut2) == 0);
  REQUIRE(TimeStamp::CompareTime(sut1,sut3) == 360);
  REQUIRE(TimeStamp::CompareTime(sut3,sut1) == -360);
  REQUIRE(TimeStamp::CompareTime(sut1,sut4) == 7199);
  REQUIRE(TimeStamp::CompareTime(sut4,sut1) == -7199);
  REQUIRE(TimeStamp::CompareTime(sut3,sut4) == 6839);
  REQUIRE(TimeStamp::CompareTime(sut4,sut3) == -6839);
}

TEST_CASE("Comparison of two dates")
{
  auto sut1 = TimeStamp::Create(20180520, 100530);
  auto sut2 = TimeStamp::Create(20180520, 100545); // same date, different time
  auto sut3 = TimeStamp::Create(20180521, 101130); // +1 day
  auto sut4 = TimeStamp::Create(20180720, 120529); // +2 months
  auto sut5 = TimeStamp::Create(20190520, 120529); // +1 year
  auto sut6 = TimeStamp::Create(20200708, 100630); // random

  REQUIRE(TimeStamp::IsSameDate(sut1,sut2) == true);
  REQUIRE(TimeStamp::IsSameDate(sut1,sut3) == false);
  REQUIRE(TimeStamp::IsSameDate(sut1,sut4) == false);
  REQUIRE(TimeStamp::IsSameDate(sut1,sut5) == false);
  REQUIRE(TimeStamp::IsSameDate(sut1,sut6) == false);
}
