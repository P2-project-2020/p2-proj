#pragma once
#include "fiato.h"

class Sax: public Fiato {
public:
     Sax(Strumento::Tune = soprano, double = 0, const std::string& = "", const std::string& = "", int = 0, bool = false, unsigned int = 1, const std::string& = "");
     Strumento* clone() const;
     
     std::string className() const;
     void loadData(const QJsonObject&);
     void saveData(QJsonObject&) const;

     bool operator==(const Sax&) const;
     bool operator!=(const Sax&) const;
};
