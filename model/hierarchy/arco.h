#pragma once
#include "strumento.h"

class Arco: virtual public Strumento{ // dato che ereditarietà virtuale e classe astratta il costruttore di strumento non verrà mai chiamato da lei
protected:
	bool lutherie;
public:
	Arco(bool = false);
};
