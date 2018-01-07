#ifndef STAION_HPP
#define STAION_HPP

#include <string>
#include "Messages.hpp"
class Station
{
public:
	explicit Station (  std::string const  & _stationName, int _nPerons );

	std::string & getStationName();
	int getPerronsCount();

	~Station() = default;
private:

	std::string m_Name;
	
	int m_perons;
};
#endif // !STAION_HPP

