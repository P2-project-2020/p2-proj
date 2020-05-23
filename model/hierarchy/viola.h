#pragma once
#include "arco.h"

class Viola: public Arco{
	
	Strumento::Tune key;
	
public:
	
	Viola(double = 0, const std::string& = Strumento::lutherie, const std::string& = "", Strumento::Tune = contralto ,bool = false);

	std::string className() const;
	Strumento::Tune tune() const;
	std::string getMaterial() const { return "Legno"; }

	void loadData(const QJsonObject&);
	void saveData(QJsonObject&) const;
};
