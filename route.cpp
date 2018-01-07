#include "route.hpp"

Route::Route(int _uniqueNumber) : m_uniqueNumber(_uniqueNumber)
{
	if (_uniqueNumber < 0) 
	{
		throw std::logic_error(Messages::BadRouteNumber);
	}
}

<<<<<<< HEAD
void Route::addScheduleItem(TrainScheduleItem const *  _pScheduleItem)
{
	m_scheduleItems.push_back(_pScheduleItem);
=======
void Route::addScheduleItem(std::unique_ptr<TrainScheduleItem>  _pScheduleItem)
{
	m_scheduleItems.push_back(std::move(_pScheduleItem));
>>>>>>> ecf7e5c255b21fe99b66690b3c38e79daad287c1
}
