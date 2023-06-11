#include "ui.h"
#include <iostream>
#include <istream>
#include <windows.h>
#include "EventValidator.h"

UI::UI()
{
	std::cout << "choose a file type: ";
	std::string fileType;
	std::cin >> fileType;
	std::cin.clear();
	this->current_service.initializePlaylist(fileType);
}

UI::~UI()
{
}

void UI::chooseMode()
{
	std::cout << "1. Admin\n";
	std::cout << "2. User\n";
	std::cout << "Please choose a mode: ";
	std::cin >> choice;
}

void UI::printMenuAdmin()
{
	std::cout << "1. add an event\n";
	std::cout << "2. delete an event\n";
	std::cout << "3. update an event\n";
	std::cout << "4. see all events\n";
	std::cout << "0. exit\n";
}

void UI::manageChoicesAdministrator()
{
	std::cout << "\nplease input a choice: ";
	std::cin >> choice;
	if (std::cin.fail())
	{
		std::cin.clear();
		std::cout << "\nwrong input";
	}
	std::cin.get();
	if (choice == 1)
	{
		std::string title, description, date, time, link;
		int number_of_people;
		std::cout << "title: ";
		std::getline(std::cin, title);
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cout << "\nwrong input";
			return;
		}
		std::cout << "description: ";
		std::getline(std::cin, description);
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cout << "\nwrong input";
			return;
		}
		std::cout << "date: ";
		std::getline(std::cin, date);
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cout << "\nwrong input";
			return;
		}
		std::cout << "time: ";
		std::getline(std::cin, time);
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cout << "\nwrong input";
			return;
		}
		std::cout << "number of people: ";
		std::cin >> number_of_people;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cout << "\nwrong input";
			return;
		}
		std::cin.get();

		std::cout << "link: ";
		std::getline(std::cin, link);
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cout << "\nwrong input";
			return;
		}
		try
		{
			this->current_service.addElementToRepo(title, description, date, time, number_of_people, link);
		}
		catch(EventException& e)
		{
			for (auto message : e.getErrors())
				std::cout << message;
		}
		catch (RepositoryException& e)
		{
			std::cout << e.what() << '\n';
		}
		catch (FileException& e)
		{
			std::cout << e.what() << '\n';
		}
	}
	else if (choice == 2)
	{
		std::string given_title;
		std::getline(std::cin, given_title);
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cout << "\nwrong input";
			return;
		}
		try
		{
			this->current_service.removeElementFromRepo(given_title);
		}
		catch (RepositoryException& e)
		{
			std::cout << e.what() << '\n';
		}
	}
	else if (choice == 3)
	{
		std::string title, description, date, time, link, title_to_change;
		int number_of_people;
		std::cout << "title of element to update: ";
		std::getline(std::cin, title_to_change);
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cout << "\nwrong input";
			return;
		}
		std::cout << "title: ";
		std::getline(std::cin, title);
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cout << "\nwrong input";
			return;
		}
		std::cout << "description: ";
		std::getline(std::cin, description);
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cout << "\nwrong input";
			return;
		}
		std::cout << "date: ";
		std::getline(std::cin, date);
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cout << "\nwrong input";
			return;
		}
		std::cout << "time: ";
		std::getline(std::cin, time);
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cout << "\nwrong input";
			return;
		}
		std::cout << "number of people: ";
		std::cin >> number_of_people;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cout << "\nwrong input";
			return;
		}
		std::cin.get();
		std::cout << "link: ";
		std::getline(std::cin, link);
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cout << "\nwrong input";
			return;
		}
		try
		{
			this->current_service.updateElement(title_to_change, title, description, date, time, number_of_people, link);
		}
		catch (EventException& e)
		{
			for (auto message : e.getErrors())
				std::cout << message;
		}
		catch (RepositoryException& e)
		{
			std::cout << e.what() << '\n';
		}
	}
	else if (choice == 4)
	{
		std::string* printableList = this->current_service.createPrintableList();
		int len = this->current_service.getRepoLength();
		for (int i = 0; i < len; i++)
			std::cout << printableList[i] << "\n";
		delete[] printableList;
	}
}

void UI::printMenuUser()
{
	std::cout << "1. See events for a given month\n";
	std::cout << "2. See all events in user list\n";
	std::cout << "0. Exit";
}

void UI::manageChoicesUser()
{
	std::cout << "\nplease input a choice: ";
	std::cin >> choice;
	if (std::cin.fail())
	{
		std::cin.clear();
		std::cout << "\nwrong input";
	}
	if (choice == 1)
	{
		std::cin.get();
		std::cout << "Please enter a month: ";
		std::string given_date;
		std::getline(std::cin, given_date);
		if (given_date > "13" or given_date == "00" or given_date.size() > 2)
		{
			std::cout << "incorrect month\n";
			return;
		}
		char* given_month = strdup(given_date.c_str());
		Repo<Event> printableList = this->current_service.createIterableWithGivenNameUser(given_month);
		int len = printableList.getSize();
		int i = 0;
		while (i < len)
		{
			int userChoice;
			std::cout << printableList.getItem(i).toString() << "\n";
			std::cout << "1. add to list    2. next    3. remove from list    0. cancel\n";
			if (i == 0)
				ShellExecute(NULL, NULL, LPCWSTR(printableList.getItem(i).getLink().c_str()), NULL, NULL, SW_SHOWNORMAL);
			std::cin >> userChoice;
			if (std::cin.fail())
			{
				std::cin.clear();
				std::cout << "\nwrong input";
				return;
			}
			if (userChoice == 1)
			{
				try
				{
					this->current_service.addToUserList(printableList.getItem(i));
					if (i == len - 1)
					{
						i = 0;
						continue;
					}
					Event updatePrintable = printableList.getItem(i);
					updatePrintable.setNOfPeople(updatePrintable.getNumberOfPeople() + 1);
					printableList.updateItem(updatePrintable.getTitle(), updatePrintable);
					continue;
				}
				catch (const char* message)
				{
					std::cout << message << '\n';
				}
			}
			else if (userChoice == 2)
			{
				if (i == len - 1)
				{
					i = 0;
					continue;
				}
			}
			else if (userChoice == 3)
			{
				try
				{
					this->current_service.removeFromUserList(printableList.getItem(i).getTitle());
					if (i == len - 1)
					{
						i = 0;
						continue;
					}
					Event updatePrintable = printableList.getItem(i);
					updatePrintable.setNOfPeople(updatePrintable.getNumberOfPeople() - 1);
					printableList.updateItem(updatePrintable.getTitle(), updatePrintable);

				}
				catch (const char* message)
				{
					std::cout << message << '\n';
				}

			}
			else if (userChoice == 0)
				break;
			i++;
		}
		delete[] given_month;
	}
	if (choice == 2)
	{
		Repo<Event> printableList = this->current_service.createPrintableUserList();
		for (int i = 0; i < printableList.getSize(); i++)
			std::cout << printableList.getItem(i).toString() << "\n";
	}
}

int UI::getChoice() const
{
	return this->choice;
}
