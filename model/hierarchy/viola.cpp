#include "viola.h"
const std::string Viola::lutherie_string = "Liuteria";

Viola::Viola(double _price, const std::string& _brand, const std::string& _desc, Strumento::Tune _key, bool _used):
	Strumento(_price ,_brand, _used, _desc), Arco(_brand == lutherie_string), key(_key){}

std::string Viola::className() const {
	return "Viola";
}

Strumento::Tune Viola::tune() const {
	return key;
}
