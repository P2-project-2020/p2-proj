#pragma once
#include "fiato.h"

class Tromba: public Fiato{
public:
	Tromba(Strumento::Tune, double, const std::string&, Fiato::Material = brass, bool = false, const std::string& = "");
	std::string className() const;
};
