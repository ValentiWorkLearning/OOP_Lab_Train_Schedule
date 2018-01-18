#include "controller.hpp"

#include "Station.hpp"
#include "Train.hpp"
#include "TrainScheduleItem.hpp"
#include "route.hpp"

Station &  Controller::addStation(std::string const & _stationName, int _nPerons)
{ 
	m_stations.insert({ _stationName, std::make_unique<Station>(_stationName, _nPerons) });

    return findStation(_stationName);
}

Train & Controller::addTrain(int _uniqueNumber,int _nPassagersCount)
{
	if (hasTrain(_uniqueNumber))
	{
        throw std::logic_error(Messages::DuplicateTrain);
	}

    m_trains.insert({ _uniqueNumber, std::make_unique<Train>(_uniqueNumber, _nPassagersCount) });
    return findTrain(_uniqueNumber);
}

Route &  Controller::addRoute(int _uniqueNumber)
{
	if (hasRoute(_uniqueNumber)) 
	{
        throw std::logic_error(Messages::DuplicateRoute);
	}
    m_routes.insert({ _uniqueNumber,  std::make_unique<Route>(_uniqueNumber) });

    return findRoute(_uniqueNumber);
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
	m_trains.erase(findTrain(_trainNumber).getTrainNumber());
}

void Controller::removeRoute(int _routeNumber)
{
	m_routes.erase(findRoute(_routeNumber).getRouteNumber());
}

std::vector<std::string> Controller::getMostPopularStations(int  _counter)
{

    std::vector<std::string> returnResult;
    std::map< Station const * , int > stationCounter;
    
    for (auto & x : m_routes) 
    {
        x.second->forEachScheduleItem( [ &stationCounter ](auto & _item) 
        {
            stationCounter[ &_item.getStation()] ++;
        } );
    }

    std::vector< std::pair < Station const *, int> > sortedStations{ stationCounter.begin(), stationCounter.end() };

    std::sort(sortedStations.begin(), sortedStations.end(), [&](auto _p1, auto _p2) ->bool
    {
        if (_p1.second == _p2.second) return _p1.first->getStationName() < _p2.first->getStationName();
        return _p1.second > _p2.second;
    }
    );

    for (auto & x : sortedStations) 
    {
    	if (returnResult.size() == _counter) break;
    	returnResult.push_back(x.first->getStationName() + ":" + std::to_string(x.second));
    }
   return returnResult;
}

std::vector<std::string> Controller::getMostLongRoute(int _count)
{	
    std::multimap < time_t, Route *, std::greater<time_t> > l_routes;
	std::vector<std::string> l_result;

	for (auto & x : m_routes) 
	{
        l_routes.insert({ x.second->getRouteDuration() , x.second.get() });
	}

	for (auto & x : l_routes) 
	{
        if (l_routes.size() == _count) break;

		l_result.push_back("Route number: " + std::to_string(x.second->getRouteNumber()) + " start station: " + findRoute(x.second->getRouteNumber()).getStartStation().getStationName()+
		" finish station: " + findRoute(x.second->getRouteNumber()).getLastStation().getStationName()+" duration: "+ std::to_string(x.first/3600)+ ':'+std::to_string((x.first % 3600)/60));
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
		if (returnResult.size() == _count) break;
		
		returnResult.push_back(x.second);		
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

std::set<std::string> Controller::getStationsWithNotEnoughtPerons()
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
					[&x, &l_stationsEvents](auto & _item)
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


Train & Controller::findTrain(int _uniqueNumber)const 
{
	auto it = m_trains.find(_uniqueNumber);
	if (it == m_trains.end()) 
	{
		throw std::logic_error(Messages::TrainDoesNotExist);
	}
	return *it->second;
}

Route & Controller::findRoute(int _uniqueNumber)const 
{

	auto it = m_routes.find(_uniqueNumber);
	if (it == m_routes.end())
	{
		throw std::logic_error(Messages::RouteDoesNotExist);
	}
	return *it->second;
}

Station & Controller::findStation(std::string const & _stationName) const 
{
	auto it = m_stations.find(_stationName);
	if (it == m_stations.end())
	{
		throw std::logic_error(Messages::StationDoesNotExist);
	}
	return *it->second;
}
