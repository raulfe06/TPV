#pragma once
#include "PacmanError.h"

class FileNotFoundError : public PacmanError
{

public:
	FileNotFoundError(const string& m) : PacmanError("al no encontrar archivo: " + m) {};
};

