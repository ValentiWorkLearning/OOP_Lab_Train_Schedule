// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

/*****************************************************************************/

#include "date.hpp"

#include <ctime>
#include <cassert>
#include <cstdio>
#include <stdexcept>

/*****************************************************************************/


Date::Date()
{
	time_t currentTime = time(nullptr);

	tm* currentTM = gmtime(&currentTime);

	m_year = currentTM->tm_year + 1900;
	m_month = currentTM->tm_mon + 1;
	m_day = currentTM->tm_mday;
	m_mins = currentTM->tm_min;
	m_hour = currentTM->tm_hour;
}


/*****************************************************************************/


Date::Date(int _year, int _month, int _day)
	: m_year(_year), m_month(_month), m_day(_day)
{
	if (!isValid())
		throw std::logic_error("Error: date is not valid!");
}


/*****************************************************************************/


Date::Date(const char * _yyyyMMDDHHMN, char _sep, char _timeSep)
{
	char sep1, sep2, sep3, sep4;
	int nMatched = sscanf(_yyyyMMDDHHMN, "%d%c %d%c %d%c %d%c %d", &m_year, &sep1, &m_month, &sep2, &m_day, &sep3, &m_hour, &sep4, &m_mins);
	if (nMatched != 9 || sep1 != _sep || sep2 != _sep || sep3 != _sep || sep4 != _timeSep)
		throw std::logic_error("Error: date format is incorrect!");

	if (!isValid())
		throw std::logic_error("Error: date is not valid!");
}


/*****************************************************************************/


bool Date::isValid() const
{
	if (m_year == 0)
		return false;

	if (m_month < 1 || m_month > 12)
		return false;
	if (m_hour > 23 || m_hour < 0)
		return false;

	if (m_mins < 0 || m_mins>59)
		return false;

	if (m_day < 1)
		return false;

	else if (m_month == 2 && isLeapYear())
		return m_day <= 29;

	else
	{
		static const int s_daysInMonth[] = {
			31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
		};

		return m_day <= s_daysInMonth[m_month - 1];
	}
}


/*****************************************************************************/


bool Date::isLeapYear() const
{
	if (m_year % 4 != 0)
		return false;

	else if (m_year % 100 == 0)
		return (m_year % 400 == 0);

	return true;
}


/*****************************************************************************/


bool Date::operator == (Date d) const
{
	return m_year == d.getYear() && m_month == d.getMonth() && m_day == d.getDay() && m_mins == d.getMinutes() && m_hour == d.getHour();
}


/*****************************************************************************/


bool Date::operator != (Date d) const
{
	return !(*this == d);
}


/*****************************************************************************/


bool Date::operator < (Date d) const
{
	if (m_year < d.getYear())
		return true;

	else if (m_year == d.getYear())
	{
		if (m_month < d.getMonth())
		{
			return true;
		}

		else if (m_month == d.getMonth())
		{
			if (m_day < d.getDay())
			{
				return true;
			}
			else if (m_day == d.getDay())
			{
				if (m_hour < d.getHour())
				{
					return true;
				}
				else if (m_hour == d.getHour())
				{
					return m_mins < d.getMinutes();
				}
				else if (m_hour > d.getHour()) 
				{
					return false;
				}
			}
			return false;
		}
		return false;
	}
	return false;
}


/*****************************************************************************/


bool Date::operator > (Date d) const
{
	return d < *this;
}


/*****************************************************************************/


bool Date::operator <= (Date d) const
{
	return (*this < d) || (*this == d);
}


/*****************************************************************************/


bool Date::operator >= (Date d) const
{
	return (d < *this) || (*this == d);
}

void Date::addDay(int _nDay)
{
	static const int s_daysInMonth[] =
	{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	m_day += _nDay;

	if (m_day > s_daysInMonth[m_month - 1])
	{
		m_day -= s_daysInMonth[m_month - 1];
		m_month++;
	}

	if (m_month > 12)
	{
		m_month = 1;
		m_year++;
	}

}

int Date::dayDifference(const Date & _d2)const 
{
	//tm_sec , tm_min, tm_hour, tn_mday, tm_mon, tm_year
	struct tm thisTime { 0, 0, 0, getDay(), (getMonth() - 1), (getYear() - 1900) };

	struct tm incomingTime { 0, 0, 0, _d2.getDay(), (_d2.getMonth() - 1), (_d2.getYear() - 1900) };

	time_t thisTime_t;
	time_t incomingTime_t;

	double difference = 0;
	const int SedondsInDay = 86400;

	thisTime_t = mktime(&thisTime);
	incomingTime_t = mktime(&incomingTime);

	difference = difftime(incomingTime_t, thisTime_t);

	return difference / SedondsInDay;
}

int Date::secondsDifference(const Date & _d2) const 
{
	struct tm thisTime { 0, getMinutes(), getHour(), getDay(), (getMonth() - 1), (getYear() - 1900) };

	struct tm incomingTime { 0, _d2.getMinutes(), _d2.getHour(), _d2.getDay(), (_d2.getMonth() - 1), (_d2.getYear() - 1900) };

	time_t thisTime_t;
	time_t incomingTime_t;

	double difference = 0;
	
	thisTime_t = mktime(&thisTime);
	incomingTime_t = mktime(&incomingTime);

	difference = difftime(incomingTime_t, thisTime_t);

	return difference ;
}
/*****************************************************************************/


std::ostream & operator << (std::ostream & o, Date d)
{
	o << d.getYear() << '/' << d.getMonth() << '/' << d.getDay();
	return o;
}


/*****************************************************************************/


std::istream & operator >> (std::istream & i, Date & d)
{
	char buf[100];
	i >> buf;

	d = Date(buf);
	return i;
}


/*****************************************************************************/