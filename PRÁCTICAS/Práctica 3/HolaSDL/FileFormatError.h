#pragma once
#include "PacmanError.h"
class FileFormatError : PacmanError
{
public:
	FileFormatError();
	~FileFormatError();
};

