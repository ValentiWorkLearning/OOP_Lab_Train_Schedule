#include <iostream>

#include"Station.hpp"
#include "TrainScheduleItem.hpp"
#include "route.hpp"
#include "Train.hpp"

#include"controller.hpp"

int main() 
{
	Controller c;

	c.addStation("Novgorodska", 4);
	
	c.addTrain(1, 34);
	c.addRoute(127);
	c.addRouteToTrain(127, 1);

	//std::unique_ptr<TrainScheduleItem> t1( new TrainScheduleItem (Novgorodkska, Date(), Date() ) );
	//std::unique_ptr<TrainScheduleItem> t2(new TrainScheduleItem(Kh, Date(), Date()));


	//c.setRoute();
	return 0;
}