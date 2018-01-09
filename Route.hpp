#ifndef ROUTE_HPP
#define ROUTE_HPP

#include<vector>

#include "TrainScheduleItem.hpp"
#include <memory>
#include <set>
#include <string>
#include <functional>

class Route
{
public:

	explicit Route (int _uniqueNumber);
	
	~Route() = default;

	Route (const Route&) = delete;
	
	Route & operator = (const Route &) = delete;

	void addScheduleItem(std::unique_ptr<TrainScheduleItem>   _pScheduleItem);

	bool hasStation(std::string const & _stationName);
	
	

	void  forEachScheduleItem(std::function<void(TrainScheduleItem const &)> _action) const 
	{
		for (auto const & trainPtr : m_scheduleItems) 
		{
			_action( * trainPtr);
		}
	}

private:

	int m_uniqueNumber;

	std::vector < std::unique_ptr<TrainScheduleItem> > m_scheduleItems;

	std::set < std::string  > m_stationNames;
};

#endif
