#pragma once
#include "arco.h"

class Viola: public Arco{
public:
	static const std::string lutherie_string;
	Viola(double, const std::string& = lutherie_string, const std::string& = "");

	std::string className() const;
	Strumento::Tune tune() const;
};
const std::string Viola::lutherie_string = "Liuteria";
