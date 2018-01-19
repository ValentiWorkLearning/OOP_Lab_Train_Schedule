#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <string>
#include <memory>
#include <vector>
#include <map>
#include <functional>
#include <set>
#include <algorithm>
#include <chrono>

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

	Station & addStation( std::string const & _stationName, int _nPerons );

	Train &  addTrain(int _uniqueNumber ,int _nPassagersCount);

	Route &  addRoute(int _uniqueNumber);

	bool hasStation(std::string const & _stationName);

	bool hasTrain(int _trainNumber);

	bool hasRoute(int _routeNumber);

	void removeStation(std::string const & _stationName);
	
	void removeTrain(int _trainNumber);

	void removeRoute(int _routeNumber);

	std::vector<std::string > getMostPopularStations(int  _counter);

    std::multimap < Date , Route * ,std::greater<Date>>
        getMostLongRoute(int _count);

	std::set<std::pair<Station const *, Station const *>> 
        getPairedStations(int _count);

	std::set <Station const * > getUnusedStations();
	
	std::set<Station const *> getStationsWithNotEnoughtPerons();


    Train & findTrain(int _uniqueNumber) const;

    Route & findRoute(int _uniqueNumber) const;

    Station & findStation(std::string const & _stationName) const;

private:

	std::map< std::string, std::unique_ptr < Station > > m_stations;

	std::map<int, std::unique_ptr< Train > > m_trains;

	std::map<int, std::unique_ptr < Route > > m_routes;
};


#endif // !CONTROLLER_HPP

