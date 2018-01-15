#pragma once
#include "PacmanError.h"

class FileFormatError : public PacmanError
{

public:
	FileFormatError(const string& m) : PacmanError("al leer el arcvhivo: " + m) {};
};

