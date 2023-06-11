#pragma once

#include "FilePlaylist.h"
#include <string>

class HTMLPlaylist : public FilePlaylist {
public:
	HTMLPlaylist(const std::string& filename) : FilePlaylist(filename) {}

	void writeToFile() const override;

	void displayPlaylist() const override;
};
