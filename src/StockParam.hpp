#ifndef STOCKPARAM_HPP
#define STOCKPARAM_HPP

#include <iostream>
#include <string>
#include <memory>
#include "Stock.hpp"

class StockParam
{
public:
  StockParam(std::string s, unsigned int ld, unsigned int v) : m_symbol(s), m_lastDividend(ld), m_value(v) {};
  StockParam(std::string s, unsigned int ld, float fd, unsigned int v): m_symbol(s), m_lastDividend(ld), m_fixedDividend(fd), m_value(v) {};

  static std::shared_ptr<StockParam> Create(std::string s, unsigned int ld, unsigned int v)
  {
    return std::make_shared<StockParam>(s, ld, v);
  };

  static std::shared_ptr<StockParam> Create(std::string s, unsigned int ld, float fd, unsigned int v)
  {
    return std::make_shared<StockParam>(s, ld, fd, v);
  };
  
  std::string GetSymbol() const { return m_symbol; };
  unsigned int GetLastDividend() const { return m_lastDividend; };
  float GetFixedDividend() const { return m_fixedDividend; };
  unsigned int GetValue() const { return m_value; };

private:
  std::string m_symbol;
  unsigned int m_lastDividend;
  float m_fixedDividend;
  unsigned int m_value;
		
};

#endif // STOCKPARAM_HPP
