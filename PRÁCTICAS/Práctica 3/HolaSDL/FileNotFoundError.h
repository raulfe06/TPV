#pragma once
#include "PacmanError.h"
class FileNotFoundError : public PacmanError
{
private:
public:
	FileNotFoundError(const string& m) : PacmanError("archivo no encontrado: " + m){};
	~FileNotFoundError() {};
};

