#include "percussione.h"

Percussione::Percussione(double _price, const std::string& _brand, bool _tuned, bool _used):
	Strumento(_price, _brand, _used), tuned(_tuned){}
