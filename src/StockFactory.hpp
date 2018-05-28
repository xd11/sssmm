#ifndef STOCKFACTORY_HPP
#define STOCKFACTORY_HPP

#include <iostream>
#include <string>
#include <memory>
#include "Stock.hpp"
#include "StockParam.hpp"

class StockFactory
{
public:
  static std::shared_ptr<Stock> Create(const std::string &type, std::shared_ptr<StockParam> param)
  {
    std::shared_ptr<Stock> stock;
    if(type == "common")
      {
	stock = std::make_shared<StockCommon>();
	stock->Init(param);
      }
    else if(type == "preferred")
      {
	stock = std::make_shared<StockPreferred>();
	stock->Init(param);
      }
    else
      {
	std::cerr << "StockFactory::Create(): Unknown type of stock (" << type << ")!" << std::endl;
	stock = nullptr;
      }
    return stock;
  }

};

#endif // STOCKFACTORY_HPP
