#pragma once
#include "strumento.h"

class Arco: virtual public Strumento{ /* dato che ereditarietà
				       * virtuale e classe astratta il
				       * costruttore di strumento non
				       * verrà mai chiamato da lei */
     static const QString json_lutherie;
     bool lutherie;
public:
     Arco(bool = false);

     void saveData(QJsonObject&) const;
     void loadData(const QJsonObject&);

     bool isLutherie() const;

     bool operator==(const Arco&) const;
     bool operator!=(const Arco&) const;
};
