#pragma once
#include "strumento.h"

class Corda: virtual public Strumento { // derivazione virtuale && calsse astratta => non dovrà mai occuparsi di costruire Strumento
private:
	unsigned int strings;		// Numero di corde dello strumento
public:
	Corda(unsigned int);
	unsigned int getStringsNumber() const;
	void setStringsNumber(unsigned int);
};
