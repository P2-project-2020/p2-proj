#ifndef ANALCOLICO_H
#define ANALCOLICO_H
#include "bevanda.h"

class Analcolico: virtual public Bevanda{
	double sugar; 			// che attributi mettere? buh
	static double sugarKcalPerGram;
public:
	Analcolico(double _zucchero);
	Analcolico(std::string _name, double _price, double sugar=0);
	Analcolico(std::string _name, std::string brand, double _price, double sugar);

	double percentualeAlcol() const { return 0; } // inline forse permette di ottimizzare?
	std::string getNome() const;
	std::string dettaglio() const;
	double getPrezzo() const;
	
};

double Analcolico::sugarKcalPerGram = 1000;


#endif /* ANALCOLICO_H */
