#pragma once	
#define _CRTDBG_MAP_ALLOC
#include "Event.h"
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include "RepoExceptions.h"

template <typename T>
class Repo {
private:
	std::vector<T> repo_array;
	std::string filename;

public:
	Repo();
	~Repo();
	Repo(const Repo&);
	int getSize() const;
	T getItem(int index);
	T getItemByName(std::string given_string);
	void addItem(const T& element);
	void removeItem(int index);
	void removeItemByName(std::string given_string);
	void updateItem(std::string title_identifier, T& updated_element);
	void updateItemByIndex(int index, T& updated_element);
	std::string getStringFormByIndex(int index) const;
	void writeToText();
	void readFile();
};

template <typename T>
Repo<T>::Repo()
{	
	this->filename = "textRepo.txt";
}

template <typename T>
Repo<T>::~Repo() {
}

template <typename T>
Repo<T>::Repo(const Repo& other)
{
	this->repo_array = other.repo_array;
}

template <typename T>
int Repo<T>::getSize() const
{
	return this->repo_array.size();
}

template <typename T>
T Repo<T>::getItem(int index)
{
	if (index < 0 || index > this->repo_array.size())
		throw "Index out of bounds";
	return this->repo_array[index];
}

template <typename T>
T Repo<T>::getItemByName(std::string given_string)
{
	for (auto iterator = this->repo_array.begin(); iterator != this->repo_array.end(); iterator++)
	{
		auto event_ptr = dynamic_cast<Event*>(&(*iterator));
		if (event_ptr->getTitle() == given_string)
			return *iterator;
	}
	throw InexistentEventException{};
}

template <typename T>
void Repo<T>::addItem(const T& element)
{
	
	Event e1{};
	try
	{
		e1 = this->getItemByName(element.getTitle());
		throw DuplicateEventException();
	}
	catch (InexistentEventException&)
	{
	}
	this->repo_array.push_back(element);
}

template <typename T>
void Repo<T>::removeItem(int index)
{
	if (index < 0 || index > this->repo_array.size())
		throw "Index out of bounds";
	auto it = this->repo_array.begin() + index;
	this->repo_array.erase(it);
}

template <typename T>
void Repo<T>::removeItemByName(std::string given_string)
{
	for (auto iterator = this->repo_array.begin(); iterator != this->repo_array.end(); iterator++)
	{
		auto event_ptr = dynamic_cast<Event*>(&(*iterator));
		if (event_ptr->getTitle() == given_string)
		{
			this->repo_array.erase(iterator);
			return;
		}
	}
	throw InexistentEventException{};
}
//helo

template <typename T>
void Repo<T>::updateItem(std::string title_identifier, T& updated_element)
{
	int flag = 0;
	for (auto iterator = this->repo_array.begin(); iterator != this->repo_array.end(); iterator++)
	{
		auto event_ptr = dynamic_cast<Event*>(&(*iterator));
		if (event_ptr->getTitle() == title_identifier)
		{
			*iterator = updated_element;
			flag = 1;
		}
	}
	if (flag == 0)
		throw InexistentEventException{};
}

template <typename T>
void Repo<T>::updateItemByIndex(int index, T& updated_element)
{
	if (index < 0 || index > this->repo_array.size())
		throw "Index out of bounds";
	this->repo_array[index] = updated_element;
}

template <typename T>
std::string Repo<T>::getStringFormByIndex(int index) const
{
	return this->repo_array[index].toString();
}

//a7

/*
template <typename T>
std::ostream& operator<<(std::ostream& out, const T& obj)
{
	out << obj.getTitle() << "," << obj.getDescription() << "," << obj.getDate() << "," << obj.getTime() << "," << obj.getLink();
	return out;
}
*/
template<typename T>
inline void Repo<T>::writeToText()
{
	std::ofstream fout("textRepo.txt");
	for (auto iterator : this->repo_array)
	{
		fout << iterator;
	}
		return;
}


template<typename T>
inline void Repo<T>::readFile()
{
	std::ifstream file("textRepo.txt");

	if (!file.is_open())
		throw std::exception("test");
	
	Event new_event;
	while (!file.eof())
	{
		while (file >> new_event)
		{
			this->repo_array.push_back(new_event);
		}
	}

	file.close();
}