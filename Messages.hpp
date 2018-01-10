#ifndef MESSAGES_HPP
#define MESSAGES_HPP

namespace Messages 
{

	const char * const StationNameEmpty = "Station name empty ";
	const char * const InvalidPeronsCount = "Invalid  perons  count ";
	const char * const InvalidTimeSended = "Invalid coming ";
	const char * const InvalidPasegersCount = "Invalid passagers count";
	const char * const InvalidTrainNumber = "Invalid train number";
	const char * const DuplicateTrain = "Duplicate train inserted";
	const char * const BadRouteNumber = "Bad route number < 0 ";
	const char * const TrainDoesNotExist = "Train doesn`t exist";
	const char * const RouteDoesNotExist = "Route doesn`t exist";
	const char * const RouteAlreadySet = "Route has setted on train yet";
	const char * const StationDoesNotExist = "Station doesn`t exist";
	const char * const StationAlreadyExistInSchedule = "Station already exist in schedule. Train can`t return to the prrevious station";
	const char * const IncorrectGetArrivalTimeValue = "Arrival time less than depature time in previos schedule item";
}

#endif