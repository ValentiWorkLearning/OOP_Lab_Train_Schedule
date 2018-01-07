#ifndef TRAIN_SCHEDULE_ITEM
#define TRAIN_SCHEDULE_ITEM

#include "Messages.hpp"

class Station;
class Date;

class  TrainScheduleItem
{
public:
	 TrainScheduleItem(Station & _station, Date & _comingTime, Date & _incomingTime);

	 TrainScheduleItem(const TrainScheduleItem&) = delete;

	 TrainScheduleItem & operator = (const TrainScheduleItem &) = delete;

private:

	Station &  m_station;
	Date m_arrivalTime;
	Date m_departureTime;
};

#endif
