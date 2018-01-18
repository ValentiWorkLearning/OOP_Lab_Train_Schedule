#include "route.hpp"

Route::Route(int _uniqueNumber) : m_uniqueNumber(_uniqueNumber)
{
	if (_uniqueNumber < 0) 
	{
		throw std::logic_error(Messages::BadRouteNumber);
	}
}

void Route::addScheduleItem(TrainScheduleItem _pScheduleItem)
{
    if (hasStation(_pScheduleItem.getStationName())) 
    {
        throw std::logic_error(Messages::StationAlreadyExistInSchedule);
    }

    if (!m_scheduleItems.empty()) 
    {
        if (m_scheduleItems.back().getDepartureTime() > _pScheduleItem.getArrivalTime()) 
        {
            throw std::logic_error(Messages::IncorrectGetArrivalTimeValue);
        }
    }

    m_stationNames.insert(_pScheduleItem.getStationName());
    m_scheduleItems.emplace_back(_pScheduleItem);
}

bool Route::hasStation(std::string const & _stationName) const 
{
	return(m_stationNames.find(_stationName) != m_stationNames.end() )? true:false ;
}

int const & Route::getRouteNumber()const
{
	return m_uniqueNumber;
}

Station const & Route::getStartStation() const 
{
    return startRoute().getStation();
}

Station const & Route::getLastStation() const 
{
    return endRoute().getStation();
}

TrainScheduleItem const & Route::startRoute() const 
{
    return m_scheduleItems.front();
}

TrainScheduleItem const & Route::endRoute() const 
{
    return m_scheduleItems.back();
}


time_t Route::getRouteDuration()
{
    if (m_scheduleItems.empty())
    {
        throw std::logic_error(Messages::EmptyRoute);
    }
    time_t returnResult = m_scheduleItems.front().getArrivalTime().secondsDifference(m_scheduleItems.back().getDepartureTime());
    return returnResult;
}

void Route::forEachScheduleItem(std::function<void(TrainScheduleItem const &)> _action) const 
{
	for (auto const & trainPtr : m_scheduleItems)
	{
		_action(trainPtr);
	}
}

