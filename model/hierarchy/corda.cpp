#include "corda.h"

Corda::Corda(unsigned int _strings): // derivazione virtuale && calsse astratta => non dovrà mai occuparsi di costruire Strumento
	strings(_strings){}

unsigned int Corda::getStringsNumber() const { return strings; }

void Corda::setStringsNumber(unsigned int n){ strings = n; }
