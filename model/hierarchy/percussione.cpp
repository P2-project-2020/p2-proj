#include "percussione.h"
const QString Percussione::json_tuned = "intonato";
Percussione::Percussione(bool _tuned):
     tuned(_tuned){}

void Percussione::loadData(const QJsonObject& obj){
     Strumento::loadData(obj);

     const QJsonValue& valTuned = obj[json_tuned];
     if(!valTuned.isUndefined() && valTuned.isBool())
	  tuned = valTuned.toBool();
}

void Percussione::saveData(QJsonObject& obj) const {
     Strumento::saveData(obj);

     obj[json_tuned] = tuned;
}

bool Percussione::operator==(const Percussione& other) const {
     return
	  Strumento::operator==(other) &&
	  tuned == other.tuned;
}

bool Percussione::operator!=(const Percussione& other) const {
     return !(*this == other);
}
