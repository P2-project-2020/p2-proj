#include "drink.h"

Drink::Drink(const std::string& _nome, double _prezzo, double _grado, double _zucchero):
	Bevanda(_nome,_prezzo),
	Alcolico(_grado),
	Analcolico(_zucchero)
{}

double Drink::percentualeAlcol() const {
	return percentualeParteAlcolica * Alcolico::percentualeAlcol();
}

std::string Drink::getNome() const {
	return Bevanda::getNome();
}

std::string Drink::dettaglio() const {
	return "Drink composto da:\n" + Alcolico::dettaglio() + "\n" + Analcolico::dettaglio();
}

double Drink::getPrezzo() const {
	return Bevanda::getPrezzo() > 0 ?
		Bevanda::getPrezzo() :
		(percentualeParteAlcolica * Alcolico::getPrezzo() +
		 percentualeParteAlcolica * Analcolico::getPrezzo());
}
