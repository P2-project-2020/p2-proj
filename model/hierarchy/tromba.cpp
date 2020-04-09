#include "tromba.h"

Tromba::Tromba(Strumento::Tune _tune, double _price, const std::string& _brand,Fiato::Material _material, bool _used, const std::string& _desc):
	Strumento(_price,_brand,_used,_desc),Fiato(_material,_tune,brass_mouthpiece){}

std::string Tromba::className() const {
	return "Tromba";
}
