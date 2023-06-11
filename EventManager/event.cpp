#include <string>
#include <vector>
#include "event.h"
#include <sstream>

using namespace std;

Event::Event()
{
	title = "";
	description = "";
	date = "";
	time = "";
	number_of_people = 0;
	link = "";
}

Event::Event(const std::string& title, const std::string& description, const std::string& date, const std::string& time, const int& number_of_people, const std::string& link)
{
	this->title = title;
	this->description = description;
	this->date = date;
	this->time = time;
	this->number_of_people = number_of_people;
	this->link = link;
}

Event::Event(const Event& event_to_be_copied)
{
	title = event_to_be_copied.title;
	description = event_to_be_copied.description;
	date = event_to_be_copied.date;
	time = event_to_be_copied.time;
	number_of_people = event_to_be_copied.number_of_people;
	link = event_to_be_copied.link;
}

Event::~Event()
{
}

void Event::setTitle(const std::string& new_title)
{
	this->title = new_title;
}

void Event::setDescription(const std::string& new_description)
{
	description = new_description;
}

void Event::setDate(const std::string& new_date)
{
	date = new_date;
}

void Event::setTime(const std::string& new_time)
{
	time = new_time;
}

void Event::setNOfPeople(const int& new_number)
{
	number_of_people = new_number;
}

void Event::setLink(const std::string& new_link)
{
	link = new_link;
}

string Event::toString() const
{
	return this->title + " " + this->description + " " + this->date + " " + this->time + " " + to_string(this->number_of_people) + " " + this->link;
}

istream& operator>>(istream& is, Event& e)
{
	std::string line;
	getline(is, line);

	vector<string> tokens;

	std::stringstream check1(line);

	std::string intermediate;

	while (getline(check1, intermediate, ' '))
	{
		tokens.push_back(intermediate);
	}

	if (tokens.size() != 6)
		return is;

	e.setTitle(tokens[0]);
	e.setDescription(tokens[1]);
	e.setDate(tokens[2]);
	e.setTime(tokens[3]);
	e.setNOfPeople(stoi(tokens[4]));
	e.setLink(tokens[5]);

	return is;
}
