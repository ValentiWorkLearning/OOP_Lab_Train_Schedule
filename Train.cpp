#include "Train.hpp"
#include "Messages.hpp"
#include "Route.hpp"

#include <string>

Train::Train(int _nTrainNumber ,int _nPassagers): m_passagersPlaces(_nPassagers), m_trainNumber(_nTrainNumber)
{
	if (m_trainNumber < 0)
		throw std::logic_error(Messages::InvalidTrainNumber);

	if (m_passagersPlaces < 0)
		throw std::logic_error(Messages::InvalidPasegersCount);
}

int Train::getTrainNumber()
{
	return m_trainNumber;
}

int Train::getPassagersCount()
{
	return m_passagersPlaces;
}

Route const * Train::getRoute() const 
{
	return m_route;
}

void Train::setRoute(Route const * _route)
{
	if (m_route != nullptr)
	{
		m_route = _route;
	}
	else throw std::logic_error(Messages::RouteAlreadySet);
}

void Train::unsetRoute()
{
	m_route = nullptr;
}
