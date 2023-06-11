#include "HTMLPlaylist.h"
#include <fstream>
#include <exception>
#include <Windows.h>
#include <shellapi.h>

void HTMLPlaylist::writeToFile() const
{
	std::ofstream f{ filename };

	if (!f.is_open()) {
		throw std::exception("File not found");
	}
	f << "<!DOCTYPE html>\n";
	f << "<html>\n";
	f << "<head>\n";
	f << "	<title>Playlist</title>\n";
	f << "</head>\n";
	f << "<body>\n";
	f << "<table border=\"1\">\n";
	f << "	<tr>\n";
	f << "		<td>Title</td>\n";
	f << "		<td>Description</td>\n";
	f << "		<td>Number of People</td>\n";
	f << "		<td>Date</td>\n";
	f << "		<td>Time</td>\n";
	f << "		<td>Link</td>\n";
	f << "\t</tr>\n";
	for (Event current_event : this->events) {
		f << "\t<tr>\n";
		f << "\t\t<td>" << current_event.getTitle() << "</td>\n";
		f << "\t\t<td>" << current_event.getDescription() << "</td>\n";
		f << "\t\t<td>" << current_event.getNumberOfPeople() << "</td>\n";
		f << "\t\t<td>" << current_event.getDate() << "</td>\n";
		f << "\t\t<td>" << current_event.getTime() << "</td>\n";
		f << "\t\t<td><a href=\"" << current_event.getLink() << "\>Link</a></td>\n";
		f << "\t</tr>\n";
	}
	f << "</table>\n</body>\n</html>\n";
}

void HTMLPlaylist::displayPlaylist() const
{
	std::string fileLocation = "\"" + this->filename + "\"";

	ShellExecuteA(NULL, "open", "C:/Program Files/Google/Chrome/Application/chrome.exe", fileLocation.c_str(), NULL, SW_SHOWNORMAL);
}
