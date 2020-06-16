#pragma once
#include "strumento.h"

class Percussione: virtual public Strumento{
     static const QString json_tuned;
     bool tuned;					// intonato o no
public:
     Percussione(bool = false);

     void loadData(const QJsonObject&);
     void saveData(QJsonObject&) const;
     
     bool operator==(const Percussione&) const;
     bool operator!=(const Percussione&) const;
};
