#ifndef TIMESTAMP_HPP
#define TIMESTAMP_HPP

#include <iostream>
#include <string>
#include <memory>
#include <ctime>

class TimeStamp
{
public:
  TimeStamp(unsigned int date, unsigned int time) : m_date(date), m_time(time) { };

  unsigned int GetDate() const { return m_date; };
  unsigned int GetTime() const { return m_time; };

  static std::shared_ptr<TimeStamp> Create(unsigned int date, unsigned int time)
  {
    return std::make_shared<TimeStamp>(date, time);
  }

  static std::shared_ptr<TimeStamp> GetNowTimeStamp()
  {
    time_t rawtime;
    struct tm * timeinfo;
    time (&rawtime);
    timeinfo = localtime(&rawtime);
    
    char chdate[80];
    strftime(chdate, 80, "%Y%m%d", timeinfo);
    std::string sdate(chdate);
    auto date = std::stoul(chdate);
    
    char chtime[80];
    strftime(chtime, 80, "%H%M%S", timeinfo);
    std::string stime(chtime);
    auto time = std::stoul(chtime);

    auto timestamp = TimeStamp::Create(date,time);
    return timestamp;
  };

  void Print(std::ostream &os = std::cout) const
  {
    os <<  m_date << "_" << m_time;
  };

  unsigned int ConvertTimeToSecond()
  {
    auto hour = m_time/10000;
    auto minute = m_time%10000/100;
    auto second = m_time%100;

    unsigned int total_second = (unsigned int)(hour*3600+minute*60+second);
    
    return total_second;
  };

  static unsigned int ConvertSecondToTime(int seconds)
  {
    if (seconds < 0)
      {
	return -1;
      }
    else
      {
	auto hour  = seconds/3600;
	auto minute = (seconds - hour*3600) / 60;
	auto second = (seconds - hour*3600) - minute*60;
	
	unsigned int time = (unsigned int)(hour*10000+minute*100+second);
	
	return time;
      }
  };
  
  static int CompareTime(std::shared_ptr<TimeStamp> t1,  std::shared_ptr<TimeStamp> t2)
  {
    if(IsSameDate(t1, t2))
      {
	return (t2->ConvertTimeToSecond() - t1->ConvertTimeToSecond());
       
      }
    else
      {
	return -999999999;
      }
  };

  static bool IsSameDate(std::shared_ptr<TimeStamp> t1,  std::shared_ptr<TimeStamp> t2)
  {
    if(t1->m_date == t2->m_date)
      return true;
    else
      return false;
  };
  
private:
  unsigned int m_date;
  unsigned int m_time;
  
};

// *****************************************************************************
inline std::ostream &operator <<(std::ostream &os, TimeStamp const &timestamp)
{
  timestamp.Print(os);
  return os;
}

inline std::ostream &operator <<(std::ostream &os, const TimeStamp *timestamp)
{  
  timestamp->Print(os);
  return os;
}

#endif // TIMESTAMP_HPP
