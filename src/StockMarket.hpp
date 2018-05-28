#ifndef STOCKMARKET_HPP
#define STOCKMARKET_HPP

#include <iostream>
#include <string>
#include <cmath>
#include <map>
#include <memory>
#include "StockListing.hpp"
#include "TradeLogBook.hpp"

class StockMarket
{
public:
  StockMarket(std::string name, std::shared_ptr<StockListing> sl, std::shared_ptr<TradeLogBook> tlb) : m_name(name), m_stockListing(sl), m_tradeLogBook(tlb) { };

  std::string GetName() const { return m_name; };
  std::shared_ptr<StockListing> GetStockListing() const { return m_stockListing; };
  std::shared_ptr<TradeLogBook> GetTradeLogBook() const { return m_tradeLogBook; };

  static std::shared_ptr<StockMarket> Create(std::string name, std::shared_ptr<StockListing> sl, std::shared_ptr<TradeLogBook> tlb)
  {
    return std::make_shared<StockMarket>(name, sl, tlb);
  }
  
  void AddStock(std::shared_ptr<Stock> stock)
  {
    m_stockListing->Add(stock);
  };
  
  void AddTrade(std::shared_ptr<Trade> trade)
  {
    m_tradeLogBook->Add(trade);
  };
  
  float GetGBCE()
  {
    int n = 0; // counting the Stocks involved
    float productVWS = 1;
    for(auto const &item : m_stockListing->GetListing())
      {
	auto stock = item.second;
	auto VWS = m_tradeLogBook->GetVolumeWeightedStock(stock);
	// If a Stock has no Trade, then its VWS is NaN
	if(!std::isnan(VWS))
	  {
	    productVWS *= VWS;
	    n++;
	  }
      }
    if (n == 0)
      {
	return std::numeric_limits<float>::quiet_NaN();
      }
    else
      {
	return pow(productVWS,1.0/n);
      }
  };
  
private:
  std::string m_name;
  std::shared_ptr<StockListing> m_stockListing;
  std::shared_ptr<TradeLogBook> m_tradeLogBook;

};

#endif // STOCKMARKET_HPP
