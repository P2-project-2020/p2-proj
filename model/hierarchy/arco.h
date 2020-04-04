#pragma once
#include "strumento.h"

class Arco: virtual public Strumento{
protected:
	std::string specificDescription;
public:
	Arco(double, const std::string&, const std::string& = "", bool = false);
};
