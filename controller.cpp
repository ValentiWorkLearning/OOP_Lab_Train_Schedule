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

bool Controller::hasStation(std::string const & _stationName)
{
	return (m_stations.find(_stationName) == m_stations.end())?false:true;
}

bool Controller::hasTrain(int _trainNumber)
{
	return (m_trains.find(_trainNumber) == m_trains.end())? false:true;
}

bool Controller::hasRoute(int _routeNumber)
{
	return (m_routes.find(_routeNumber) == m_routes.end())?false:true;
}

void Controller::removeStation(std::string const & _stationName)
{
	m_stations.erase(findStation(_stationName).getStationName());
}

void Controller::removeTrain(int _trainNumber)
{
	m_trains.erase(findTrain(_trainNumber)->getTrainNumber());
}

void Controller::removeRoute(int _routeNumber)
{
	m_routes.erase(findRoute(_routeNumber)->getRouteNumber());
}

std::vector<std::string> Controller::getMostPopularStations(int  _counter)
{
	std::vector<std::string > returnResult;

	std::map<std::string, int> stationCounter;
	
	for (auto & x : m_stations) 
	{
		stationCounter.insert({ x.second->getStationName(), 0 });
	}

	for (auto & x : m_routes) 
	{
		for (auto & y : m_stations)
		{
			if (x.second->hasStation(y.second->getStationName())) 
			{
				stationCounter[y.second->getStationName()]++;
			}
		}
	}

	std::multimap<int, std::string,std::greater<int>> greaterStation; 
	
	for (auto &x : stationCounter) 
	{
		greaterStation.emplace(x.second, x.first);
	}

	for (auto & x : greaterStation) 
	{
		static int i = 0;
		if (i == _counter) break;
		returnResult.push_back(x.second + ":" + std::to_string(x.first));
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
	
	for (auto & x: m_stations) 
	{
		for (auto & y:m_stations) 
		{
			if (x.second->getStationName() != y.second->getStationName()&&
				l_pairedStations.find( std::make_pair( y.second->getStationName() , x.second->getStationName() ) ) == l_pairedStations.end())
			{
				l_pairedStations.emplace(std::make_pair(x.second->getStationName(), y.second->getStationName()), 0);
			}
		}
	}

	for (auto & x: l_pairedStations ) 
	{
		for (auto & y : m_routes )
		{
			if (y.second->hasStation(x.first.first) && y.second->hasStation(x.first.second)) 
			{
				l_pairedStations[std::make_pair(x.first.first, x.first.second)] ++;
			}
		}
	}
	
	std::multimap<  int, std::pair<std::string, std::string> , std::greater<> > l_countToPairedStations;

	for (auto & x: l_pairedStations) 
	{
		if (x.second > 2)
			l_countToPairedStations.emplace(x.second, x.first);
	}

	for (auto & x : l_countToPairedStations) 
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

	for (auto & x : m_stations) 
	{
		for (auto & y : m_routes) 
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
	for (auto & x : deprecatedStations) 
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
	
	struct StationEvent 
	{
		enum class Event : bool { Arrive, Departure };
		Date m_date;
		Event m_event;

		StationEvent(Date const & _date, Event _event) :m_date(_date), m_event(_event) {};
	};

	for (auto & x : m_stations)
	{
		std::vector <StationEvent> l_stationsEvents{};
		std::string l_currentStation{ x.second->getStationName() };

		int l_platformsAvaliable{x.second->getPerronsCount()};
	
		for (auto & y : m_routes)
		{
			if (y.second->hasStation(x.second->getStationName()))
			{
				y.second->forEachScheduleItem(
					[&x, &l_stationsEvents](TrainScheduleItem const & _item)
				{
					if (_item.getStationName() == x.second->getStationName())
					{
						l_stationsEvents.push_back(StationEvent(_item.getArrivalTime(), StationEvent::Event::Arrive));
						l_stationsEvents.push_back(StationEvent(_item.getDepartureTime(), StationEvent::Event::Departure));
					}
				}
				);
			}
		}
		std::sort(l_stationsEvents.begin(), l_stationsEvents.end(), [](StationEvent & _st1, StationEvent & _st2)
		{
			return _st1.m_date < _st2.m_date;
		});

		for (auto x : l_stationsEvents) 
		{
			static int  l_platformsUsed{};

			(x.m_event == StationEvent::Event::Arrive) ? ++l_platformsUsed : --l_platformsUsed;

			if (l_platformsUsed > l_platformsAvaliable) 
			{
				returnValue.insert(l_currentStation);
			}
		}
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
