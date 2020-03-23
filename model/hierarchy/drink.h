#ifndef DRINK_H
#define DRINK_H
#include "analcolico.h"
#include "alcolico.h"

class Drink: public Alcolico, public Analcolico {
public:
	Drink(std::string _name, Alcolico base1, Analcolico base2); // Non se se inserire anche il prezzo o fare in modo che di default venga calcolato in base alle quantità
	
}; 

#endif /* DRINK_H */
