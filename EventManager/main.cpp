#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#define _CRTDBG_MAP_ALLOC_NEW
#include <crtdbg.h>
#include <assert.h>
#endif
#include "ui.h"
#include "Service.h"
#include <iostream>


using namespace std;

void testAll()
{
	Event testEvent1;
	testEvent1.setTitle("Test1");
	testEvent1.setDescription("testDescription");
	testEvent1.setDate("03/03/2000");
	testEvent1.setTime("testTime");
	testEvent1.setNOfPeople(2);
	testEvent1.setLink("testLink");
	assert(testEvent1.getTitle() == "Test1");
	assert(testEvent1.getDescription() == "testDescription");
	assert(testEvent1.getDate() == "03/03/2000");
	assert(testEvent1.getTime() == "testTime");
	assert(testEvent1.getNumberOfPeople() == 2);
	assert(testEvent1.getLink() == "testLink");
	Service test_service;
	test_service.addElementToRepo("Neversea", "Festival", "04/02/2022", "23:44", 2000, "https://www.extasy.com/entertainment/neversea-festival-2023?gclid=Cj0KCQjwla-hBhD7ARIsAM9tQKsyiWDUJ_zWk2NkhhDzsWvEWiuIFMReKHDCGfe1U4l_2L3Ir-F0g50aArf1EALw_wcB/");
	test_service.addElementToRepo("Untold", "Festival", "02/03/2023", "12:00", 4000, "https://www.untold.com/tickets/?gclid=Cj0KCQjwla-hBhD7ARIsAM9tQKvVueSkHn6VrViL0QGdVEjDMqSrPHoUkXQQ1LtXKze3aHW_oWrBWZEaAu30EALw_wcB/");
	test_service.addElementToRepo("Electric Castle", "Festival", "12/03/2023", "13::00", 12000, "https://www.electriccastle.ro/tickets?gclid=Cj0KCQjwla-hBhD7ARIsAM9tQKuDNytlZqmD7FSdovAxijKGAHxVnT4Flp48uLjeKM04iqNoFtH1Kk8aAkIZEALw_wcB/");
	test_service.addElementToRepo("AoA", "Festival", "24/04/2023", "15:00", 2000, "https://www.openairfestival.ro/");
	assert(test_service.getRepoLength() == 4);
	try
	{
		test_service.addElementToRepo("Neversea", "Festival", "04/02/2022", "23:44", 2000, "https://www.extasy.com/entertainment/neversea-festival-2023?gclid=Cj0KCQjwla-hBhD7ARIsAM9tQKsyiWDUJ_zWk2NkhhDzsWvEWiuIFMReKHDCGfe1U4l_2L3Ir-F0g50aArf1EALw_wcB/");
		assert(false);
	}
	catch (const char* message)
	{
		assert(true);
	}
	test_service.removeElementFromRepo("Electric Castle");
	assert(test_service.getRepoLength() == 3);
	try
	{
		test_service.removeElementFromRepo("Electric Castle");
		assert(false);
	}
	catch (const char* message)
	{
		assert(true);
	}
	try
	{
		test_service.updateElement("Neversea", "Test1", "Festival", "04/02/2022", "23:44", 2000, "https://www.extasy.com/entertainment/neversea-festival-2023?gclid=Cj0KCQjwla-hBhD7ARIsAM9tQKsyiWDUJ_zWk2NkhhDzsWvEWiuIFMReKHDCGfe1U4l_2L3Ir-F0g50aArf1EALw_wcB/");
		test_service.updateElement("shalalala", "Test2", "Festival", "04/02/2022", "23:44", 2000, "https://www.extasy.com/entertainment/neversea-festival-2023?gclid=Cj0KCQjwla-hBhD7ARIsAM9tQKsyiWDUJ_zWk2NkhhDzsWvEWiuIFMReKHDCGfe1U4l_2L3Ir-F0g50aArf1EALw_wcB/");
		assert(false);
	}
	catch (const char* message)
	{
		assert(true);
	}
	std::string* testPrintable = test_service.createPrintableList();
	//test_service.addElementToRepo("Test1", "testDescription", "testDate", "testTime", 2, "testLink");
	test_service.addToUserList(testEvent1);
	Event testEvent2;
	testEvent2.setTitle("Test2");
	testEvent2.setDescription("testDescription");
	testEvent2.setDate("04/03/2000");
	testEvent2.setTime("testTime");
	testEvent2.setNOfPeople(2);
	testEvent2.setLink("testLink");
	test_service.addElementToRepo("Test2", "testDescription", "04/03/2000", "testTime", 2, "testLink");
	test_service.addToUserList(testEvent2);
	Repo<Event> testIterable1 = test_service.createIterableWithGivenNameUser("03");
	Repo<Event> testIterable2 = test_service.createIterableWithGivenNameUser("");
	Repo<Event> testIterable3 = test_service.createPrintableUserList();
	try
	{
		test_service.addToUserList(testEvent1);
		assert(false);
	}
	catch (const char* message)
	{
		assert(true);
	}
	test_service.removeFromUserList("Test1");
	try
	{
		test_service.removeFromUserList("Test1");
		assert(false);
	}
	catch (const char* message)
	{
		assert(true);
	}
	testIterable1 = test_service.createIterableWithNoName();
	try
	{
		testIterable1.getItem(20222);
		assert(false);
	}
	catch (const char* message)
	{
		assert(true);
	}
	testIterable1.getItem(0);
	Repo<Event> testRepo;
	testRepo.addItem(testEvent1);
	testRepo.getItemByName(testEvent1.getTitle());
	try
	{
		testRepo.getItemByName("aksgasfaslkf");
		assert(false);
	}
	catch (const char* message)
	{
		assert(true);
	}
	testRepo.removeItem(0);
	try
	{
		testRepo.removeItem(23);
		assert(false);
	}
	catch (const char* message)
	{
		assert(true);
	}
	testRepo.addItem(testEvent1);
	testRepo.updateItemByIndex(0, testEvent2);
	try
	{
		testRepo.updateItemByIndex(293, testEvent2);
		assert(false);
	}
	catch (const char* message)
	{
		assert(true);
	}
	std::cout << "passed all tests\n";
}

void manageMenu()
{
	UI ui;
	ui.chooseMode();
	while (ui.getChoice())
	{
		if (ui.getChoice() == 1)
		{
			ui.printMenuAdmin();
			do
			{
				ui.manageChoicesAdministrator();
			} while (ui.getChoice());
		}
		else if (ui.getChoice() == 2)
		{
			ui.printMenuUser();
			do
			{
				ui.manageChoicesUser();
			} while (ui.getChoice());
		}
		ui.chooseMode();
	}
}

int main()
{
	//testAll();
	manageMenu();
	_CrtDumpMemoryLeaks();
	return 0;
} 