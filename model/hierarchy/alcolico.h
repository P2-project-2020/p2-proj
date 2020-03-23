#ifndef ALCOLICO_H
#define ALCOLICO_H
#include "bevanda.h"

class Alcolico: virtual public Bevanda{
	float strength;
public:
	Alcolico(std::string _name, double _price, float _strength);
	Alcolico(std::string _name, std::string _brand, double _price, float _strength);
};

#endif /* ALCOLICO_H */
