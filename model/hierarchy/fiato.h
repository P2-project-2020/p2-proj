#pragma once
#include "strumento.h"

class Fiato: virtual public Strumento{
public:
	enum Material {silver, brass, plastic};
	
protected:
	enum Mouthpiece {woodwind_mouthpiece, brass_mouthpiece};
	Material material;
	Tune instrumentTune;

public:
	Fiato(Material, Strumento::Tune, Mouthpiece);
	Strumento::Tune tune() const;
	std::string getMaterial() const;
private:
	Mouthpiece mouthpiece;
};
