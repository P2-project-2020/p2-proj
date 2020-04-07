#include "sax.h"

Sax::Sax(Fiato::Material _material, Strumento::Tune _tune, double _price, const std::string& _brand, bool _used):
	Fiato(_material, _tune, Fiato::woodwind_mouthpiece, _price, _brand, _used){}
