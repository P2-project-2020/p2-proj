#include "viola.h"

Viola::Viola(double _price, const std::string& _brand, const std::string& _desc):
	Strumento(_price ,_brand, _desc), Arco(_brand == lutherie_string){}

std::string Viola::className() const {
	return "Viola";
}

Strumento::Tune Viola::tune() const {
	return undefined;
}
