#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP


#include <map>
#include <string>
#include <memory>

class Station;
class Train; 
class TrainScheduleItem;
class Route;

class Controller
{
public:
	Controller() = default;

	~Controller() = default;

	void addStation( std::string const & _stationName, int _nPerons );

	void addTrain(int _uniqueNumber ,int _nPassagersCount);

	void addRoute(int _uniqueNumber);

	void addScheduleItemToRoute(int _routeNumber, std::unique_ptr<TrainScheduleItem>  _pScheduleItem);

	void addRouteToTrain(int _routeNumber, int _trainNumber );
private:

	Train * findTrain(int _uniqueNumber);
	Route * findRoute(int _uniqueNumber);

	std::map< std::string, std::unique_ptr < Station > > m_stations;

	std::map<int, std::unique_ptr<  Train> > m_trains;

	std::map<int, std::unique_ptr < Route > > m_routes;
};


#endif // !CONTROLLER_HPP

