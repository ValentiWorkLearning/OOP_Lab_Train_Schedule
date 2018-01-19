// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _DATE_HPP_
#define _DATE_HPP_

/*****************************************************************************/

#include <iostream>

/*****************************************************************************/


class Date
{

	/*-----------------------------------------------------------------*/

public:

	/*-----------------------------------------------------------------*/

	Date();
	Date(int _year, int _month, int _day);
	Date(const char * _yyyyMMDDHHMN, char _sep = '/', char _timeSep = ':');
    Date(const time_t _time);
	int getYear() const;
	int getMonth() const;
	int getDay() const;
	int getHour()const;
	int getMinutes() const;

	bool isLeapYear() const;

	bool operator == (Date d) const;
	bool operator != (Date d) const;
	bool operator < (Date d) const;
	bool operator <= (Date d) const;
	bool operator > (Date d) const;
	bool operator >= (Date d) const;

	void addDay(int _nDay);
	
	int  dayDifference(Date const & _d2)const ;

	int secondsDifference(Date const & _d2)const;
	/*-----------------------------------------------------------------*/

private:

	/*-----------------------------------------------------------------*/

	bool isValid() const;
	/*-----------------------------------------------------------------*/

	int m_year, m_month, m_day, m_hour, m_mins;

	/*-----------------------------------------------------------------*/

};


/*****************************************************************************/


inline int Date::getYear() const
{
	return m_year;
}


/*****************************************************************************/


inline int Date::getMonth() const
{
	return m_month;
}


/*****************************************************************************/


inline int Date::getDay() const
{
	return m_day;
}

inline int Date::getHour()const
{
	return m_hour;
}

inline int Date::getMinutes()const
{
	return m_mins;
}
/*****************************************************************************/

std::ostream & operator << (std::ostream & o, Date d);

std::istream & operator >> (std::istream & i, Date & d);

/*****************************************************************************/

#endif //  _DATE_HPP_