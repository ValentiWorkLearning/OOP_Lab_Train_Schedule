#include "TrainScheduleItem.hpp"

TrainScheduleItem::TrainScheduleItem(Station & _station		, 
										Date & _comingTime	, 
										Date & _incomingTime)
									:	m_station(_station)	, 
										m_arrivalTime(_comingTime)
									,m_departureTime(_incomingTime)
{
	if (m_arrivalTime > m_departureTime)
		throw std::logic_error(Messages::InvalidTimeSended);
}
