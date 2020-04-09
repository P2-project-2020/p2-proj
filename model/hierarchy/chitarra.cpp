#include "chitarra.h"
const unsigned int Chitarra::defaultStrings = 6;

Chitarra::Chitarra(Chitarra::guitarType _type, double _price, const std::string& _brand, const std::string& _model, const std::string& _desc, bool _used, unsigned int _stringsNumber):
	Strumento(_price,_brand,_used,_desc), Corda(_stringsNumber), type(_type), model(_model){}

Strumento::Tune Chitarra::tune() const { return undefined; }

std::string Chitarra::className() const {
	std::string specifier;
	switch (type){
	case electric:
		specifier = "elettrica";
		break;
	case acoustic:
		specifier = "acustica";
		break;
	case classic:
		specifier = "classica";
		break;
	}
	return std::string("chitarra ") + specifier;
}
