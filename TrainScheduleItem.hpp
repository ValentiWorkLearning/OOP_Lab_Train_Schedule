#ifndef TRAIN_SCHEDULE_ITEM
#define TRAIN_SCHEDULE_ITEM


class Station;
class Date;

#include "date.hpp"
#include "Messages.hpp"
#include <string>

class  TrainScheduleItem
{
public:
	 TrainScheduleItem(Station & _station, Date  _comingTime, Date  _incomingTime);

	 TrainScheduleItem(const TrainScheduleItem&) = delete;

	 TrainScheduleItem & operator = (const TrainScheduleItem &) = delete;

	 std::string const & getStationName();

	 Date const & getArrivalTime();
	 Date const & getDepartureTime();
private:

	Station &  m_station;
	Date m_arrivalTime;
	Date m_departureTime;
};

#endif
