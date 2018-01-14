#pragma once
#include "PacmanError.h"
class FileNotFoundError : PacmanError
{
public:
	FileNotFoundError();
	~FileNotFoundError();
};

