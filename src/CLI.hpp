#ifndef CLI_HPP
#define CLI_HPP

#include <iostream>
#include <string>
#include <memory>
#include <ctype.h>
#include "StockFactory.hpp"
#include "Stock.hpp"
#include "StockParam.hpp"
#include "Trade.hpp"
#include "TimeStamp.hpp"
#include "StockMarket.hpp"

class CLI
{
public:
  CLI(std::shared_ptr<StockMarket> sm) : m_stockMarket(sm) { };

  static std::shared_ptr<CLI> Create(std::shared_ptr<StockMarket> sm)
  {
    return std::make_shared<CLI>(sm);
  };

  // **************************************** GENERIC METHODS ****************************************
  static void ClearScreen(std::ostream &os = std::cout)
  {
    os << std::string(50,'\n');
  };

  static void Separator(std::ostream &os = std::cout)
  {
    os << "¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤" << std::endl;
  };

  static unsigned short MultipleChoice(std::string question, unsigned short max, std::istream &is = std::cin, std::ostream &os = std::cout)
  {
    float answer = -1;
    os << question << std::endl;
    os << "Please enter your choice [1-" << max << "]:" << std::endl;
    while(1)
      {
	is >>  answer;
	if(is.fail() || answer < 1 || answer > max || ceilf(answer) != answer)
	  {
	    is.clear();
	    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	    os << "Please enter your choice [1-" << max << "]:" << std::endl;
	  }
	else
	  {
	    break;
	  }
      }
    return (unsigned int)answer;
  };

  static unsigned int GetPositiveInteger(std::istream &is = std::cin, std::ostream &os = std::cout)
  {
    os << "Please enter a positive integer:" << std::endl;
    float answer = -1;
    while(1)
      {
	is >> answer;
	if(is.fail() || answer < 0 || ceilf(answer) != answer)
	  {
	    is.clear();
	    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	    os << "Please enter a positive integer:" << std::endl;
	  }
	else
	  {
	    break;
	  }
      }
    return (unsigned int)answer;
  };

  
  static float GetPositiveFloat(std::istream &is = std::cin, std::ostream &os = std::cout)
  {
    os << "Please enter a positive float:" << std::endl;
    float answer = -1;
    while(1)
      {
	is >> answer;
	if(is.fail() || answer < 0)
	  {
	    is.clear();
	    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	    os << "Please enter a positive float:" << std::endl;
	  }
	else
	  {
	    break;
	  }
      }
    return answer;
  };

  static std::string GetString(std::istream &is = std::cin, std::ostream &os = std::cout)
  {
    std::string answer = "";
    os << "Please enter a non-empty string:" << std::endl;
    while(1)
      {
	is >> answer;
	if(is.fail() || answer.empty())
	  {
	    is.clear();
	    os << "Please enter a non-empty string:" << std::endl;
	  }
	else
	  {
	    break;
	  }
      }
    return answer;
  };



  // **************************************** SPECIFIC METHODS ****************************************
  void Header(std::ostream &os = std::cout)
  {
    Separator();
    os << "¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤ Super Simple Stock Market Manager ¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤" << std::endl;
    Separator();
    os << "The Stock Market you are working on is: " << m_stockMarket->GetName() << std::endl;
  };

  void BackToMainMenu(std::istream &is = std::cin, std::ostream &os = std::cout)
  {
    os << "¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤" << std::endl;
    os << "Press 'b' and then 'Enter' to go back to the main menu" << std::endl;
    std::string key = "a";
    while(1)
      {
	is >> key;
	if(is.fail() || key !=  "b")
	  {
	    is.clear();
	    os << "Press 'b' and then 'Enter' to go back to the main menu" << std::endl;
	  }
	else
	  {
	    ClearScreen();
	    Header();
	    MainMenu();
	    break;
	  }
      } 
  };

  void MainMenu(std::ostream &os = std::cout)
  {
    os << "Available actions" << std::endl;
    os << "¤¤¤¤¤ Stocks ¤¤¤¤¤" << std::endl;
    os << "1. Display available stocks (CSV)" << std::endl;
    os << "2. Add a new stock to the market" << std::endl;
    os << "3. Get the dividend yield of a stock " << std::endl;
    os << "4. Get the P/E ratio of a stock" << std::endl;
    os << "¤¤¤¤¤ Trades ¤¤¤¤¤" << std::endl;
    os << "5. Consult the trade log book (CSV)" << std::endl;
    os << "6. Register a new trade" << std::endl;
    os << "7. Get the Volume Weighted Stock Price of a stock (last 5 min)" << std::endl;
    os << "¤¤¤¤¤ Stock Market ¤¤¤¤¤" << std::endl;
    os << "8. Get the GBCE" << std::endl;
    os << "¤¤¤¤¤ Other actions ¤¤¤¤¤" << std::endl;
    os << "9. Exit the programme" << std::endl;
    
    Separator();
    auto answer = MultipleChoice("What would like to do?", 9);
    this->MainMenuAction(answer);
    
  };

  void MainMenuAction(unsigned short choice, std::ostream &os = std::cout)
  {
    ClearScreen();
    Separator();
    switch (choice)
      {
      case 1:;
	os << m_stockMarket->GetStockListing();
	break;
      case 2:
	AddStock();
	break;
      case 3:
	GetStockDividendYield();
	break;
      case 4:
	GetStockPERatio();
	break;
      case 5:;
	os << m_stockMarket->GetTradeLogBook();
	break;
      case 6:
	AddTrade();
	break;
      case 7:
	GetVWSP();
	break;
      case 8:
	os << "Current GBCE = " << m_stockMarket->GetGBCE() << std::endl;
	break;
      case 9:
	exit(0);
      default:
	os <<  "Unknown option" << std::endl;
      }
    BackToMainMenu();
  };

  std::shared_ptr<Stock> GetStock(std::string symbol)
  {
    auto listing = m_stockMarket->GetStockListing()->GetListing();
    if (listing.find(symbol) != listing.end())
      {
	return listing.at(symbol);
      }
    else
      {
	return nullptr;
      }
  };


  void AddStock(std::istream &is = std::cin, std::ostream &os = std::cout)
  {
    // type
    os << "¤¤¤¤¤ Types available ¤¤¤¤¤" << std::endl;
    os << "1. common" << std::endl;
    os << "2. preferred" << std::endl;
    Separator();
    auto type = MultipleChoice("Which type of stock to add?", 2);
    std::string typeName;
    if (type == 1)
      {
	typeName = "common";
      }
    else if (type == 2)
      {
	typeName = "preferred";
      }
    else
      {
	os << "Error: Type of Stock unknown" << std::endl;
	BackToMainMenu();
      }

    // symbol
    os << "Name for the new stock - ";
    auto symbol = GetString(is, os);
    if(GetStock(symbol))
      {
	os << "Error: Stock (" << symbol << ") already exists" << std::endl;
	BackToMainMenu();
      }

    // lastDividend
    os << "Last dividend - ";
    auto lastDividend = GetPositiveInteger(is, os);
    
    // value
    os << "Par value - ";
    auto value = GetPositiveInteger(is, os);

    std::shared_ptr<StockParam> param;
    if(typeName == "common")
      {
        param =  StockParam::Create(symbol, lastDividend, value);
      }
    else if (typeName == "preferred")
      {
	// fixedDividend
	os << "Fixed dividend (%) - ";
	auto fixedDividend = GetPositiveFloat(is, os);
        param =  StockParam::Create(symbol, lastDividend, fixedDividend, value);
      }
    else
      {
	os << "Error: Type of Stock unknown" << std::endl;
	BackToMainMenu();
      }

    auto stock = StockFactory::Create(typeName, param);
    m_stockMarket->AddStock(stock);
    os << "Stock (" << stock->GetSymbol() << ") added" << std::endl;
  };



  void AddTrade(std::istream &is = std::cin, std::ostream &os = std::cout)
  {
    os << "Stock to be traded - ";
    auto symbol = GetString(is, os);
    auto stock = GetStock(symbol);
    if (!stock)
      {
	os << "Error: Stock (" << symbol << ") unknown" << std::endl;
	BackToMainMenu();
      }

    // action
    os << "¤¤¤¤¤ Actions available ¤¤¤¤¤" << std::endl;
    os << "1. BUY" << std::endl;
    os << "2. SELL" << std::endl;
    Separator();
    auto type = MultipleChoice("Which trading action?", 2);
    TradeAction action;
    if (type == 1)
      {
	action = TradeAction::BUY;
      }
    else if (type == 2)
      {
        action = TradeAction::SELL;
      }
    else
      {
	os << "Error: Type of Action unknown" << std::endl;
	BackToMainMenu();
      }

    // quantity
    os << "Quantity - ";
    auto quantity = GetPositiveInteger(is, os);
    
    // price
    os << "Price - ";
    auto price = GetPositiveInteger(is, os);

    // time stamp
    auto timeStamp = TimeStamp::GetNowTimeStamp();

    auto trade = Trade::Create(stock, quantity, action, price, timeStamp);
    m_stockMarket->AddTrade(trade);
    os << "Trade added" << std::endl;
  };

  
  void GetStockDividendYield(std::istream &is = std::cin, std::ostream &os = std::cout)
  {
    os << "Stock to test - ";
    auto symbol = GetString(is, os);
    auto stock = GetStock(symbol);
    
    if (stock)
      {
	os << "Price to test - ";
	auto price = GetPositiveInteger(is, os);
	os << "The dividend yield for the stock (" << symbol << ") and the price " << price << " is: " << stock->GetDividendYield(price) << std::endl;
      }
    else
      {
	os << "Error: Stock (" << symbol << ") unknown" << std::endl;
      }
    
    BackToMainMenu();
  };

  void GetStockPERatio(std::istream &is = std::cin, std::ostream &os = std::cout)
  {
    os << "Stock to test - ";
    auto symbol = GetString(is, os);
    auto stock = GetStock(symbol);
    
    if (stock)
      {
	os << "Price to test - ";
	auto price = GetPositiveInteger(is, os);
	os << "The P/E ratio for the stock (" << symbol << ") and the price " << price << " is: " << stock->GetPERatio(price) << std::endl;
      }
    else
      {
	os << "Error: Stock (" << symbol << ") unknown" << std::endl;
      }
    
    BackToMainMenu();
  };

  void GetVWSP(std::istream &is = std::cin, std::ostream &os = std::cout)
  {
    os << "Stock you want information on - ";
    auto symbol = GetString(is, os);
    auto stock = GetStock(symbol);
    
    if (stock)
      {
	auto tradelogbook = m_stockMarket->GetTradeLogBook();
	auto vwsp = tradelogbook->GetHistory(stock)->GetVolumeWeightedStock(stock);
	os << "The Volume Weighted Stock Price for the stock (" << symbol << ") for the last 5 minutes is: " << vwsp << std::endl;
      }
    else
      {
	os << "Error: Stock (" << symbol << ") unknown" << std::endl;
      }
    
    BackToMainMenu();
  };

private:
  std::shared_ptr<StockMarket> m_stockMarket;

};

#endif // CLI_HPP
