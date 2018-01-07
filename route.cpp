#include "route.hpp"

Route::Route(int _uniqueNumber) : m_uniqueNumber(_uniqueNumber)
{
	if (_uniqueNumber < 0) 
	{
		throw std::logic_error(Messages::BadRouteNumber);
	}
}

void Route::addScheduleItem(std::unique_ptr<TrainScheduleItem>_pScheduleItem)
{
	if (m_stationNames.find(_pScheduleItem->getStationName()) == m_stationNames.end())
	{
		if (m_scheduleItems.empty() || (m_scheduleItems.back()->getDepartureTime() <= _pScheduleItem->getArrivalTime()))
		{
			m_stationNames.insert(_pScheduleItem->getStationName());
			m_scheduleItems.push_back(std::move(_pScheduleItem));
		}
		else 
		{
			throw std::logic_error(Messages::IncorrectGetArrivalTimeValue);
		}
	}
	else 
	{
		throw std::logic_error(Messages::StationAlreadyExistInSchedule);
	}
}

