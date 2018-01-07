#include "Station.hpp"

Station::Station( std::string const & _stationName, int _nPerons):m_Name(_stationName), m_perons(_nPerons)
{
	if (_nPerons <= 0)
		throw std::logic_error(Messages::InvalidPeronsCpunt);

	if (_stationName.empty())
		throw std::logic_error(Messages::StationNameEmpty);
}

std::string & Station::getStationName()
{
	return m_Name;
}

int Station::getPerronsCount()
{
	return m_perons;
}
