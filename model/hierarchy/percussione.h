#pragma once
#include "strumento.h"

class Percussione: virtual public Strumento{
	bool tuned;					// intonato o no
public:
	Percussione(double, const std::string&, bool = false, bool = false);
};
