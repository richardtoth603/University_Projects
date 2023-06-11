#pragma once
#include "FilePlaylist.h"
#include <string>

class CSVPlaylist :
	public FilePlaylist
{
public:
	CSVPlaylist(const std::string& filename) : FilePlaylist(filename) {}

	void writeToFile() const override;

	void displayPlaylist() const override;
};