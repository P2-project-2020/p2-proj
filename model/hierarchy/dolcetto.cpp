#include "dolcetto.h"

Dolcetto::Dolcetto(std::string _nome, double _kcal, double _prezzo, categoria _type, bool _isCooked, bool _isSweet, bool _isBrioche, bool _hasFruits, bool _hasRipieno):
    Piatto(_nome, _kcal, _prezzo, _type, _isCooked, _isSweet), isBrioche(_isBrioche), hasFruits(_hasFruits), hasRipieno(_hasRipieno) {}

bool Dolcetto::getIsBrioche() const {
    return isBrioche;
}
bool Dolcetto::getHasFruits() const {
    return hasFruits;
}
bool Dolcetto::getHasRipieno() const {
    return hasRipieno;
}
