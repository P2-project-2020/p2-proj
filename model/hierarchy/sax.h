#pragma once
#include "fiato.h"

class Sax: public Fiato {
public:
	Sax(Strumento::Tune = soprano, double = 0, const std::string& = "", Fiato::Material = brass, bool = false);
	std::string className() const;
	void loadData(const QJsonObject&);
	void saveData(QJsonObject&) const;
};
