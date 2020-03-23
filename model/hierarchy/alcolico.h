#ifndef ALCOLICO_H
#define ALCOLICO_H

class Alcolico: virtual public Bevanda{
	float gradi
public:
	Alcolico(std::string _nome, double _prezzo, float _gradi);
};

#endif /* ALCOLICO_H */
