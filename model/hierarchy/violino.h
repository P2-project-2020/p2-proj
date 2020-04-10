#pragma once
#include "arco.h"

class Violino: public Arco{
public:
	static const std::string lutherie_string;
	Violino(double, const std::string& = lutherie_string, const std::string& = "", bool = false);

	std::string className() const;
	Strumento::Tune tune() const;
	std::string getMaterial() const { return "Legno"; }
};
const std::string Violino::lutherie_string = "Liuteria";
