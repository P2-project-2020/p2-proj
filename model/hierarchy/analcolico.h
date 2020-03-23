#ifndef ANALCOLICO_H
#define ANALCOLICO_H
#include "bevanda.h"

class Analcolico: virtual public Bevanda{
	double sugar; 			// che attributi mettere? buh
public:
	Analcolico(std::string _name, double _price, double sugar);
	Analcolico(std::string _name, std::string brand, double _price, double sugar);
};


#endif /* ANALCOLICO_H */
