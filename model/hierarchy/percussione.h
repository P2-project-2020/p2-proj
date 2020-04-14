#pragma once
#include "strumento.h"

class Percussione: virtual public Strumento{
protected:
	bool tuned;					// intonato o no
public:
	Percussione(bool = false);
};
