#include "prodotto.h"

Prodotto::Prodotto(std::string _nome, double _kcal, double _prezzo):
	nome(_nome), kcal(_kcal), prezzo(_prezzo) {}

Prodotto::Prodotto():
	kcal(0), prezzo(0){}
