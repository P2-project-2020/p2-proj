#pragma once
#include "corda.h"

class Basso: virtual public Corda{
public:
	enum bassType {electric, acoustic};
	Basso(bassType, double, const std::string&, const std::string& = "", bool = false, unsigned int = defaultStrings, bool = false);
	std::string className() const;
	Strumento::Tune tune() const { return undefined; }
	std::string getMaterial() const { return "Legno"; }
	
private:
	static const unsigned int defaultStrings;
	bassType type;
	bool fretLess;
};
