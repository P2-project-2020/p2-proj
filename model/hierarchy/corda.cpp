#include "corda.h"

Corda::Corda(unsigned int _strings, double _price, const std::string& _brand, bool _used):
	Strumento(_price,_brand,_used), strings(_strings){}
