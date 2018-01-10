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

bool Route::hasStation(std::string const & _stationName)
{
	return(m_stationNames.find(_stationName) == m_stationNames.end() )? false:true ;
}

int const & Route::getRouteNumber(void)const
{
	return m_uniqueNumber;
}

Station const & Route::getStartStation(void)
{
	return m_scheduleItems.front().get()->getStation();
}

Station const & Route::getLastStation(void)
{
	return m_scheduleItems.back().get()->getStation();
}

time_t Route::getRouteDuration(void)
{
	time_t returnResult = m_scheduleItems.front()->getArrivalTime().secondsDifference(m_scheduleItems.back()->getDepartureTime());
	return returnResult;
}


