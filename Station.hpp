#ifndef STATION_HPP
#define STATION_HPP


#include "Messages.hpp"

#include <string>

class Station
{
public:

	Station (  std::string const  & _stationName, int _nPerons );

	~Station() = default;
	
	std::string const  & getStationName()const ;

	int getPerronsCount() const ;

private:

	std::string m_Name;
	
	int m_perons;
};
#endif // !STAION_HPP

