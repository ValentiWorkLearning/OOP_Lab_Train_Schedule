
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
    Station & s1 = _c.addStation("Novgorodska", 4);
    Station & s2 = _c.addStation("Poltava", 5);
    Station & s3 = _c.addStation("Lviv", 10);
    Station & s4 = _c.addStation("Kiev", 10);
    Station & s5 = _c.addStation("Kharkiv", 10);
    Station & s6 = _c.addStation("Kremenchug", 7);
    Station & s7 = _c.addStation("Ternopil", 4);
    Station & s8 = _c.addStation("Volchansk", 1);
	
	Train & t1 = _c.addTrain(1, 860);
    Train & t2 = _c.addTrain(2, 720);
    Train & t3 = _c.addTrain(3, 450);
    Train & t4 = _c.addTrain(4, 450);

	Route & r1 = _c.addRoute(127);
    Route & r2 = _c.addRoute(128);
    Route & r3 = _c.addRoute(129);
    Route & r4 = _c.addRoute(726);

    t1.setRoute(&r1);
    t2.setRoute(&r2);
    t3.setRoute(&r3);
    t4.setRoute(&r4);

	r1.addScheduleItem(TrainScheduleItem(s1, Date("2018/11/08/11:45"), Date("2018/11/08/12:45")));
	r1.addScheduleItem(TrainScheduleItem(s2, Date("2018/11/08/12:55"), Date("2018/11/08/13:55")));
	r1.addScheduleItem(TrainScheduleItem(s3, Date("2018/11/08/15:45"), Date("2018/11/08/17:45")));
	r1.addScheduleItem(TrainScheduleItem(s4, Date("2018/11/08/17:55"), Date("2018/11/08/18:00")));
	r1.addScheduleItem(TrainScheduleItem(s5, Date("2018/11/08/18:55"), Date("2018/11/08/18:56")));
	r1.addScheduleItem(TrainScheduleItem(s6, Date("2018/11/08/19:00"), Date("2018/11/08/19:05")));
	r1.addScheduleItem(TrainScheduleItem(s7, Date("2018/11/08/20:45"), Date("2018/11/08/20:55")));
	r1.addScheduleItem(TrainScheduleItem(s8, Date("2018/11/08/22:45"), Date("2018/11/08/23:55")));

	r2.addScheduleItem(TrainScheduleItem(s5, Date("2018/11/08/17:55"), Date("2018/11/08/18:00")));
	r2.addScheduleItem(TrainScheduleItem(s6, Date("2018/11/08/19:00"), Date("2018/11/08/19:05")));
	r2.addScheduleItem(TrainScheduleItem(s7, Date("2018/11/08/20:45"), Date("2018/11/08/20:55")));
	r2.addScheduleItem(TrainScheduleItem(s4, Date("2018/11/08/21:55"), Date("2018/11/08/22:30")));
	r2.addScheduleItem(TrainScheduleItem(s3, Date("2018/11/08/22:55"), Date("2018/11/08/22:56")));
	r2.addScheduleItem(TrainScheduleItem(s8, Date("2018/11/08/22:57"), Date("2018/11/08/23:55")));

	r3.addScheduleItem(TrainScheduleItem(s3, Date("2018/11/08/15:45"), Date("2018/11/08/17:45")));
	r3.addScheduleItem(TrainScheduleItem(s2, Date("2018/11/08/18:55"), Date("2018/11/08/19:55")));
	r3.addScheduleItem(TrainScheduleItem(s6, Date("2018/11/08/20:00"), Date("2018/11/08/20:15")));
	r3.addScheduleItem(TrainScheduleItem(s5, Date("2018/11/08/22:55"), Date("2018/11/08/22:56")));

	r4.addScheduleItem(TrainScheduleItem(s3, Date("2018/11/08/15:45"), Date("2018/11/08/17:45")));
	r4.addScheduleItem(TrainScheduleItem(s2, Date("2018/11/08/18:55"), Date("2018/11/08/19:55")));
	r4.addScheduleItem(TrainScheduleItem(s6, Date("2018/11/08/20:00"), Date("2018/11/08/20:15")));
	r4.addScheduleItem(TrainScheduleItem(s5, Date("2018/11/08/22:55"), Date("2018/11/08/22:56")));
	
}

void createOverlapConfiguration(Controller &_c) 
{
	Station & s1 = _c.addStation("Novgorodska", 1);
    Station & s2 = _c.addStation("Poltava", 2);
    Station & s3 = _c.addStation("Lviv", 1);
    Station & s4 = _c.addStation("Kiev", 1);
    Station & s5 = _c.addStation("Kharkiv", 1);
	
	Route& r1 = _c.addRoute(127);
    Route& r2 = _c.addRoute(128);
    Route& r3 = _c.addRoute(129);
    Route& r4 = _c.addRoute(726);

	Train & t1 = _c.addTrain(1, 860);
    Train & t2 = _c.addTrain(2, 720);
    Train & t3 = _c.addTrain(3, 450);

    r1.addScheduleItem(TrainScheduleItem(s1, Date("2018/11/08/11:45"), Date("2018/11/08/12:45")));
    r2.addScheduleItem(TrainScheduleItem(s1, Date("2018/11/08/11:45"), Date("2018/11/08/12:45")));

    r1.addScheduleItem(TrainScheduleItem(s5, Date("2018/11/08/18:55"), Date("2018/11/08/18:56")));
    r2.addScheduleItem(TrainScheduleItem(s5, Date("2018/11/08/17:55"), Date("2018/11/08/18:00")));
    r3.addScheduleItem(TrainScheduleItem(s5, Date("2018/11/08/22:55"), Date("2018/11/08/22:56")));


    r1.addScheduleItem(TrainScheduleItem(s4, Date("2018/11/08/19:55"), Date("2018/11/08/20:00")));
    r2.addScheduleItem(TrainScheduleItem(s4, Date("2018/11/08/21:55"), Date("2018/11/08/22:30")));
    r3.addScheduleItem(TrainScheduleItem(s4, Date("2018/11/08/23:55"), Date("2018/11/09/12:30")));

    r1.addScheduleItem(TrainScheduleItem(s2, Date("2018/11/08/21:55"), Date("2018/11/08/22:00")));
    r1.addScheduleItem(TrainScheduleItem(s3, Date("2018/11/08/22:35"), Date("2018/11/08/22:40")));
    r2.addScheduleItem(TrainScheduleItem(s3, Date("2018/11/08/22:37"), Date("2018/11/08/22:38")));
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
	Route & r1  = c.addRoute(1);
	Station & s1 = c.addStation("Malinovka", 1);
	ASSERT_THROWS(r1.addScheduleItem(TrainScheduleItem(s1, Date("2017/11/08/11:59"), Date("2017/11/08/11:00"))), Messages::InvalidTimeSended);

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

DECLARE_OOP_TEST(test_add_duplicated_routes) 
{
	Controller c;

	c.addRoute(128);

    ASSERT_THROWS(c.addRoute(128), Messages::DuplicateRoute);
}

DECLARE_OOP_TEST(test_most_long_route)
{

	Controller c;
	createCommonConfiguration(c);
    Route & r1 = c.findRoute(127);
    Route & r2 = c.findRoute(128);
    Route & r3 = c.findRoute(129);
    Route & r4 = c.findRoute(726);
    std::vector<Route * > routes{ &r1, &r2,&r3,&r4 };

    std::multimap <Date, Route *, std::greater<Date>> expectedResult;
    for (auto &x : routes) 
    {
        expectedResult.insert({ Date(x->getRouteDuration()),x });
    }

    std::multimap < Date, Route *, std::greater<Date>> receivedResult = c.getMostLongRoute(5);

    assert(expectedResult == receivedResult);
}

DECLARE_OOP_TEST(test_stations_with_not_enough_perons_1)
{
	Controller c;
	createOverlapConfiguration(c);

    std::set<Station const * > expectedResult{ &c.findStation("Novgorodska"),&c.findStation("Lviv") };

	std::set<Station const *> receivedResult = c.getStationsWithNotEnoughtPerons();

	assert(expectedResult == receivedResult);
}

DECLARE_OOP_TEST(test_stations_with_not_enough_perons_2) 
{
	Controller c;

	Station & s1 =  c.addStation("Novgorodska", 10);

    std::vector<Route *> routes;
    std::vector<Train * > trains;
    
	for (int i = 0; i < 10; i++) 
	{
	    routes.emplace_back(&c.addRoute( i+ 127));
        trains.emplace_back(&c.addTrain(i, 860));
        routes[i]->addScheduleItem(TrainScheduleItem(s1, Date("2018/11/08/11:45"), Date("2018/11/08/12:45")));
        trains[i]->setRoute(routes[i]);
	}
	Route & r2 = c.addRoute(450);
	Train & t2 = c.addTrain(120, 123);

    r2.addScheduleItem(TrainScheduleItem(s1, Date("2018/11/08/12:20"), Date("2018/11/08/12:45")));
    t2.setRoute(&r2);
  
	std::set<Station const *> expectedResult = {&s1};

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

    std::set<std::pair<Station const * , Station const * >> receivedResult = c.getPairedStations(5);
	
    std::vector< std::pair<Station &, Station &> > expectedValue
    { 
		{c.findStation("Kharkiv"),c.findStation("Kremenchug")},
		{c.findStation("Kharkiv"),c.findStation("Lviv")},
		{c.findStation("Kremenchug"),c.findStation("Lviv")},
		{c.findStation("Kharkiv"),c.findStation("Poltava")},
		{c.findStation("Kremenchug"),c.findStation("Poltava")} 
	};
    for (auto & x : expectedValue) 
    {
        assert (receivedResult.find({ &x.first , &x.second}) != receivedResult.end());
    }
}
DECLARE_OOP_TEST(test_unused_stations) 
{
	Controller c;
	createCommonConfiguration(c);

	//add unused stations
	Station & s1 = c.addStation("Kirovka", 1);
	Station & s2 = c.addStation("Golovnevka", 2);
    Station & s3 = c.addStation("Kirilenska", 4);
    Station & s4 = c.addStation("Malinovka", 1);
	
    std::set<Station const * > expectedResult { &s1,&s2,&s3,&s4 };
	assert(expectedResult == c.getUnusedStations());
}
/*****************************************************************************/

