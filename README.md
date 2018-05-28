====== Super Simple Stock Market Manager ======

===== Comments on the constraints =====

1. The software is written in strict standard C++14 without any external dependencies (by design and tested in isolation on a virtual machine). The tests use the [[https://github.com/catchorg/Catch2|CATCH2]] automated test framework. This framework is a single header file which is provided with the other source files.
2. Some MakeFile and bash scripts are provided:
	a. **build_app.sh** to build the software //via// **Makefile**
	b. **run** **_app.sh** to execute the software
	c. **build_test.sh** to build the tests //via// **Makefile_test**
	d. **run_test.sh** to execute the tests
3. The sample data are hard-coded as neither database nor I/O are allowed. The user interface is purely in command-line as no GUI is allowed.
4. The formula for the //P/E ratio// is ambiguous as no //Dividend// is defined anywhere. For the purpose of this exercice, it has been assumed that //Dividend// meant //Last Dividend//, based on dimensional analysis. It is not specified if the //GBCE All Share Index// should be calculating from the //Volume Weighted Stock Price// for all stocks based on trades in past 5 minutes or based on all trades. For the purpose of this exercice, it has been assumed that it was based on all trades.
5. The functionalities provided are:
	a. consulting the list of stocks
	b. adding new stocks
	c. consulting the list of trades
	d. adding new trades
	e. calculating the //Dividend Yield// for any stock, for any price as input
	f. calculating the //P/E ratio// for any stock, for any price as input
	g. calculating the //Volume Weighted Stock Price// based on trades within the past 5 minutes for any stock
	h. calculating the //GBCE All Share Index// for all stocks

===== Portability =====

The software has been developed on and for GNU/Linux with GCC (4.9.2). The following flags are used: "-std=c++14 -pedantic-errors -Wall -Wextra -Werror".

Microsoft Visual Studio Community 2017 refuses to compile. The error message is: "error C4996: 'localtime': This function or variable may be unsafe. Consider using localtime_s instead.". **localtime** is used for the generation of **TimeStamps** from the current time. **localtime_t** is a Microsoft-only implementation, when **localtime** is part of the C++ standard. This software adheres to the standard. Sorting portability issues due to the non-respect of standards is beyond the scope of this exercice.
 
===== Naming conventions =====

* **class:** MyClass.hpp
* **attribute**: m_thisIsAMember
* **method**: ThisIsAMethod()
* **variable**: var

===== Comments on Stock =====

1. A factory is used
2. As **StockCommon** and **StockPreferred** have a lot in common, the base class **Stock** that they derive from defines the common attributes and methods. However, if other kinds of stocks with different attributes and methods would be added, the level of abstraction should be revised.
3. As no format has been specified for //Stock Symbol//, it is represented by a **std::string** and is case-sensitive (JOE and Joe are not the same symbols).
4. No currency conversion is available: all the prices, values etc. are in the same unit (pence).
5. The variables representing prices, values etc. have therefore been declared as unsigned integers.
6. //Fixed Dividend// is represented in %: 'Fixed Dividend = X' means 'X%'
7. If a calculation is not possible (such as dividing by zero), a **NaN** is explicitly returned.
8. Some of the calculations provide results with fractions of pence. More information on monetary rules is required to round/format these outputs.

===== Comments on Trade =====

1. A factory method is used.

===== Comments on TimeStamp =====

1. A factory method is used.
2. Due to its C ANSI legacy, C++ does not handle date and time very well. Therefore, the class **TimeStamp** suffers from some severe limitations:
	a. it is only possible to calculate a time difference for two **TimeStamps** sharing the same date (as year/month/day).
	b. No time zone is taken into account.
	c. In this software, **TimeStamps** are only generated from the current time (//via// the method **GetNowTimeStamp()**). They should not be used in any other way: there is no control on the values they can take. For example, it is possible to declare a timestamp as 20181332_256161 (for YYYYMMDD_hhmmss).
3. Correcting these limitations would imply to develop a complete library handling dates, times and durations. Such a task is well beyond the scope of the present exercice.
4. Alternatively, this software could take advantage of the [[http://en.cppreference.com/w/cpp/chrono|std::chrono]] library from the next C++ standard (C++20).

===== Comments on StockListing =====

1. A factory method is used .
2. It is essentially a **std::map** with some extra features. As STL containers are not meant to be inherited, composition was used.
3. **StockListing** uses the **Stock** symbol as a unique primary key. This unicity is enforced when an attempt of adding a new stock is made (no addition if the key already exists).

===== Comments on TradeLogBook =====

1. A factory method is used .
2. It is essentially a **std::map** with some extra features. As STL containers are not meant to be inherited, composition was used.
3. **TradeLogBook** uses a static counter as a unique primary key.
4. **GetHistory()** generates a **TradeLogBook** for a given **Stock**, from an optional **TimeStamp** and a duration in seconds. This duration is exclusive (i.e for 30 seconds, only **TimeStamps** strictly within the previous 30 seconds are accepted).
5. For optimisation purposes, a **TradeLogBook** could be defined per **Stock** and use a proper **TimeStamp** as primary key. Therefore, the **Trades** will be ordered by date when added and any request such as calculating the //Volume Weighted Stock Price// would be faster.

===== Comments on StockMarket =====

1. A factory method is used.
2. It is essentially an interface, wrapping a **StockListing** and a **TradeLogBook**.
3. A singleton pattern has not been used: the coexistence of the several instances could be useful (one to treat the real market, several to run simulations).

===== Comments on CLI =====

1. A factory method is used.
2. Standard C++ is not the most adapted language for command-line interfaces. In real development conditions, an API or a more appropriate GUI framework (such as Qt) would be used. CLI.hpp heavily relies on the rest of the code but there is no dependencies to CLI.hpp. Therefore, it can be easily removed and replaced by something more adapted.
3. Some workarounds have been used to compensate the incapaciity of **std::iostream** to control the user's inputs.
4. The control of the inputs is made such a way, that the types are checked before trying to create an object or to call a method.
