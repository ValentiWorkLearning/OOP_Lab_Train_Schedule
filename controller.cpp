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
