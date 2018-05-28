#ifndef STOCK_HPP
#define STOCK_HPP

#include <iostream>
#include <string>
#include <memory>
#include <limits>
#include "StockParam.hpp"

class Stock
{
public:
  std::string GetSymbol() const { return m_symbol; };
  
  virtual float GetDividendYield(float price) const = 0;
  
  float GetPERatio(float price) const
  {
    auto dividend = m_lastDividend;
    if(dividend != 0)
      return price/dividend;
    else
      {
	std::cerr << "Stock::GetPERatio() (" << m_symbol << "): Dividing by zero!"<< std::endl;
	return std::numeric_limits<float>::quiet_NaN();
      }
  };
  
  virtual void Init(std::shared_ptr<StockParam> param)
  {
    m_symbol = param->GetSymbol();
    m_lastDividend = param->GetLastDividend();
    m_value = param->GetValue();
  }
  
  virtual void Print(std::ostream &os = std::cout) const
  {
    os << GetSymbol() << ",Unspecified," << m_lastDividend << ",," << m_value;
  };

    
protected:
  std::string m_symbol;
  unsigned int m_lastDividend;
  unsigned int m_value;
};

// *****************************************************************************
class StockCommon : public Stock
{
public:
  float GetDividendYield(float price) const override
  {
    if(price != 0)
      return (float)m_lastDividend/price;
    else
      {
	std::cerr << "StockCommon::GetDividendYield() (" << m_symbol << "): Dividing by zero!"<< std::endl;
	return std::numeric_limits<float>::quiet_NaN();
      }
  };
  
  void Print(std::ostream &os) const override
  {
    os << GetSymbol() << ",common," << m_lastDividend << ",," << m_value;
  }
};

// *****************************************************************************
class StockPreferred : public Stock
{
public:
  float GetDividendYield(float price) const override
  {
    if(price != 0)
      return m_fixedDividend*m_value/price/100;
    else
      {
	std::cerr << "StockPreferred::GetDividendYield() (" << m_symbol << "): Dividing by zero!"<< std::endl;
	return std::numeric_limits<float>::quiet_NaN();
      }
  };
    
  void Print(std::ostream &os) const override
  {
    os << GetSymbol() << ",preferred," << m_lastDividend << "," << m_fixedDividend << "," << m_value;
  }

  void Init(std::shared_ptr<StockParam> param)
  {
    Stock::Init(param);
    m_fixedDividend = param->GetFixedDividend();
  }
  
protected:
  float m_fixedDividend;
  
};

// *****************************************************************************
inline std::ostream &operator <<(std::ostream &os, Stock const &stock)
{
  stock.Print(os);
  return os;
}

inline std::ostream &operator <<(std::ostream &os, const Stock *stock)
{  
  stock->Print(os);
  return os;
}

#endif // STOCK_HPP
