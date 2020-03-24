#include "snack.h"

Snack::Snack(std::string _nome, double _kcal, double _prezzo, categoria _type, bool _isCooked, bool _isSweet, bool _isConfezionato):
    Piatto(_nome, _kcal, _prezzo, _type, _isCooked, _isSweet), isConfezionato(_isConfezionato) {}

bool Snack::getIsConfezionato() const {
    return isConfezionato;
}
