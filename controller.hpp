#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP


#include <map>
#include <string>
#include <memory>
#include <sstream>
#include <vector>
#include <map>
#include <functional>

class Station;
class Train; 
class TrainScheduleItem;
class Route;
class Date;

class Controller
{
public:
	Controller() = default;

	~Controller() = default;

	Controller(Controller const &) = delete;

	Controller & operator = (Controller &) = delete;

	void addStation( std::string const & _stationName, int _nPerons );

	void addTrain(int _uniqueNumber ,int _nPassagersCount);

	void addRoute(int _uniqueNumber);

	void addScheduleItemToRoute(int _routeNumber, std::string const & _stationName, Date _arriveTime, Date  _departureTime);

	void addRouteToTrain(int _routeNumber, int _trainNumber );

	bool hasStationInRoute(int _routeNumber, std::string const & _stationName);

	std::vector<std::string > getMostPopularStations(int  _counter);

	std::vector<std::string> getMostLongRouteList(int _count);

	std::vector<std::pair < std::string, std::string > > getPairedStations(int _count);
private:

	Train * findTrain(int _uniqueNumber);
	
	Route * findRoute(int _uniqueNumber);

	Station & findStation(std::string const & _stationName);
	
	std::map< std::string, std::unique_ptr < Station > > m_stations;

	std::map<int, std::unique_ptr<  Train> > m_trains;

	std::map<int, std::unique_ptr < Route > > m_routes;


};


#endif // !CONTROLLER_HPP

