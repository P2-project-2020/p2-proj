#pragma once

#include "corda.h"

class Chitarra: public Corda{
public:
     enum guitarType {electric, acoustic, classic};
     static const std::map<Chitarra::guitarType, std::string> guitarTypes;
	
     Chitarra(Chitarra::guitarType = electric, double = 0, const std::string& = "", const std::string& = "", const std::string& = "", bool = false, unsigned int = defaultStrings, unsigned int = 1, const std::string& = "");
     Strumento* clone() const;
     
     std::string className() const;
     Strumento::Tune tune() const;
     std::string getMaterial() const { return "Legno"; }
     guitarType getType() const;
     
     void loadData(const QJsonObject&);
     void saveData(QJsonObject&) const;

     bool operator==(const Chitarra&) const;
     bool operator!=(const Chitarra&) const;

     static std::string typeToString(const guitarType&);
     static guitarType findType(const std::string&);
	
private:
     guitarType type;
     
     static const unsigned int defaultStrings;
     static const QString json_type;
     static const QString json_model;
};

