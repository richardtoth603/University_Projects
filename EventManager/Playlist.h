#pragma once
#include <vector>
#include "event.h"

class Playlist
{
protected:
	std::vector<Event> events;
	int current;

public:
	Playlist();
	
	void add(const Event& ev);
	
	void remove(Event& ev);

	Event getCurrentEvent();

	void next();

	bool isEmpty();

	virtual ~Playlist() {}
};
