#include "strumento.h"

Strumento::Strumento(double _price, const std::string& _brand, bool _used, const std::string& _desc):
	price(_price),description(_desc),used(_used),brand(_brand){}

double Strumento::getPrice() const {
	return price;
}

void Strumento::setPrice(double _price) {
	price = _price;
}

std::string Strumento::getDescription() const {
	return description;
}

void Strumento::setDescription(const std::string& _desc) {
	description = _desc;
}
