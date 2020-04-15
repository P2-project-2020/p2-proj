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

	void loadData(const QJsonObject& obj);
	void saveData(QJsonObject& obj) const;

private:
	Shape pianoShape;
	Keys pianoKeys;
	
	static const unsigned int numberOfKeys;
	static const std::vector<std::pair<Pianoforte::Shape, std::string>> shapes;
	static const std::vector<std::pair<Pianoforte::Keys, std::string>> keys;
	static const QString json_shape;
	static const QString json_keys;

	static std::string shapeToString(const Pianoforte::Shape&);
	static Pianoforte::Shape findShape(const std::string&);
	
	static std::string keysToString(const Pianoforte::Keys&);
	static Pianoforte::Keys findKeys(const std::string&);
};
