#pragma once
#include "strumento.h"

class Corda: virtual public Strumento{
protected:
	unsigned int strings;		// Numero di corde dello strumento
public:
	Corda(unsigned int, double, const std::string&, bool = false);
	unsigned int getStringsNumber() const { return strings; }
};
