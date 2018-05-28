#include <iostream>
#include "StockFactory.hpp"
#include "Stock.hpp"
#include "StockParam.hpp"
#include "StockListing.hpp"
#include "TradeLogBook.hpp"
#include "StockMarket.hpp"
#include "CLI.hpp"

using namespace std;

int main()
{
  // Setting the GBCE Stock Market
  auto stockListing = StockListing::Create("GBCE Stock Listing");
  auto tradeLogBook = TradeLogBook::Create("GBCE Trade Log Book");
  auto stockMarket = StockMarket::Create("Global Beverage Corporation Exchange", stockListing, tradeLogBook);

  // Adding the sample data to the GBCE Stock Listing
  auto stockParam_TEA = StockParam::Create("TEA",0,100);
  auto stock_TEA = StockFactory::Create("common",stockParam_TEA);
  stockMarket->AddStock(stock_TEA);

  auto stockParam_POP = StockParam::Create("POP",8,100);
  auto stock_POP = StockFactory::Create("common", stockParam_POP);
  stockMarket->AddStock(stock_POP);

  auto stockParam_ALE = StockParam::Create("ALE",23,60);
  auto stock_ALE = StockFactory::Create("common", stockParam_ALE);
  stockMarket->AddStock(stock_ALE);

  auto stockParam_GIN = StockParam::Create("GIN",8,2.0,100);
  auto stock_GIN = StockFactory::Create("preferred", stockParam_GIN);
  stockMarket->AddStock(stock_GIN);

  auto stockParam_JOE = StockParam::Create("JOE",13,250);
  auto stock_JOE = StockFactory::Create("common", stockParam_JOE);
  stockMarket->AddStock(stock_JOE);
  
  // Command-line interface
  auto cli  = CLI::Create(stockMarket);
  cli->Header();
  cli->MainMenu();

  // for Windows
  getchar();
  
  return 0;
}
