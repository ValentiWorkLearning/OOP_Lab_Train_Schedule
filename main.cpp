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
	c.addTrain(2, 34);
	c.addTrain(3, 34);

	c.addRoute(127);
	c.addRoute(128);
	c.addRoute(129);

	c.addRouteToTrain(127, 1);
	c.addRouteToTrain(128, 2);
	c.addRouteToTrain(129, 3);

	c.addScheduleItemToRoute(127, "Novgorodska", Date("2018/11/08/11:45"), Date("2018/11/08/12:45" ) );
	c.addScheduleItemToRoute(127, "Poltava", Date("2018/11/08/12:55"), Date("2018/11/08/13:55" ) );
	c.addScheduleItemToRoute(127, "Lviv", Date("2018/11/08/15:45"), Date("2018/11/08/17:45"));


	c.addScheduleItemToRoute(128, "Poltava", Date("2018/11/08/12:55"), Date("2018/11/08/13:55"));
	c.addScheduleItemToRoute(128, "Lviv", Date("2018/11/08/15:45"), Date("2018/11/08/17:45"));

	c.addScheduleItemToRoute(129, "Lviv", Date("2018/11/08/15:45"), Date("2018/11/08/17:45"));
	c.addScheduleItemToRoute(129, "Poltava", Date("2018/11/08/18:55"), Date("2018/11/08/19:55"));

	std::vector<std::string> expectedValue = c.getMostPopularStations(5);
	return 0;
}