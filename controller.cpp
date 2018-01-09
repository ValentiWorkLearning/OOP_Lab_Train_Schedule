#include "controller.hpp"

#include "Station.hpp"
#include "Train.hpp"
#include "TrainScheduleItem.hpp"
#include "route.hpp"

void Controller::addStation(std::string const & _stationName, int _nPerons)
{
	m_stations.insert({ _stationName, std::make_unique<Station>(_stationName, _nPerons) });
}

void Controller::addTrain(int _uniqueNumber,int _nPassagersCount)
{
	if (m_trains.find(_uniqueNumber) == m_trains.end())
	{
		m_trains.insert({ _uniqueNumber, std::make_unique<Train>(_uniqueNumber, _nPassagersCount) });
	}
	else
	{
		throw std::logic_error(Messages::DuplicateTrain);
	}
}

void Controller::addRoute(int _uniqueNumber)
{
	if (m_routes.find(_uniqueNumber) == m_routes.end()) 
	{
		m_routes.insert({ _uniqueNumber,  std::make_unique<Route>(_uniqueNumber)  });
	}
}

void Controller::addScheduleItemToRoute(int _routeNumber, std::string const & _stationName, Date  _arriveTime, Date _departureTime)
{
	findRoute(_routeNumber)->addScheduleItem( std::make_unique<TrainScheduleItem>( findStation(_stationName), _arriveTime, _departureTime) );
}

void Controller::addRouteToTrain(int _routeNumber, int _trainNumber)
{
	findTrain( _trainNumber )->setRoute( findRoute(_routeNumber) );
}

bool Controller::hasStationInRoute(int _routeNumber, std::string const & _stationName)
{
	return findRoute(_routeNumber)->hasStation(_stationName);;
}

std::vector<std::string> Controller::getMostPopularStations(int  _counter)
{
	std::vector<std::string > returnResult;

	std::map<std::string, int> stationCounter;
	
	for (auto it = m_stations.begin(); it != m_stations.end(); it++) 
	{
		stationCounter.insert({ it->second->getStationName(), 0 });
	}

	for (auto it = m_routes.begin(); it != m_routes.end(); it++) 
	{
		for (auto it1 = m_stations.begin(); it1 != m_stations.end(); it1++) 
		{
			if (it->second->hasStation(it1->second->getStationName())) 
			{
				stationCounter[it1->second->getStationName()]++;
			}
		}
	}

	std::multimap<int, std::string,std::greater<int>> greaterStation; 
	
	for (auto it = stationCounter.begin(); it != stationCounter.end(); it++) 
	{
		greaterStation.emplace( it->second, it->first );
	}

	for (auto it = greaterStation.begin(); it != greaterStation.end(); it++) 
	{
		static int i = 0;
		if (i == _counter) break;

		returnResult.push_back(it->second + ":"  + std::to_string( it->first) );
		i++;
	}
	return returnResult;
}

Train * Controller::findTrain(int _uniqueNumber)
{
	auto it = m_trains.find(_uniqueNumber);
	if (it == m_trains.end()) 
	{
		throw std::logic_error(Messages::TrainDoesNotExist);
	}
	return it->second.get();
}

Route * Controller::findRoute(int _uniqueNumber)
{

	auto it = m_routes.find(_uniqueNumber);
	if (it == m_routes.end())
	{
		throw std::logic_error(Messages::RouteDoesNotExist);
	}
	return it->second.get();
}

Station & Controller::findStation(std::string const & _stationName)
{
	auto it = m_stations.find(_stationName);
	if (it == m_stations.end())
	{
		throw std::logic_error(Messages::StationDoesNotExist);
	}
	return *it->second;
}
