#pragma once

#include "corda.h"

class Basso: virtual public Corda{
public:
     enum bassType {electric, acoustic};
     static const std::map<Basso::bassType,std::string> bassTypes;
     
     Basso(bassType = electric, double = 0, const std::string& = "", const std::string& = "", bool = false, unsigned int = defaultStrings, bool = false, unsigned int = 1);
     Strumento* clone() const;
     
     std::string className() const override;
     Strumento::Tune tune() const override { return undefined; }
     std::string getMaterial() const override { return "Legno"; }
     bassType getType() const;

     void loadData(const QJsonObject&) override;
     void saveData(QJsonObject&) const override;
     
     static bassType findType(const std::string&);
     
private:
     bassType type;
     bool fretLess;
	
     static const unsigned int defaultStrings;
     static const QString json_type;
     static const QString json_fretless;
};
