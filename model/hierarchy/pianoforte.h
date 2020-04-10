#pragma once
#include "percussione.h"
#include "corda.h"

class Pianoforte: public Corda, public Percussione{
public:
	enum Shape {grand, upright};
	enum Keys {wood, plastic, ivory};
	Pianoforte(Pianoforte::Shape, Pianoforte::Keys, double, const std::string&, bool = false, const std::string& = "");

	std::string className() const;
	Strumento::Tune tune() const { return undefined; }
	std::string getMaterial() const;

private:
	Shape pianoShape;
	Keys pianoKeys;
	static const unsigned int numberOfKeys;
};
