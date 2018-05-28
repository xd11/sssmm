#include "catch.hpp"

#include "../StockFactory.hpp"

using namespace std;

TEST_CASE("Basic operations on Stocks")
{
  float epsilon = 0.00000001;
  
  auto sut1Param = StockParam::Create("COM",10,100);
  auto sut1 = StockFactory::Create("common", sut1Param);
  
  auto sut2Param = StockParam::Create("PRE",8,2.5,800);
  auto sut2 = StockFactory::Create("preferred", sut2Param);
  
  REQUIRE(fabs(sut1->GetDividendYield(50) - 0.2) < epsilon);
  REQUIRE(sut1->GetPERatio(50) == 5);
  REQUIRE(isnan(sut1->GetDividendYield(0)));
  REQUIRE(sut1->GetPERatio(0) == 0);
  
  REQUIRE(fabs(sut2->GetDividendYield(50) - 0.4) < epsilon);
  REQUIRE(sut2->GetPERatio(50) == 6.25);
  REQUIRE(isnan(sut2->GetDividendYield(0)));
  REQUIRE(sut2->GetPERatio(0) == 0);
}
