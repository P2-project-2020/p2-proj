#pragma once
#include "arco.h"

class Violino: public Arco{
public:
	Violino(double, const std::string& = Strumento::lutherie, const std::string& = "", bool = false);

	std::string className() const;
	Strumento::Tune tune() const;
	std::string getMaterial() const { return "Legno"; }

	void loadData(const QJsonObject&);
	void saveData(QJsonObject&) const;
};
