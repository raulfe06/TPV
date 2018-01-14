#pragma once
#include <stdexcept>
#include <exception>

using namespace std;

class PacmanError : public logic_error
{
public:
	PacmanError(const string& m) : logic_error("Error " + m) {};
};

