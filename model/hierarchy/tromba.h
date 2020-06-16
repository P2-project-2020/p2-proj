#pragma once
#include "fiato.h"

class Tromba: public Fiato{
public:
     Tromba(Strumento::Tune = contralto, double = 0, const std::string& = "", int = 0, bool = false, const std::string& = "", unsigned int = 1);
     Strumento* clone() const;
     
     std::string className() const;
     
     void loadData(const QJsonObject&);
     void saveData(QJsonObject&) const;
};
