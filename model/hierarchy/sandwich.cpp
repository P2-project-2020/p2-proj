#include "sandwich.h"

Sandwich::Sandwich(std::string _nome, double _kcal, double _prezzo, categoria _type, bool _isCooked, bool _isSweet, size _sizeType, bool _isTramezzino):
    Piatto(_nome, _kcal, _prezzo, _type, _isCooked, _isSweet), sizeType(_sizeType), isTramezzino(_isTramezzino) {}

size Sandwich::getSizeType() const {
    return sizeType;
}

bool Sandwich::getIsTramezzino() const {
    return isTramezzino;
}
