#include "basso.h"
const unsigned int Basso::defaultStrings = 4;

Basso::Basso(bassType _type, double _price, const std::string& _brand, const std::string& _desc, bool _used, unsigned int _stringNumber, bool _fretLess):
	Strumento(_price, _brand, _used, _desc), Corda(_stringNumber), type(_type), fretLess(_fretLess){}

std::string Basso::className() const {
	std::string specifier;
	if(type == electric) specifier = "elettrico";
	else specifier = "acustico";
	return "basso " + specifier;
}
