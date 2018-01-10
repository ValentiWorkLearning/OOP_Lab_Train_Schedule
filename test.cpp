// (C) 205633-205636, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

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
DECLARE_OOP_TEST(test_invalid_parameters) 
{
	Controller c;

	//Invalid parameters to create train
	ASSERT_THROWS(c.addTrain(-1, 1),Messages::InvalidTrainNumber);
	ASSERT_THROWS(c.addTrain(1, -1), Messages::InvalidPasegersCount);
	
	//Invalid parameters to create route
	ASSERT_THROWS(c.addRoute(-1), Messages::BadRouteNumber);
	
	//Invalid parameters to create station
	ASSERT_THROWS(c.addStation("", 1), Messages::StationNameEmpty);
	ASSERT_THROWS(c.addStation("Malinovka", 0),Messages::InvalidPeronsCount);
	ASSERT_THROWS(c.addStation("Malinovka", -1), Messages::InvalidPeronsCount);

	//Invalid parameters to create schedule item
	c.addRoute(1);
	c.addStation("Malinovka", 1);
	ASSERT_THROWS(c.addScheduleItemToRoute(1, "Malinovka", Date("2017/11/08/11:59"), Date("2017/11/08/11:00")), Messages::InvalidTimeSended);

}

DECLARE_OOP_TEST(test_add_and_delete_few_stations) 
{
	Controller c;
	c.addStation("Malinovka",1);
	c.addStation("Maslyanivka",1);
	
	assert(c.hasStation("Malinovka"));
	assert(c.hasStation("Maslyanivka"));

	c.removeStation("Malinovka");
	assert(!c.hasStation("Malinovka"));
}

DECLARE_OOP_TEST(test_add_and_delete_few_trains)
{
	Controller c;
	c.addTrain(232, 563);
	c.addTrain(724, 563);

	assert(c.hasTrain(232));
	assert(c.hasTrain(724));

	c.removeTrain(232);
	assert(!c.hasTrain(232));
}

DECLARE_OOP_TEST(test_add_and_delete_few_routes)
{
	Controller c;
	c.addRoute(232);
	c.addRoute(724);

	assert(c.hasRoute(232));
	assert(c.hasRoute(724));

	c.removeRoute(232);
	assert(!c.hasRoute(232));
}

DECLARE_OOP_TEST(test_most_long_route)
{

	Controller c;
	createCommonConfiguration(c);
	std::vector<std::string> receivedResult  = c.getMostLongRoute(5);
}

DECLARE_OOP_TEST(test_stations_with_not_enough_perons_1)
{
	Controller c;
	createOverlapConfiguration(c);

	std::set<std::string> expectedResult{ "Novgorodska" , "Lviv" };

	std::set<std::string> receivedResult = c.getStationsWithNotEnoughtPerons();

	assert(expectedResult == receivedResult);
}

DECLARE_OOP_TEST(test_stations_with_not_enough_perons_2) 
{
	Controller c;

	c.addStation("Novgorodska", 10);

	for (int i = 0; i < 10; i++) 
	{
		c.addRoute( i+ 127);
		c.addTrain(i, 860);
		c.addScheduleItemToRoute(i+127, "Novgorodska", Date("2018/11/08/11:45"), Date("2018/11/08/12:45"));
		c.addRouteToTrain(i + 127, i);
	}
	c.addRoute(450);
	c.addTrain(120, 123);
	c.addScheduleItemToRoute(450, "Novgorodska", Date("2018/11/08/12:20"), Date("2018/11/08/12:45"));
	c.addRouteToTrain(450,120);

	std::set<std::string> expectedResult = {"Novgorodska"};

	assert(expectedResult == c.getStationsWithNotEnoughtPerons());
}

DECLARE_OOP_TEST(test_most_popular_station) 
{
	Controller c;

	createCommonConfiguration(c);

	std::vector<std::string> expectedValue{ "Kharkiv:4","Kremenchug:4", "Lviv:4","Poltava:3","Kiev:2" };

	assert(expectedValue == c.getMostPopularStations(5));
}

DECLARE_OOP_TEST(test_paired_stations) 
{
	Controller c;
	createCommonConfiguration(c);

	std::vector< std::pair<std::string, std::string> > expectedValue{ 
		{"Kharkiv","Kremenchug"},
		{"Kharkiv","Lviv"},
		{"Kremenchug","Lviv"},
		{"Kharkiv","Poltava"},
		{"Kremenchug","Poltava"} 
	};
	
	assert(expectedValue == c.getPairedStations(5));
}
DECLARE_OOP_TEST(test_unused_stations) 
{
	Controller c;
	createCommonConfiguration(c);

	//add unused stations
	c.addStation("Kirovka", 1);
	c.addStation("Golovnevka", 2);
	c.addStation("Kirilenska", 4);
	c.addStation("Malinovka", 1);

	std::set<std::string> expectedResult = { "Golovnevka","Kirilenska","Kirovka","Malinovka" };
		
	assert(expectedResult == c.getUnusedStations());
}
/*****************************************************************************/

