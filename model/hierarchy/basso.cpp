#include "basso.h"

Basso::Basso(bassType _type, double _price, const std::string& _brand, bool _used, unsigned int _stringNumber, bool _fretLess):
	Corda(_stringNumber, _price, _brand, _used), type(_type), fretLess(_fretLess){}

std::string Basso::className() const {
	std::string specifier;
	if(type == electric) specifier = "elettrico";
	else specifier = "acustico";
	return "basso " + specifier;
}
