#pragma once
#include "percussione.h"
#include "corda.h"

class Pianoforte: public Corda, public Percussione{
public:
	enum Shape {grand, upright};
	enum Keys {wood, plastic, ivory};

	static const std::map<Pianoforte::Shape, std::string> shapes;
	static const std::map<Pianoforte::Keys, std::string> keys;

	static Pianoforte::Shape findShape(const std::string&);
	static Pianoforte::Keys findKeys(const std::string&);
	
	Pianoforte(Pianoforte::Shape = grand, Pianoforte::Keys = ivory, double = 0, const std::string& = "", bool = false, const std::string& = "");

	std::string className() const;
	Strumento::Tune tune() const { return undefined; }
	std::string getMaterial() const;

	void loadData(const QJsonObject& obj);
	void saveData(QJsonObject& obj) const;

private:
	Shape pianoShape;
	Keys pianoKeys;
	
	static const unsigned int numberOfKeys;
	
	static const QString json_shape;
	static const QString json_keys;
};
