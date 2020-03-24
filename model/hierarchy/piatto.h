#ifndef PIATTO_H
#define PIATTO_H
#include <iostream>
#include "prodotto.h"

enum categoria {vegetariano, vegano, normale};

class Piatto : virtual public Prodotto
{
private:
    categoria type;
    bool isCooked; //cooked = true, raw = false
    bool isSweet; //sweet = true, salty = false


public:
    Piatto(std::string = "", double = 0.0, double = 0.0, categoria = normale, bool = false, bool = false);
    categoria getCategoria() const;
    bool getIsCooked() const;
    bool getIsSweet() const;
};

#endif // PIATTO_H
