#pragma once

#include "corda.h"

class Basso: virtual public Corda{
public:
	enum bassType {electric, acoustic};
	static const std::map<Basso::bassType,std::string> bassTypes;
	
	Basso(bassType = electric, double = 0, const std::string& = "", const std::string& = "", bool = false, unsigned int = defaultStrings, bool = false);
	
	std::string className() const override;
	Strumento::Tune tune() const override { return undefined; }
	std::string getMaterial() const override { return "Legno"; }
    bassType getType() const;

	void loadData(const QJsonObject&) override;
	void saveData(QJsonObject&) const override;

protected:
	static bassType findType(const std::string&);
	static std::string typeToString(const bassType&);
	
private:
	bassType type;
	bool fretLess;
	
	static const unsigned int defaultStrings;
	static const QString json_type;
	static const QString json_fretless;
};
