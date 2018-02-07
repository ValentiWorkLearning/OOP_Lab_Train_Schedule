#include "controller.hpp"

#include "Station.hpp"
#include "Train.hpp"
#include "TrainScheduleItem.hpp"
#include "route.hpp"

Station &  Controller::addStation(std::string const & _stationName, int _nPerons)
{
    if (hasStation(_stationName)) 
    {
        throw std::logic_error(Messages::DuplicateStation);
    }
    Station & rS = *m_stations.insert({ _stationName,  std::make_unique<Station>(_stationName,_nPerons) }).first->second.get() ;
    return rS;
}

Train & Controller::addTrain(int _uniqueNumber,int _nPassagersCount)
{
	if (hasTrain(_uniqueNumber))
	{
        throw std::logic_error(Messages::DuplicateTrain);
	}

    Train & rTr= *m_trains.insert({ _uniqueNumber, std::make_unique<Train>(_uniqueNumber, _nPassagersCount) }).first->second.get();
    return rTr;
}

Route &  Controller::addRoute(int _uniqueNumber)
{
	if (hasRoute(_uniqueNumber)) 
	{
        throw std::logic_error(Messages::DuplicateRoute);
	}
     Route &  rRt = *m_routes.insert({ _uniqueNumber,  std::make_unique<Route>(_uniqueNumber) }).first->second.get();
    return rRt;
}

bool Controller::hasStation(std::string const & _stationName)
{
	return m_stations.find(_stationName) != m_stations.end();
}

bool Controller::hasTrain(int _trainNumber)
{
	return m_trains.find(_trainNumber) != m_trains.end();
}

bool Controller::hasRoute(int _routeNumber)
{
	return m_routes.find(_routeNumber) != m_routes.end();
}

void Controller::removeStation(std::string const & _stationName)
{
	m_stations.erase(_stationName);
}

void Controller::removeTrain(int _trainNumber)
{
	m_trains.erase(_trainNumber);
}

void Controller::removeRoute(int _routeNumber)
{
	m_routes.erase(_routeNumber);
}


std::vector<std::pair<Station const *, int >> 
Controller::getMostPopularStations(int  _counter)
{

    std::vector<std::pair<Station const *, int >> returnResult;
    std::map< Station const * , int > stationCounter;
    
    for (auto & x : m_routes) 
    {
        x.second->forEachScheduleItem( [ &stationCounter ](auto & _item) 
        {
            stationCounter[ &_item.getStation()] ++;
        } );
    }

    std::vector< std::pair < Station const *, int> > sortedStations{ stationCounter.begin(), stationCounter.end() };

    std::sort(sortedStations.begin(), sortedStations.end(), [&](auto _p1, auto _p2)->bool
    {
        if (_p1.second == _p2.second) return _p1.first->getStationName() < _p2.first->getStationName();
        return _p1.second > _p2.second;
    }
    );

    for (auto & x : sortedStations) 
    {
    	if (returnResult.size() == _counter) break;
        returnResult.push_back({ x.first,x.second });
    }
   return returnResult;
}

std::multimap < Date, Route *, std::greater<Date> >
Controller::getMostLongRoute(int _count)
{
    std::multimap < Date, Route *, std::greater<Date> > l_routes;
	for (auto & x : m_routes) 
	{   
        if (l_routes.size() == _count) break;
        l_routes.insert({ Date(x.second->getRouteDuration() ) , x.second.get() });
	}

	return l_routes;
}

std::set<std::pair<Station const *, Station const *>>  Controller::getPairedStations(int _count)
{
    std::set<std::pair<Station const *, Station const *>> l_returnResult;
    std::map <std::pair<Station const *, Station const * >, int > l_pairedStations;

    for (auto & x : m_stations) 
    {
        if (l_returnResult.size() == _count) break;
        for (auto & y : m_stations) 
        {
            for (auto & z : m_routes) 
            {
    
                if (z.second->hasStation(*x.second) && z.second->hasStation(*y.second) && x.second->getStationName() != y.second->getStationName())
                {
                    if (l_pairedStations.find({ y.second.get(), x.second.get() }) == l_pairedStations.end())
                    {
                        l_pairedStations[{x.second.get(), y.second.get()}] ++;                      
                        if (l_pairedStations[{x.second.get(), y.second.get()}] > 2)
                        {
                            l_returnResult.insert({ x.second.get(),y.second.get() });
                        }
                    }                  
                }
            }
        }
    }
	return l_returnResult;
}

std::set<Station const *> Controller::getUnusedStations(void)
{
	std::set<Station const *> returnResult;
	std::set<Station const *> deprecatedStations;

	for (auto & x : m_stations) 
	{
		for (auto & y : m_routes) 
		{
			if (!y.second->hasStation(*x.second)) 
			{
				returnResult.emplace(x.second.get());
			}
			else 
			{
				deprecatedStations.insert(x.second.get());
			}
		}
	}
	for (auto & x : deprecatedStations) 
	{
		returnResult.erase(x);
	}
	return returnResult;
}

std::set<Station const *> Controller::getStationsWithNotEnoughtPerons()
{
	std::set<Station const *> returnValue;
	
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
		Station * l_currentStation = x.second.get();

		int l_platformsAvaliable{x.second->getPerronsCount()};
	
		for (auto & y : m_routes)
		{
			if (y.second->hasStation(*x.second))
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
