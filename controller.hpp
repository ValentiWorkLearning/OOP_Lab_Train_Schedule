#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP


#include <map>
#include <string>
#include <memory>

class Station;
class Train; 
class TrainScheduleItem;
class Route;
<<<<<<< HEAD
class Date;
=======
>>>>>>> ecf7e5c255b21fe99b66690b3c38e79daad287c1

class Controller
{
public:
	Controller() = default;

	~Controller() = default;

	void addStation( std::string const & _stationName, int _nPerons );

	void addTrain(int _uniqueNumber ,int _nPassagersCount);

	void addRoute(int _uniqueNumber);

<<<<<<< HEAD
	void addScheduleItem(std::string const & _stationName, Date _arrivalTime, Date _departureTime );

	void addScheduleItemToRoute(int _routeNumber,  TrainScheduleItem  const *  _pScheduleItem);
=======
	void addScheduleItemToRoute(int _routeNumber, std::unique_ptr<TrainScheduleItem>  _pScheduleItem);
>>>>>>> ecf7e5c255b21fe99b66690b3c38e79daad287c1

	void addRouteToTrain(int _routeNumber, int _trainNumber );
private:

	Train * findTrain(int _uniqueNumber);
	Route * findRoute(int _uniqueNumber);

	std::map< std::string, std::unique_ptr < Station > > m_stations;

	std::map<int, std::unique_ptr<  Train> > m_trains;

	std::map<int, std::unique_ptr < Route > > m_routes;
};


#endif // !CONTROLLER_HPP

