#include "TrainScheduleItem.hpp"
#include "Station.hpp"
TrainScheduleItem::TrainScheduleItem(Station & _station		, 
										Date  _comingTime	, 
										Date  _incomingTime)
									:	m_station(_station)	, 
										m_arrivalTime(_comingTime)
									,m_departureTime(_incomingTime)
{
	if (m_arrivalTime > m_departureTime)
		throw std::logic_error(Messages::InvalidTimeSended);
}

std::string const & TrainScheduleItem::getStationName()
{
	return m_station.getStationName();
}

Date const & TrainScheduleItem::getArrivalTime()
{
	return m_arrivalTime;
}

Date const & TrainScheduleItem::getDepartureTime()
{
	return m_departureTime;
}
