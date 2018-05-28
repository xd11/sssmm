#ifndef TRADE_HPP
#define TRADE_HPP

#include <iostream>
#include <string>
#include <memory>
#include "Stock.hpp"
#include "TimeStamp.hpp"

enum TradeAction { BUY, SELL };

inline const std::string ToString(TradeAction a)
{
  switch (a)
    {
    case BUY:
      return "BUY";
    case SELL:
      return "SELL";
    default:
      return "UNKNOWN";
    }
}

class Trade
{
public:
  Trade(std::shared_ptr<Stock> s, unsigned int q, TradeAction a, unsigned int p, std::shared_ptr<TimeStamp> t) : m_stock(s), m_quantity(q), m_action(a), m_price (p), m_timestamp(t) { };

  static std::shared_ptr<Trade> Create(std::shared_ptr<Stock> s, unsigned int q, TradeAction a, unsigned int p, std::shared_ptr<TimeStamp> t)
  {
    return std::make_shared<Trade>(s,q,a,p,t);
  }
  
  std::shared_ptr<Stock> GetStock() const { return m_stock; };
  unsigned int GetQuantity() const { return m_quantity; };
  TradeAction GetTradeAction() const { return m_action; };
  unsigned int GetPrice() const { return m_price; };
  std::shared_ptr<TimeStamp> GetTimeStamp() const { return m_timestamp; };
  
  void Print(std::ostream &os = std::cout) const
  {
    os <<  m_stock->GetSymbol() << "," <<  m_timestamp << "," << ToString(m_action) << "," << m_quantity << "," << m_price;
  };
  
private:
  std::shared_ptr<Stock> m_stock;
  unsigned int m_quantity;
  TradeAction m_action;
  unsigned int m_price;
  std::shared_ptr<TimeStamp> m_timestamp;
  
};

// *****************************************************************************
inline std::ostream &operator <<(std::ostream &os, Trade const &trade)
{
  trade.Print(os);
  return os;
}

inline std::ostream &operator <<(std::ostream &os, const Trade *trade)
{  
  trade->Print(os);
  return os;
}

#endif // TRADE_HPP
