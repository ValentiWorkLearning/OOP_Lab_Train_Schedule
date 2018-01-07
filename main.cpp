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
	c.addStation("Poltava", 5);
	c.addStation("Lviv", 10);


	c.addTrain(1, 34);
	
	c.addRoute(127);
	
	c.addRouteToTrain(127, 1);

	c.addScheduleItemToRoute(127, "Novgorodska", Date("2018/11/08/11:45"), Date("2018/11/08/12:45" ) );
	c.addScheduleItemToRoute(127, "Poltava", Date("2018/11/08/12:55"), Date("2018/11/08/13:55" ) );

	try 
	{
		c.addScheduleItemToRoute(127, "Poltava", Date("2018/11/08/12:35"), Date("2018/11/08/13:55"));
	}
	catch (std::logic_error _e) 
	{
		std::cout << _e.what();
	}
	return 0;
}