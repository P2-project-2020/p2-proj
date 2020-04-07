#pragma once
#include "strumento.h"

class Percussione: virtual public Strumento{
	bool tuned;					// intonato o no
public:
	Percussione(bool = false);
};
