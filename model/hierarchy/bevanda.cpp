#include "bevanda.h"

Bevanda::Bevanda():
	Prodotto(), volume(0), hot(false), frizzante(false)
{}

Bevanda::Bevanda(const std::string& _nome, double prezzo, double _kcal):
	Prodotto(_nome,_kcal,prezzo), volume(0), hot(false), frizzante(false){}

bool Bevanda::isSuperalcolico() const {
	return percentualeAlcol() >= sogliaSuperalcolico;
}
