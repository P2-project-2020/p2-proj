#pragma once
#include "fiato.h"

class Sax: public Fiato {
public:
	Sax(Fiato::Material, Strumento::Tune, double, const std::string&, bool = false);
};
