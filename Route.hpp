#ifndef ROUTE_HPP
#define ROUTE_HPP

#include "TrainScheduleItem.hpp"

#include <vector>
#include <memory>
#include <set>
#include <string>
#include <functional>
#include <ctime>

class Route
{
public:

	explicit Route (int _uniqueNumber);
	
	~Route() = default;

	Route (const Route&) = delete;
	
	Route & operator = (const Route &) = delete;

	void addScheduleItem(TrainScheduleItem  _pScheduleItem);
	
    bool hasStation(Station const & _station)const;

	int const & getRouteNumber() const;

    TrainScheduleItem const & startRoute() const ;

    TrainScheduleItem const & endRoute() const ;

	time_t getRouteDuration();
	
	void  forEachScheduleItem(std::function<void(TrainScheduleItem const &)> _action) const;

private:

    std::vector < TrainScheduleItem > m_scheduleItems;
	std::set < std::string  > m_stationNames;
	
	int m_uniqueNumber;
};

#endif
