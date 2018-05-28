#ifndef STOCKLISTING_HPP
#define STOCKLISTING_HPP

#include <iostream>
#include <string>
#include <map>
#include <memory>
#include "Stock.hpp"

class StockListing
{
public:
  StockListing(std::string name) : m_name(name) { };

  std::string GetName() const { return m_name; };
  std::map< std::string, std::shared_ptr<Stock> > GetListing() const { return m_listing; };

  static std::shared_ptr<StockListing> Create(std::string name)
  {
    return std::make_shared<StockListing>(name);
  }

  void Add(std::shared_ptr<Stock> stock)
  {
    if (m_listing.find(stock->GetSymbol()) == m_listing.end())
      {
	m_listing.emplace(stock->GetSymbol(), stock);
      }
    else
      {
	std::cerr << "StockListing::Add() failed: Stock('" << stock->GetSymbol() << "') already exists in the listing" << std::endl; 
      }    
  };

  void Print(std::ostream &os = std::cout) const
  {
    os << "StockListing: " << m_name << std::endl;
    os << "symbol,type,lastDividend,fixedDividend,value" << std::endl;
    for(const auto &item : m_listing)
      {
	os << item.second << std::endl;
      }
  };

private:
  std::string m_name;
  std::map< std::string, std::shared_ptr<Stock> > m_listing;

};

// *****************************************************************************
inline std::ostream &operator <<(std::ostream &os, StockListing const &stocklisting)
{
  stocklisting.Print(os);
  return os;
}

inline std::ostream &operator <<(std::ostream &os, const StockListing *stocklisting)
{  
  stocklisting->Print(os);
  return os;
}

#endif // STOCKLISTING_HPP
