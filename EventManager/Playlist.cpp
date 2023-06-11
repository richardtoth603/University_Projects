#include "Playlist.h"

Playlist::Playlist()
{
	this->current = 0;
}

void Playlist::add(const Event& ev)
{
	this->events.push_back(ev);
}

void Playlist::remove(Event& ev)
{
	std::remove(this->events.begin(), this->events.end(), ev);
}

Event Playlist::getCurrentEvent()
{
	if (this->current == this->events.size())
		this->current = 0;
	return this->events[this->current];
	return Event{};
}

void Playlist::next()
{
	if (this->events.size() == 0)
		return;
	this->current++;
	Event currentEvent = this->getCurrentEvent();
}

bool Playlist::isEmpty()
{
	return this->events.size() == 0;
}