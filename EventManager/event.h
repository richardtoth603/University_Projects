#pragma once
#define _CRTDBG_MAP_ALLOC
#include <string>
#include <fstream>
#include <iostream>

class Event
{
private:
	std::string title;
	std::string description;
	int number_of_people;
	std::string date;
	std::string time;
	std::string link;
	

public:
	Event();
	Event(const std::string& title, const std::string& description, const std::string& date, const std::string& time, const int& number_of_people, const std::string& link);
	Event(const Event&);
	~Event();

	bool operator==(const Event& other) const {
		return title == other.title && description == other.description && number_of_people == other.number_of_people && date == other.date && time == other.time && link == other.link;
	}

	friend std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		os << e.title << "," << e.description << "," << e.date << "," << e.time << "," << std::to_string(e.number_of_people) << "," << e.link;
		return os;
	}

	friend std::istream& operator>>(std::istream& is, Event& e);

	std::string getTitle() const { return title; }
	std::string getDescription() const { return description; }
	std::string getDate() const { return date; }
	std::string getTime() const { return time; }
	int getNumberOfPeople() const { return number_of_people; }
	std::string getLink() const { return link; }

	void setTitle(const std::string& new_title);
	void setDescription(const std::string& new_description);
	void setDate(const std::string& new_date);
	void setTime(const std::string& new_time);
	void setNOfPeople(const int& new_number);
	void setLink(const std::string& new_link);

	std::string toString() const;
};
