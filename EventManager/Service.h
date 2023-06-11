#pragma once
#define _CRTDBG_MAP_ALLOC
#define _CRT_SECURE_NO_WARNINGS
#include "DynamicArray.h"
#include "CSVPlaylist.h"
#include "HTMLPlaylist.h"
#include "EventValidator.h"

class Service {
private:
	Repo<Event> currentArray;
	Repo<Event> userArray;
	FilePlaylist* userPlaylist;
	EventValidator validator;
	int used_elements;

public:
	Service();
	~Service();

	void initializePlaylist(const std::string& type);
	void addElementToRepo(const std::string& title, const std::string& description, const std::string& date, const std::string& time, const int& number_of_people, const std::string& link);
	void removeElementFromRepo(const std::string& given_title);
	void updateElement(const std::string& title_identifier, const std::string& new_title, const std::string& new_description, const std::string& new_date, const std::string& new_time, const int& new_number_of_people, const std::string& new_link);
	int getRepoLength() const;
	std::string* createPrintableList() const;
	Repo<Event> createIterableWithGivenNameUser(const char* given_month);
	void addToUserList(const Event& chosenEvent);
	Repo<Event> createPrintableUserList();
	void removeFromUserList(const std::string& given_title);
	Repo<Event> createIterableWithNoName();
