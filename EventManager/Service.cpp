#include "Service.h"
#include <sstream>
#include <assert.h>
#include <iostream>
#define _CRT_SECURE_NO_WARNINGS

Service::Service()
{
	this->used_elements = 0;
	this->currentArray.readFile();
	//this->addElementToRepo("Neversea", "Festival", "04/02/2022", "23:44", 2000, "https://www.extasy.com/entertainment/neversea-festival-2023?gclid=Cj0KCQjwla-hBhD7ARIsAM9tQKsyiWDUJ_zWk2NkhhDzsWvEWiuIFMReKHDCGfe1U4l_2L3Ir-F0g50aArf1EALw_wcB/");
	//this->addElementToRepo("Untold", "Festival", "02/03/2023", "12:00", 4000, "https://www.untold.com/tickets/?gclid=Cj0KCQjwla-hBhD7ARIsAM9tQKvVueSkHn6VrViL0QGdVEjDMqSrPHoUkXQQ1LtXKze3aHW_oWrBWZEaAu30EALw_wcB/");
	//this->addElementToRepo("Electric Castle", "Festival", "12/03/2023", "13::00", 12000, "https://www.electriccastle.ro/tickets?gclid=Cj0KCQjwla-hBhD7ARIsAM9tQKuDNytlZqmD7FSdovAxijKGAHxVnT4Flp48uLjeKM04iqNoFtH1Kk8aAkIZEALw_wcB/");
	//this->addElementToRepo("AoA", "Festival", "24/04/2023", "15:00", 2000, "https://www.openairfestival.ro/");
	/*
	assert(this->currentArray.getSize() == 4);
	std::cout << "passed";
	this->removeElementFromRepo("Electric Castle");
	assert(this->currentArray.getSize() == 3);
	std::cout << "passed";
	try
	{
		this->removeElementFromRepo("Electric Castle");
		assert(false);
	}
	catch (const char* message)
	{
		assert(true);
		std::cout << "passed";
	}
	this->addElementToRepo("Electric Castle", "Festival", "12/03/2023", "13::00", 12000, "https://www.electriccastle.ro/tickets?gclid=Cj0KCQjwla-hBhD7ARIsAM9tQKuDNytlZqmD7FSdovAxijKGAHxVnT4Flp48uLjeKM04iqNoFtH1Kk8aAkIZEALw_wcB/");
	try
	{
		this->addElementToRepo("Electric Castle", "Festival", "12/03/2023", "13::00", 12000, "https://www.electriccastle.ro/tickets?gclid=Cj0KCQjwla-hBhD7ARIsAM9tQKuDNytlZqmD7FSdovAxijKGAHxVnT4Flp48uLjeKM04iqNoFtH1Kk8aAkIZEALw_wcB/");
		assert(false);
	}
	catch (const char* message)
	{
		assert(true);
		std::cout << "passed";
	}
	*/
}

Service::~Service()
{
}

void Service::initializePlaylist(const std::string& type)
{
	if (type == "csv")
	{
		this->userPlaylist = new CSVPlaylist("CSVRepo.csv");
	}
	if (type == "html")
	{
		this->userPlaylist = new HTMLPlaylist("htmlrepo.html");
	}
}

void Service::addElementToRepo(const std::string& title, const std::string& description, const std::string& date, const std::string& time, const int& number_of_people, const std::string& link)
{
	Event new_event(title, description, date, time, number_of_people, link);
	validator.validate(new_event);
	this->currentArray.addItem(new_event);
	this->currentArray.writeToText();
}

void Service::removeElementFromRepo(const std::string& given_title)
{
	this->currentArray.removeItemByName(given_title);
	this->currentArray.writeToText();
}

void Service::updateElement(const std::string& title_identifier, const std::string& new_title, const std::string& new_description, const std::string& new_date, const std::string& new_time, const int& new_number_of_people, const std::string& new_link)
{
	Event updated_event(new_title, new_description, new_date, new_time, new_number_of_people, new_link);
	validator.validate(updated_event);
	this->currentArray.updateItem(title_identifier, updated_event);
	this->currentArray.writeToText();
}

int Service::getRepoLength() const
{
	return this->currentArray.getSize();
}

std::string* Service::createPrintableList() const
{
	int repoSize = this->currentArray.getSize();
	std::string* list_of_printables;
	list_of_printables = new std::string[repoSize];
	for (int i = 0; i < repoSize; i++)
		list_of_printables[i] = this->currentArray.getStringFormByIndex(i);
	return list_of_printables;
}

Repo<Event> Service::createIterableWithGivenNameUser(const char* given_month)
{
	int size = this->currentArray.getSize();
	Repo<Event> list_of_printables;
	if (strcmp(given_month, ""))
	{
		for (int i = 0; i < size; i++)
		{
			char* aux_date = strdup(this->currentArray.getItem(i).getDate().c_str());
			char* ptr = strtok(aux_date, "/");
			ptr = strtok(NULL, "/");
			if (strcmp(ptr, given_month) == 0)
				list_of_printables.addItem(this->currentArray.getItem(i));
			delete[] aux_date;
		}
		return list_of_printables;
	}
	for (int i = 0; i < size; i++)
	{
		list_of_printables.addItem(this->currentArray.getItem(i));
	}
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = i + 1; j < size; j++)
		{
			/*
			char* aux_date_i = strdup(this->currentArray.getItem(i).getDate().c_str());
			char* ptr_i = strtok(aux_date_i, "/");
			ptr_i = strtok(NULL, "/");
			char* aux_date_j = strdup(this->currentArray.getItem(j).getDate().c_str());
			char* ptr_j = strtok(aux_date_j, "/");
			ptr_j = strtok(NULL, "/");
			if (strcmp(aux_date_i, aux_date_j) < 0)
			{
				Event event_i = this->currentArray.getItem(i);
				Event event_j = this->currentArray.getItem(j);
			}*/
			std::string date_i[4];
			std::string date_j[4];
			std::string separated_date;
			std::istringstream full_date_i(list_of_printables.getItem(i).getDate());
			std::istringstream full_date_j(list_of_printables.getItem(j).getDate());
			int k = 0;
			while (getline(full_date_i, separated_date, '/'))
			{
				date_i[k++] = separated_date;
			}
			k = 0;
			while (getline(full_date_j, separated_date, '/'))
			{
				date_j[k++] = separated_date;
			}
			if (date_i[2] < date_j[2])
			{
				Event event_i = list_of_printables.getItem(i);
				Event event_j = list_of_printables.getItem(j);
				list_of_printables.updateItemByIndex(i, event_j);
				list_of_printables.updateItemByIndex(j, event_i);
			}
			else if (date_i[2] == date_j[2] && date_i[1] < date_j[1])
			{
				Event event_i = list_of_printables.getItem(i);
				Event event_j = list_of_printables.getItem(j);
				list_of_printables.updateItemByIndex(i, event_j);
				list_of_printables.updateItemByIndex(j, event_i);
			}
			else if (date_i[2] == date_j[2] && date_i[1] == date_j[1] && date_i[0] < date_j[0])
			{
				Event event_i = list_of_printables.getItem(i);
				Event event_j = list_of_printables.getItem(j);
				list_of_printables.updateItemByIndex(i, event_j);
				list_of_printables.updateItemByIndex(j, event_i);
			}
		}
	}
	return list_of_printables;
}

void Service::addToUserList(const Event& chosenEvent)
{
	try
	{
		Event toBeAdded = chosenEvent;
		int nr_of_people = chosenEvent.getNumberOfPeople() + 1;
		toBeAdded.setNOfPeople(nr_of_people);
		this->userArray.addItem(toBeAdded);
		this->currentArray.updateItem(toBeAdded.getTitle(), toBeAdded);
		this->userPlaylist->add(chosenEvent); //test
		this->userPlaylist->writeToFile(); //test
		this->userPlaylist->displayPlaylist(); //test
	}
	catch (const char* message)
	{
		throw message;}
}

Repo<Event> Service::createPrintableUserList()
{
	return this->userArray;
}

void Service::removeFromUserList(const std::string& given_title)
{
	try
	{
		Event item_to_be_removed = this->currentArray.getItemByName(given_title);
		int nr_of_people = item_to_be_removed.getNumberOfPeople() - 1;
		item_to_be_removed.setNOfPeople(nr_of_people);
		this->currentArray.updateItem(given_title, item_to_be_removed);
		this->userArray.removeItemByName(given_title);
	}
	catch (const char* message)
	{
		throw message;}
}

Repo<Event> Service::createIterableWithNoName()
{
	Repo<Event> list_of_printables;
	int size = this->currentArray.getSize();
	for (int i = 0; i < size; i++)
	{
		list_of_printables.addItem(this->currentArray.getItem(i));
	}
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = i + 1; j < size; j++)
		{
			/*
			char* aux_date_i = strdup(this->currentArray.getItem(i).getDate().c_str());
			char* ptr_i = strtok(aux_date_i, "/");
			ptr_i = strtok(NULL, "/");
			char* aux_date_j = strdup(this->currentArray.getItem(j).getDate().c_str());
			char* ptr_j = strtok(aux_date_j, "/");
			ptr_j = strtok(NULL, "/");
			if (strcmp(aux_date_i, aux_date_j) < 0)
			{
				Event event_i = this->currentArray.getItem(i);
				Event event_j = this->currentArray.getItem(j);
			}*/
			std::string date_i[4];
			std::string date_j[4];
			std::string separated_date;
			std::istringstream full_date_i(this->currentArray.getItem(i).getDate());
			std::istringstream full_date_j(this->currentArray.getItem(j).getDate());
			int k = 0;
			while (getline(full_date_i, separated_date, '/'))
			{
				date_i[k++] = separated_date;
			}
			k = 0;
			while (getline(full_date_j, separated_date, '/'))
			{
				date_j[k++] = separated_date;
			}
			if (date_i[2] < date_j[2])
			{
				Event event_i = this->currentArray.getItem(i);
				Event event_j = this->currentArray.getItem(j);
				list_of_printables.updateItemByIndex(i, event_j);
				list_of_printables.updateItemByIndex(j, event_i);
			}
			else if (date_i[2] == date_j[2] && date_i[1] < date_j[1])
			{
				Event event_i = this->currentArray.getItem(i);
				Event event_j = this->currentArray.getItem(j);
				list_of_printables.updateItemByIndex(i, event_j);
				list_of_printables.updateItemByIndex(j, event_i);
			}
			else if (date_i[2] == date_j[2] && date_i[1] == date_j[1] && date_i[0] < date_j[0])
			{
				Event event_i = this->currentArray.getItem(i);
				Event event_j = this->currentArray.getItem(j);
				list_of_printables.updateItemByIndex(i, event_j);
				list_of_printables.updateItemByIndex(j, event_i);
			}
		}
	}
	return list_of_printables;
}

