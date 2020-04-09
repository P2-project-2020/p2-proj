#pragma once
#include "corda.h"

class Chitarra: public Corda{
public:
	enum guitarType {electric, acoustic, classic};

	Chitarra(Chitarra::guitarType, double, const std::string&, const std::string&, const std::string& = "", bool = false, unsigned int = defaultStrings);
	std::string className() const;
	Strumento::Tune tune() const;
	
private:
	static const unsigned int defaultStrings;
	guitarType type;
	std::string model;
};

