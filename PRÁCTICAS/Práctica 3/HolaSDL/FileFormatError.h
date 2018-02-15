#pragma once
#include "PacmanError.h"
#include "checkML.h"


class FileFormatError : public PacmanError
{

public:
	FileFormatError(const string& m) : PacmanError("de formato: " + m) {};
	~FileFormatError() {};
};

