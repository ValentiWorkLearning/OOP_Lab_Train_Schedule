#include "TrainScheduleItem.hpp"
#include "Station.hpp"

TrainScheduleItem::TrainScheduleItem(   Station & _station              , 
										Date  _comingTime               , 
										Date  _incomingTime):	
										m_station(_station)             , 
										m_arrivalTime(_comingTime)      ,
										m_departureTime(_incomingTime)
{
	if (m_arrivalTime > m_departureTime)
		throw std::logic_error(Messages::InvalidTimeSended);
}

std::string const & TrainScheduleItem::getStationName() const 
{
	return m_station.getStationName();
}

Station const & TrainScheduleItem::getStation() const
{
	return m_station;
}

Date const & TrainScheduleItem::getArrivalTime() const 
{
	return m_arrivalTime;
}

Date const & TrainScheduleItem::getDepartureTime()const 
{
	return m_departureTime;
}
