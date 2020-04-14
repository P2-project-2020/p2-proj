#pragma once

#include "corda.h"

class Basso: virtual public Corda{
public:
	enum bassType {electric, acoustic};

	Basso(bassType, double, const std::string&, const std::string& = "", bool = false, unsigned int = defaultStrings, bool = false);
	
	std::string className() const override;
	Strumento::Tune tune() const override { return undefined; }
	std::string getMaterial() const override { return "Legno"; }

	void loadData(const QJsonObject&) override;
	void saveData(QJsonObject&) const override;
	
private:
	static const unsigned int defaultStrings;
	bassType type;
	bool fretLess;
};
