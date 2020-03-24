#ifndef BEVANDA_H
#define BEVANDA_H
#include "prodotto.h"
#include <string>

class Bevanda: public Prodotto{
	
	std::string brand;
	double volume;
	bool hot;
	bool frizzante;
	
public:

	Bevanda(const std::string& _brand, double _price, const std::string& _nome_generico_, );
	double percentualeAlcol() const;
};

#endif /* BEVANDA_H */
