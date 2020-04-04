#include "arco.h"

Arco::Arco(double _price, const std::string& _brand, const std::string& _specificDescription, bool _used):
	Strumento(_brand,_price,_used), specificDescription(_specificDescription){}
