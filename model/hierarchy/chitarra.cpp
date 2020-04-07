#include "chitarra.h"

Chitarra::Chitarra(Chitarra::guitarType _type, double _price, const std::string& _brand, const std::string& _model, bool _used, unsigned int _stringsNumber):
	Corda(_stringsNumber,_price,_brand,_used), type(_type), model(_model){}

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
