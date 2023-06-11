#include "EventValidator.h"

EventException::EventException(std::vector<std::string> _errors): errors{_errors}
{
}

std::vector<std::string> EventException::getErrors() const
{
	return this->errors;
}

void EventValidator::validate(const Event& e)
{
	std::vector<std::string> errors;
	if (e.getTitle().size() == 0)
		errors.push_back("The title cannot be empty\n");
	if (e.getDescription().size() == 0)
		errors.push_back("The description cannot be empty\n");
	if (e.getDate().size() != 10)
		errors.push_back("Incorrect date\n");
	
	size_t posWww = e.getLink().find("www");
	size_t posHttp = e.getLink().find("http");
	if (posWww != 0 && posHttp != 0)
		errors.push_back("Incorrect link\n");

	if (errors.size() > 0)
		throw EventException(errors);

}