#include "Train.hpp"
#include "Messages.hpp"
#include "Route.hpp"

#include <string>

Train::Train(int _nTrainNumber ,int _nPassagers): m_passagersPlaces(_nPassagers), m_trainNumber(_nTrainNumber),m_route(nullptr)
{
	if (m_trainNumber < 0)
		throw std::logic_error(Messages::InvalidTrainNumber);

	if (m_passagersPlaces < 0)
		throw std::logic_error(Messages::InvalidPasegersCount);
}

int Train::getTrainNumber() const 
{
	return m_trainNumber;
}

int Train::getPassagersCount() const 
{
	return m_passagersPlaces;
}

void Train::setRoute(Route const * _route)
{
    if (m_route != nullptr) 
    {
        throw std::logic_error(Messages::RouteAlreadySet);
    }
	
    m_route = _route;
}

void Train::unsetRoute()
{
	m_route = nullptr;
}

Route const * Train::getRoute() const 
{
	return m_route;
}

