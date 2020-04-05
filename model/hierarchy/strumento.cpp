#include "strumento.h"

Strumento::Strumento(double _price, const std::string& _brand, bool _used, Strumento::Tune _tune):
	price(_price),used(_used),brand(_brand),instrumentTune(_tune){}
