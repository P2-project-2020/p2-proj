#include "piatto.h"

Piatto::Piatto(std::string _nome, double _kcal, double _prezzo, categoria _type, bool _isCooked, bool _isSweet):
    Prodotto(_nome, _kcal, _prezzo), type(_type), isCooked(_isCooked), isSweet(_isSweet) {}

categoria Piatto::getCategoria() const {
    return type;
}

bool Piatto::getIsCooked() const {
    return isCooked;
}

bool Piatto::getIsSweet() const {
    return isSweet;
}


