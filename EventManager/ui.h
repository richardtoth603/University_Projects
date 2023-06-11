#pragma once
#define _CRTDBG_MAP_ALLOC

#include "Service.h"

class UI {
private:
	Service current_service;
	int choice = 0;
public:
	UI();
	~UI();
	void chooseMode();
	void printMenuAdmin();
	void manageChoicesAdministrator();
	void printMenuUser();
	void manageChoicesUser();
	int getChoice() const;
};
