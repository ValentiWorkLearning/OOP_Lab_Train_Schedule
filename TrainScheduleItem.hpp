#ifndef TRAIN_SCHEDULE_ITEM
#define TRAIN_SCHEDULE_ITEM

#include "date.hpp"
#include "Messages.hpp"


#include <string>

class Station;
class Date;

class  TrainScheduleItem
{
public:
	 TrainScheduleItem(Station & _station, Date  _comingTime, Date  _incomingTime);

	 std::string const & getStationName()const;
	 
	 Station const & getStation()const;

	 Date const & getArrivalTime() const ;
	 Date const & getDepartureTime() const ;
private:

	Station &  m_station;
	Date m_arrivalTime;
	Date m_departureTime;
};

#endif
