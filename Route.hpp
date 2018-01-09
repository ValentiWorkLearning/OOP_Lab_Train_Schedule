#ifndef ROUTE_HPP
#define ROUTE_HPP

#include<vector>

#include "TrainScheduleItem.hpp"
#include <memory>
#include <set>
#include <string>

class Route
{
public:

	explicit Route (int _uniqueNumber);
	
	~Route() = default;

	Route (const Route&) = delete;
	
	Route & operator = (const Route &) = delete;

	void addScheduleItem(std::unique_ptr<TrainScheduleItem>   _pScheduleItem);

	bool hasStation(std::string const & _stationName);
private:
	int m_uniqueNumber;
	std::vector < std::unique_ptr<TrainScheduleItem> > m_scheduleItems;

	std::set < std::string  > m_stationNames;
};

#endif
