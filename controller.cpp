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

std::vector<std::string> Controller::getMostLongRoute(int _count)
{
	
	std::set<std::pair<time_t, int> ,std::greater<std::pair<time_t, int> > > l_routes;
	
	std::vector<std::string> l_result;

	for (auto & x : m_routes) 
	{
		l_routes.emplace( std::make_pair(x.second->getRouteDuration(), x.second->getRouteNumber() ) );
	}

	for (auto & x : l_routes) 
	{
		static int i = 0;
		
		if (i == _count) break;

		Route * tempRoute = findRoute(x.second);
		l_result.push_back("Route number: " + std::to_string(x.second) + " start station: " + tempRoute->getStartStation().getStationName()+
		" finish station: " + tempRoute->getLastStation().getStationName()+" duration: "+ std::to_string(x.first/3600)+ ':'+std::to_string((x.first % 3600)/60));
		i++;
	}
	return l_result;
}

std::vector< std::pair<std::string, std::string> > Controller::getPairedStations(int _count)
{
	std::vector<std::pair<std::string, std::string>> returnResult;
	std::map< std::pair<std::string, std::string>, int> l_pairedStations;
	
	for (auto && x: m_stations) 
	{
		for (auto && y:m_stations) 
		{
			if (x.second->getStationName() != y.second->getStationName()&&
				l_pairedStations.find( std::make_pair( y.second->getStationName() , x.second->getStationName() ) ) == l_pairedStations.end())
			{
				l_pairedStations.emplace(std::make_pair(x.second->getStationName(), y.second->getStationName()), 0);
			}
		}
	}

	for (auto && x: l_pairedStations ) 
	{
		for (auto && y : m_routes )
		{
			if (y.second->hasStation(x.first.first) && y.second->hasStation(x.first.second)) 
			{
				l_pairedStations[std::make_pair(x.first.first, x.first.second)] ++;
			}
		}
	}
	
	std::multimap<  int, std::pair<std::string, std::string> , std::greater<> > l_countToPairedStations;

	for (auto && x: l_pairedStations) 
	{
		if (x.second > 2)
			l_countToPairedStations.emplace(x.second, x.first);
	}

	for (auto && x : l_countToPairedStations) 
	{
		static int i = 0;

		if (i == _count) break;
		
		returnResult.push_back(x.second);
		
		i++;
	}
	return returnResult;
}

std::set<std::string> Controller::getUnusedStations(void)
{
	std::set<std::string> returnResult;
	std::set<std::string> deprecatedStations;

	for (auto && x : m_stations) 
	{
		for (auto && y : m_routes) 
		{
			if (!y.second->hasStation(x.second->getStationName())) 
			{
				returnResult.emplace(x.second->getStationName());
			}
			else 
			{
				deprecatedStations.insert(x.second->getStationName());
			}
		}
	}
	for (auto && x : deprecatedStations) 
	{
		if (returnResult.find(x) != returnResult.end()) 
		{
			returnResult.erase(x);
		}
	}
	return returnResult;
}

std::set<std::string> Controller::getStationsWithNotEnoughtPerons(void)
{
	std::set<std::string> returnValue;
	
	std::vector<std::pair<Date, Date>> l_stationToBusyPeriod;

	for (auto && x : m_stations)
	{

		for (auto && y : m_routes)
		{
			if (y.second->hasStation(x.second->getStationName()))
			{
				y.second->forEachScheduleItem(
					[&x, &l_stationToBusyPeriod](TrainScheduleItem const & _item)
				{
					if (_item.getStationName() == x.second->getStationName())
					{
						l_stationToBusyPeriod.push_back(std::make_pair(_item.getArrivalTime(), _item.getDepartureTime()));
					}
				}
				);
			}
		}

		int l_timeOverlaps = 0;
		
		for (int i = 0; i < l_stationToBusyPeriod.size(); i++) 
		{
			for (int j = 0; j < l_stationToBusyPeriod.size(); j++) 
			{
				if (i == j) continue;
		
				if (l_stationToBusyPeriod[i].first <= l_stationToBusyPeriod[j].second && 
					l_stationToBusyPeriod[i].second >= l_stationToBusyPeriod[j].first) 
				{
					l_timeOverlaps++;
				}
			}
 		}

		if (l_timeOverlaps > x.second->getPerronsCount()) 
		{
			returnValue.insert(x.second->getStationName());
		}
		l_stationToBusyPeriod.clear();
	}

	return returnValue;
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
