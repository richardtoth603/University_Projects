#include "RepoExceptions.h"

FileException::FileException(const std::string& msg) : message(msg)
{
}

const char* FileException::what()
{
	return message.c_str();
}

RepositoryException::RepositoryException() : exception{}, message{""}
{
}

RepositoryException::RepositoryException(const std::string& msg): message{msg}
{
}

const char* RepositoryException::what()
{
	return this->message.c_str();
}

const char* DuplicateEventException::what()
{
	return "There is another event with the same title";
}

const char* InexistentEventException::what()
{
	return "There are no events with the given title";
}
