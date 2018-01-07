#ifndef ROUTE_HPP
#define ROUTE_HPP

#include<vector>

#include "TrainScheduleItem.hpp"
#include <memory>
#include <set>

class Route
{
public:

	explicit Route (int _uniqueNumber);
	
	~Route() = default;

	Route(const Route&) = delete;
	
	Route & operator = (const Route &) = delete;

	void addScheduleItem(TrainScheduleItem const *  _pScheduleItem);

private:
	int m_uniqueNumber;
	std::vector < TrainScheduleItem const *  > m_scheduleItems;

	std::set < TrainScheduleItem const * > m_searchItems;
};

#endif
