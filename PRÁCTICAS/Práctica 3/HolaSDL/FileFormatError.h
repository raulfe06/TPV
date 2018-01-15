#pragma once
#include "PacmanError.h"


class FileFormatError : public PacmanError
{

public:
	FileFormatError(const string& m) : PacmanError("de formato: " + m) {};
	~FileFormatError() {};
};

