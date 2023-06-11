#pragma once
#include "Playlist.h"
#include <string>

class FilePlaylist :
	public Playlist
{
protected:
	std::string filename;

public:
	FilePlaylist(const std::string& filename);

	virtual void writeToFile() const = 0;

	virtual void displayPlaylist() const = 0;

	virtual ~FilePlaylist() {}
};
