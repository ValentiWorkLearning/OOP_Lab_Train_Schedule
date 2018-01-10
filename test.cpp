// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

/*****************************************************************************/


#include "messages.hpp"

#include"Station.hpp"
#include "TrainScheduleItem.hpp"
#include "route.hpp"
#include "Train.hpp"

#include"controller.hpp"

#include "testslib.hpp"

/*****************************************************************************/

void createCommonConfiguration(Controller & _c) 
{
	_c.addStation("Novgorodska", 4);
	_c.addStation("Poltava", 5);
	_c.addStation("Lviv", 10);
	_c.addStation("Kiev", 10);
	_c.addStation("Kharkiv", 10);
	_c.addStation("Kremenchug", 7);
	_c.addStation("Ternopil", 4);
	_c.addStation("Volchansk", 1);

	//add unused stations
	_c.addStation("Kirovka", 1);
	_c.addStation("Golovnevka", 2);
	_c.addStation("Kirilenska", 4);
	_c.addStation("Malinovka", 1);
	//
	_c.addTrain(1, 860);
	_c.addTrain(2, 720);
	_c.addTrain(3, 450);
	_c.addTrain(4, 450);

	_c.addRoute(127);
	_c.addRoute(128);
	_c.addRoute(129);
	_c.addRoute(726);

	_c.addRouteToTrain(127, 1);
	_c.addRouteToTrain(128, 2);
	_c.addRouteToTrain(129, 3);
	_c.addRouteToTrain(726, 4);

	_c.addScheduleItemToRoute(127, "Novgorodska", Date("2018/11/08/11:45"), Date("2018/11/08/12:45"));
	_c.addScheduleItemToRoute(127, "Poltava", Date("2018/11/08/12:55"), Date("2018/11/08/13:55"));
	_c.addScheduleItemToRoute(127, "Lviv", Date("2018/11/08/15:45"), Date("2018/11/08/17:45"));
	_c.addScheduleItemToRoute(127, "Kiev", Date("2018/11/08/17:55"), Date("2018/11/08/18:00"));
	_c.addScheduleItemToRoute(127, "Kharkiv", Date("2018/11/08/18:55"), Date("2018/11/08/18:56"));
	_c.addScheduleItemToRoute(127, "Kremenchug", Date("2018/11/08/19:00"), Date("2018/11/08/19:05"));
	_c.addScheduleItemToRoute(127, "Ternopil", Date("2018/11/08/20:45"), Date("2018/11/08/20:55"));
	_c.addScheduleItemToRoute(127, "Volchansk", Date("2018/11/08/22:45"), Date("2018/11/08/23:55"));

	_c.addScheduleItemToRoute(128, "Kharkiv", Date("2018/11/08/17:55"), Date("2018/11/08/18:00"));
	_c.addScheduleItemToRoute(128, "Kremenchug", Date("2018/11/08/19:00"), Date("2018/11/08/19:05"));
	_c.addScheduleItemToRoute(128, "Ternopil", Date("2018/11/08/20:45"), Date("2018/11/08/20:55"));
	_c.addScheduleItemToRoute(128, "Kiev", Date("2018/11/08/21:55"), Date("2018/11/08/22:30"));
	_c.addScheduleItemToRoute(128, "Lviv", Date("2018/11/08/22:55"), Date("2018/11/08/22:56"));
	_c.addScheduleItemToRoute(128, "Volchansk", Date("2018/11/08/22:57"), Date("2018/11/08/23:55"));

	_c.addScheduleItemToRoute(129, "Lviv", Date("2018/11/08/15:45"), Date("2018/11/08/17:45"));
	_c.addScheduleItemToRoute(129, "Poltava", Date("2018/11/08/18:55"), Date("2018/11/08/19:55"));
	_c.addScheduleItemToRoute(129, "Kremenchug", Date("2018/11/08/20:00"), Date("2018/11/08/20:15"));
	_c.addScheduleItemToRoute(129, "Kharkiv", Date("2018/11/08/22:55"), Date("2018/11/08/22:56"));

	_c.addScheduleItemToRoute(726, "Lviv", Date("2018/11/08/15:45"), Date("2018/11/08/17:45"));
	_c.addScheduleItemToRoute(726, "Poltava", Date("2018/11/08/18:55"), Date("2018/11/08/19:55"));
	_c.addScheduleItemToRoute(726, "Kremenchug", Date("2018/11/08/20:00"), Date("2018/11/08/20:15"));
	_c.addScheduleItemToRoute(726, "Kharkiv", Date("2018/11/08/22:55"), Date("2018/11/08/22:56"));
	_c.addScheduleItemToRoute(726, "Malinovka", Date("2018/11/08/23:23"), Date("2018/11/08/23:58"));
	std::vector<std::string> expectedValue = _c.getMostPopularStations(5);

	std::vector< std::pair<std::string, std::string> > expectedValue1 = _c.getPairedStations(5);

	std::set<std::string> expectedResult = _c.getUnusedStations();
}


void createOverlapConfiguration(Controller &_c) 
{
	_c.addStation("Novgorodska", 1);
	_c.addStation("Poltava", 2);
	_c.addStation("Lviv", 1);
	_c.addStation("Kiev", 1);
	_c.addStation("Kharkiv", 1);
	
	_c.addRoute(127);
	_c.addRoute(128);
	_c.addRoute(129);
	_c.addRoute(726);

	_c.addTrain(1, 860);
	_c.addTrain(2, 720);
	_c.addTrain(3, 450);

	_c.addScheduleItemToRoute(127, "Novgorodska", Date("2018/11/08/11:45"), Date("2018/11/08/12:45"));
	_c.addScheduleItemToRoute(128, "Novgorodska", Date("2018/11/08/11:45"), Date("2018/11/08/12:45"));

	_c.addScheduleItemToRoute(127, "Kharkiv", Date("2018/11/08/18:55"), Date("2018/11/08/18:56"));
	_c.addScheduleItemToRoute(128, "Kharkiv", Date("2018/11/08/17:55"), Date("2018/11/08/18:00"));
	_c.addScheduleItemToRoute(129, "Kharkiv", Date("2018/11/08/22:55"), Date("2018/11/08/22:56"));

	_c.addScheduleItemToRoute(127, "Kiev", Date("2018/11/08/19:55"), Date("2018/11/08/20:00"));
	_c.addScheduleItemToRoute(128, "Kiev", Date("2018/11/08/21:55"), Date("2018/11/08/22:30"));
	_c.addScheduleItemToRoute(129, "Kiev", Date("2018/11/08/23:55"), Date("2018/11/09/12:30"));

	_c.addScheduleItemToRoute(127, "Poltava", Date("2018/11/08/21:55"), Date("2018/11/08/22:00"));

	_c.addScheduleItemToRoute(127, "Lviv", Date("2018/11/08/22:35"), Date("2018/11/08/22:40"));
	_c.addScheduleItemToRoute(128, "Lviv", Date("2018/11/08/22:37"), Date("2018/11/08/22:38"));
	
	
	


}
/*****************************************************************************/


DECLARE_OOP_TEST(test_common_configuration)
{

	Controller c;

	
}

DECLARE_OOP_TEST(test_lyamda_simple) 
{
	Route r{ 127 };
	Station s{ "Malinovka",23 };
	Station s1{ "Kostyanivka",23 };
	r.addScheduleItem(std::make_unique <TrainScheduleItem>(s, Date("2018/11/08/22:23"), Date("2018/11/08/22:58")));
	r.addScheduleItem(std::make_unique <TrainScheduleItem>(s1, Date("2018/11/08/23:23"), Date("2018/11/08/23:58")));

	r.forEachScheduleItem(
		[](TrainScheduleItem const & _trainItem)
	{
		std::cout << _trainItem.getStationName() << std::endl;
	}
	);
}

DECLARE_OOP_TEST(test_stations_with_not_enough_perons)
{
	Controller c;
	createOverlapConfiguration(c);

	std::set<std::string> expectedResult{ "Novgorodska" , "Lviv" };

	std::set<std::string> receivedResult = c.getStationsWithNotEnoughtPerons();

	assert(expectedResult == receivedResult);
}
/*****************************************************************************/

