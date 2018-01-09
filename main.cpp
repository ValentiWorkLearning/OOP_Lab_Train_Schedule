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
	c.addStation("Kiev", 10);
	c.addStation("Kharkiv", 10);
	c.addStation("Kremenchug", 7);
	c.addStation("Ternopil", 4);
	c.addStation("Volchansk", 1);

	//add unused stations
	c.addStation("Kirovka", 1);
	c.addStation("Golovnevka", 2);
	c.addStation("Kirilenska", 4);
	c.addStation("Malinovka", 1);
	//
	c.addTrain(1, 860);
	c.addTrain(2, 720);
	c.addTrain(3, 450);
	c.addTrain(4, 450);

	c.addRoute(127);
	c.addRoute(128);
	c.addRoute(129);
	c.addRoute(726);

	c.addRouteToTrain(127, 1);
	c.addRouteToTrain(128, 2);
	c.addRouteToTrain(129, 3);
	c.addRouteToTrain(726, 4);

	c.addScheduleItemToRoute(127, "Novgorodska", Date("2018/11/08/11:45"), Date("2018/11/08/12:45" ) );
	c.addScheduleItemToRoute(127, "Poltava", Date("2018/11/08/12:55"), Date("2018/11/08/13:55" ) );
	c.addScheduleItemToRoute(127, "Lviv", Date("2018/11/08/15:45"), Date("2018/11/08/17:45"));
	c.addScheduleItemToRoute(127, "Kiev", Date("2018/11/08/17:55"), Date("2018/11/08/18:00"));
	c.addScheduleItemToRoute(127, "Kharkiv", Date("2018/11/08/18:55"), Date("2018/11/08/18:56"));
	c.addScheduleItemToRoute(127, "Kremenchug", Date("2018/11/08/19:00"), Date("2018/11/08/19:05"));
	c.addScheduleItemToRoute(127, "Ternopil", Date("2018/11/08/20:45"), Date("2018/11/08/20:55"));
	c.addScheduleItemToRoute(127, "Volchansk", Date("2018/11/08/22:45"), Date("2018/11/08/23:55"));

	c.addScheduleItemToRoute(128, "Kharkiv", Date("2018/11/08/17:55"), Date("2018/11/08/18:00"));
	c.addScheduleItemToRoute(128, "Kremenchug", Date("2018/11/08/19:00"), Date("2018/11/08/19:05"));
	c.addScheduleItemToRoute(128, "Ternopil", Date("2018/11/08/20:45"), Date("2018/11/08/20:55"));
	c.addScheduleItemToRoute(128, "Kiev", Date("2018/11/08/21:55"), Date("2018/11/08/22:30"));
	c.addScheduleItemToRoute(128, "Lviv", Date("2018/11/08/22:55"), Date("2018/11/08/22:56"));
	c.addScheduleItemToRoute(128, "Volchansk", Date("2018/11/08/22:57"), Date("2018/11/08/23:55"));

	c.addScheduleItemToRoute(129, "Lviv", Date("2018/11/08/15:45"), Date("2018/11/08/17:45"));
	c.addScheduleItemToRoute(129, "Poltava", Date("2018/11/08/18:55"), Date("2018/11/08/19:55"));
	c.addScheduleItemToRoute(129, "Kremenchug", Date("2018/11/08/20:00"), Date("2018/11/08/20:15"));
	c.addScheduleItemToRoute(129, "Kharkiv", Date("2018/11/08/22:55"), Date("2018/11/08/22:56"));

	c.addScheduleItemToRoute(726, "Lviv", Date("2018/11/08/15:45"), Date("2018/11/08/17:45"));
	c.addScheduleItemToRoute(726, "Poltava", Date("2018/11/08/18:55"), Date("2018/11/08/19:55"));
	c.addScheduleItemToRoute(726, "Kremenchug", Date("2018/11/08/20:00"), Date("2018/11/08/20:15"));
	c.addScheduleItemToRoute(726, "Kharkiv", Date("2018/11/08/22:55"), Date("2018/11/08/22:56"));
	c.addScheduleItemToRoute(726, "Malinovka", Date("2018/11/08/23:23"), Date("2018/11/08/23:58"));
	std::vector<std::string> expectedValue = c.getMostPopularStations(5);

	std::vector< std::pair<std::string, std::string> > expectedValue1 = c.getPairedStations(5);

	std::set<std::string> expectedResult = c.getUnusedStations();
	return 0;
}