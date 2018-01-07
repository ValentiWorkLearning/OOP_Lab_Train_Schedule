#ifndef TRAIN_SCHEDULE_ITEM
#define TRAIN_SCHEDULE_ITEM

<<<<<<< HEAD
#include "Messages.hpp"

class Station;
class Date;
=======
#include "date.hpp"
#include "Messages.hpp"

class Station;
>>>>>>> ecf7e5c255b21fe99b66690b3c38e79daad287c1

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
