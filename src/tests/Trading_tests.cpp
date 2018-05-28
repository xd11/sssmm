#include "catch.hpp"

#include "../StockFactory.hpp"
#include "../TradeLogBook.cpp"
#include "../StockMarket.hpp"

using namespace std;

TEST_CASE("Calculations on trades")
{
  float epsilon = 0.001;
  
  auto stockListing = StockListing::Create("Test Stock Listing");
  auto tradeLogBook = TradeLogBook::Create("Test Trade Log Book");
  auto stockMarket = StockMarket::Create("Test Stock Market", stockListing, tradeLogBook);

  // stocks
  auto stockParam_TEA = StockParam::Create("TEA",0,100);
  auto stock_TEA = StockFactory::Create("common",stockParam_TEA);
  stockListing->Add(stock_TEA);
  
  auto stockParam_GIN = StockParam::Create("GIN",8,2.0,100);
  auto stock_GIN = StockFactory::Create("preferred", stockParam_GIN);
  stockListing->Add(stock_GIN);

  // dummy stock, no trade for it, to test how the calculation of GBCE handle a NaN
  auto stockParam_DUM = StockParam::Create("DUM",10,10);
  auto stock_DUM = StockFactory::Create("common", stockParam_DUM);
  stockListing->Add(stock_DUM);

  // time stamps
  auto timeNow = TimeStamp::Create(20180525, 210000);
  auto time1 = TimeStamp::Create(20180525, 205900); // -1 minute
  auto time2 = TimeStamp::Create(20180525, 210003); // + 3seconds
  auto time3 = TimeStamp::Create(20180525, 205830); // -1min30
  auto time4 = TimeStamp::Create(20180524, 210000); // -1 day
  auto time5 = TimeStamp::Create(20180525, 205730); // -2min30
  auto time6 = TimeStamp::Create(20180525, 205501); // -4min59
  auto time7 = TimeStamp::Create(20180525, 205500); // -5 minutes
  auto time8 = TimeStamp::Create(20180525, 205922); // -38 seconds
  auto time9 = TimeStamp::Create(20180525, 210140); // + 1min40
  auto time10 = TimeStamp::Create(20180525, 205530); // -4min30

  // trades 
  auto trade1 = Trade::Create(stock_TEA, 200, TradeAction::BUY, 500, time1); // in 
  tradeLogBook->Add(trade1);
  auto trade2 = Trade::Create(stock_TEA, 100, TradeAction::BUY, 300, time2); // out
  tradeLogBook->Add(trade2);
  auto trade3 = Trade::Create(stock_TEA, 200, TradeAction::BUY, 500, time3); // in
  tradeLogBook->Add(trade3);
  auto trade4 = Trade::Create(stock_TEA, 200, TradeAction::BUY, 500, time4); // out
  tradeLogBook->Add(trade4);
  auto trade5 = Trade::Create(stock_TEA, 150, TradeAction::BUY, 1000, time5); // in
  tradeLogBook->Add(trade5);
  auto trade6 = Trade::Create(stock_TEA, 50, TradeAction::BUY, 600, time6); // in
  tradeLogBook->Add(trade6);
  auto trade7 = Trade::Create(stock_GIN, 40, TradeAction::BUY, 50, time7); // out
  tradeLogBook->Add(trade7);
  auto trade8 = Trade::Create(stock_GIN, 200, TradeAction::BUY, 75, time8); // in
  tradeLogBook->Add(trade8);
  auto trade9 = Trade::Create(stock_GIN, 600, TradeAction::BUY, 48, time9); // out
  tradeLogBook->Add(trade9);
  auto trade10 = Trade::Create(stock_GIN, 10, TradeAction::BUY, 90, time10); // in
  tradeLogBook->Add(trade10);

  SECTION("Calculation of VWSP")
    {
      REQUIRE( fabs(tradeLogBook->GetVolumeWeightedStock(stock_TEA) == 566.667) < epsilon );
      REQUIRE( fabs(tradeLogBook->GetVolumeWeightedStock(stock_GIN) == 54.9412) < epsilon );
      REQUIRE( isnan(tradeLogBook->GetVolumeWeightedStock(stock_DUM)) );
    }

  SECTION("Calculation of VWSP after filtering")
    {
      auto filter_TEA = tradeLogBook->GetHistory(stock_TEA,300,timeNow);
      auto filter_GIN = tradeLogBook->GetHistory(stock_GIN,300,timeNow);
    
      REQUIRE( fabs(filter_TEA->GetVolumeWeightedStock(stock_TEA) == 633.333) < epsilon );
      REQUIRE( fabs(filter_GIN->GetVolumeWeightedStock(stock_GIN) == 75.714) < epsilon );
    }

  SECTION("Calculation of GBCE")
    {

      auto GBCE = sqrt(tradeLogBook->GetVolumeWeightedStock(stock_TEA) * tradeLogBook->GetVolumeWeightedStock(stock_GIN));

      REQUIRE( !isnan(GBCE) );
      REQUIRE( fabs(stockMarket->GetGBCE()-GBCE) < epsilon );
    }
}
