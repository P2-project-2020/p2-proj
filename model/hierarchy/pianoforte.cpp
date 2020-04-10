#include "pianoforte.h"
const unsigned int Pianoforte::numberOfKeys = 48;

Pianoforte::Pianoforte(Pianoforte::Shape _shape, Pianoforte::Keys _keys, double _price, const std::string& _brand, bool _used, const std::string& _desc):
	Strumento(_price, _brand, _used, _desc),
	Corda(numberOfKeys*3),
	Percussione(true),
	pianoShape(_shape), pianoKeys(_keys){}

std::string Pianoforte::className() const {
	std::string specifier;
	switch (pianoShape) {
	case grand:
		specifier = "a coda"; break;
	case upright:
		specifier = "a muro"; break;
	}
	return "Pianoforte " + specifier;
}

std::string Pianoforte::getMateriale() const {
	return (pianoKeys == ivory)
}
