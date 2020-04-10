#pragma once
#include "arco.h"

class Viola: public Arco{
	Strumento::Tune key;
public:
	static const std::string lutherie_string;
	Viola(double, const std::string& = lutherie_string, const std::string& = "", Strumento::Tune = contralto ,bool = false);

	std::string className() const;
	Strumento::Tune tune() const;
	std::string getMaterial() const { return "Legno"; }
};
const std::string Viola::lutherie_string = "Liuteria";
