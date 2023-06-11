#include "CSVPlaylist.h"
#include <fstream>
#include <exception>
#include <Windows.h>
#include <shellapi.h>

void CSVPlaylist::writeToFile() const
{
	std::ofstream f{ filename };

	if (!f.is_open()) {
		throw std::exception("File not found");

	}
	for (Event current_event : this->events) {
		f << current_event << '\n';
	}
	f.close();
}

void CSVPlaylist::displayPlaylist() const
{
	std::string fileLocation = "\"" + this->filename + "\"";

	ShellExecuteA(NULL, "open", "C:/Program Files/Microsoft Office/root/Office16/EXCEL.EXE", fileLocation.c_str(), NULL, SW_SHOWNORMAL);

}
