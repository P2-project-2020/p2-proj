#include "analcolico.h"

Analcolico::Analcolico(double _zucchero):
	Bevanda(), sugar(_zucchero){}

Analcolico::Analcolico(std::string _name, double _price, double _sugar):
	Bevanda(_name,_price,_sugar*sugarKcalPerGram), sugar(_sugar){}

Analcolico::Analcolico(std::string _name, std::string brand, double _price, double _sugar):
	Bevanda(_name,_brand,_price,_sugar*sugarKcalPerGram){} // vedere come gestire il brand

std::string Analcolico::getNome() const {
	return Bevanda::getNome(); // + Bevanda::getBrand()
}
std::string Analcolico::dettaglio() const {
	return Bevanda::dettaglio() + "\Zuccheri (g): " + std::to_string(sugar);
}

double Analcolico::getPrezzo() const {
	return Bevanda::getPrezzo(); // Chiamate di questo genere si possono togliere
}
