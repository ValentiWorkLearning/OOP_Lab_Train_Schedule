#ifndef TRAIN_HPP
#define TRAIN_HPP

class Route; 

class Train
{
public:
	Train(int _nTrainNumber, int _nPassagers);
	
	~Train()=default;
	
	Train(const Train&) = delete;

	Train & operator = (const Train &) = delete;

	int getTrainNumber();
	
	int getPassagersCount();

	void setRoute(Route const * _route);

	void unsetRoute();

	Route const * getRoute()const ;
	
	
private:

	int m_trainNumber;
	int m_passagersPlaces;
	
	Route const * m_route;
};


#endif // !TRAIN_HPP

