#pragma once
#include "strumento.h"

class Corda: virtual public Strumento{ // derivazione virtuale && calsse astratta => non dovrà mai occuparsi di costruire Strumento
protected:
	unsigned int strings;		// Numero di corde dello strumento
public:
	Corda(unsigned int);
	unsigned int getStringsNumber() const { return strings; }
};
