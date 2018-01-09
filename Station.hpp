#ifndef STAION_HPP
#define STAION_HPP

#include <string>
#include "Messages.hpp"
class Station
{
public:
	explicit Station (  std::string const  & _stationName, int _nPerons );

	std::string const  & getStationName()const ;

	int getPerronsCount() const ;

	~Station() = default;
private:

	std::string m_Name;
	
	int m_perons;
};
#endif // !STAION_HPP

