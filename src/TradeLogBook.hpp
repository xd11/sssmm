#ifndef TRADELOGBOOK_HPP
#define TRADELOGBOOK_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <memory>
#include "Trade.hpp"

class TradeLogBook
{
public:
  TradeLogBook(std::string name) : m_name(name) { };

  static long long int GetCounter() { return COUNTER; };
  std::string GetName() const { return m_name; };
  std::map< long long int, std::shared_ptr<Trade> > GetLogBook() const { return m_logBook; };

  static std::shared_ptr<TradeLogBook> Create(std::string name)
  {
    return std::make_shared<TradeLogBook>(name);
  }

  void Add(std::shared_ptr<Trade> trade)
  {
    if (0 == 0)
      {
	m_logBook.emplace(COUNTER, trade);
        COUNTER++;
      }
    else
      {
	std::cerr << "TradeLogBook::Add() failed: Trade was not added" << std::endl; 
      }
  };

  void Print(std::ostream &os = std::cout) const
  {
    os << "TradeLogBook: " << m_name << std::endl;
    os << "key,stock,date_time,action,quantity,price" << std::endl;
    for(auto const &item : m_logBook)
      {
	os << item.first << "," << item.second << std::endl;
      }
  };

  std::shared_ptr<TradeLogBook> GetHistory(std::shared_ptr<Stock> stock, unsigned short timeinsecond = 300, std::shared_ptr<TimeStamp> tstart = TimeStamp::GetNowTimeStamp()) const
  {
    std::stringstream query;
    query << m_name << "_last_" << timeinsecond << "_seconds_from_" << tstart;
    auto result = TradeLogBook::Create(query.str());
    
    for(auto const &item : m_logBook)
      {
	auto itrade = item.second;
	auto istock = itrade->GetStock();
	
	if (stock->GetSymbol() == istock->GetSymbol())
	  { 
	    auto timediff = TimeStamp::CompareTime(itrade->GetTimeStamp(), tstart);
	    if(timediff < timeinsecond && timediff > 0)
	      {
	        result->Add(itrade);
	      }
	  }
      }
    return result;
  };

  float GetVolumeWeightedStock(std::shared_ptr<Stock> stock)
  {
    float sumPrice = 0;
    float sumQuantity = 0;
    for(auto const &item : m_logBook)
      {
	auto trade = item.second;
	if(stock->GetSymbol() == trade->GetStock()->GetSymbol())
	  {
	    sumPrice += trade->GetPrice() * trade->GetQuantity();
	    sumQuantity += trade->GetQuantity();
	  }
      }
    if (sumQuantity > 0)
      {
        return (float)(sumPrice) / sumQuantity;
      }
    else
      {
	return std::numeric_limits<float>::quiet_NaN();
      }
  }
  
private:
  static long long int COUNTER;
  std::string m_name;
  std::map< long long int, std::shared_ptr<Trade> > m_logBook;
};

// *****************************************************************************

inline std::ostream &operator <<(std::ostream &os, TradeLogBook const &tradelogbook)
{
  tradelogbook.Print(os);
  return os;
}

inline std::ostream &operator <<(std::ostream &os, const TradeLogBook *tradelogbook)
{  
  tradelogbook->Print(os);
  return os;
}

#endif // TRADELOGBOOK_HPP
