#pragma once
#include "fiato.h"

class Tromba: public Fiato{
public:
	Tromba(Strumento::Tune = contralto, double = 0, const std::string& = "", Fiato::Material = brass, bool = false, const std::string& = "");
	std::string className() const;

	void loadData(const QJsonObject&);
	void saveData(QJsonObject&) const;
};
