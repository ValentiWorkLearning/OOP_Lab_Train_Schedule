#include "route.hpp"

Route::Route(int _uniqueNumber) : m_uniqueNumber(_uniqueNumber)
{
	if (_uniqueNumber < 0) 
	{
		throw std::logic_error(Messages::BadRouteNumber);
	}
}

void Route::addScheduleItem(std::unique_ptr<TrainScheduleItem>  _pScheduleItem)
{
	m_scheduleItems.push_back(std::move(_pScheduleItem));
}
