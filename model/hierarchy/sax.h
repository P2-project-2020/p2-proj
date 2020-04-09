#pragma once
#include "fiato.h"

class Sax: public Fiato {
public:
	Sax(Strumento::Tune, double, const std::string&, Fiato::Material = brass, bool = false);

	std::string className() const;
};
