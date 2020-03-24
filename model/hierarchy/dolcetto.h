#ifndef DOLCETTO_H
#define DOLCETTO_H
#include "piatto.h"

class Dolcetto : public Piatto
{
private:
    bool isBrioche; //riduzione prezzo se è brioche
    bool hasFruits; //informazione per ingrediente o info utili per filtraggio
    bool hasRipieno;
public:
    Dolcetto(std::string = "", double = 0.0, double = 0.0, categoria = normale, bool = false, bool = false, bool = true, bool = false, bool = false);
    bool getIsBrioche() const;
    bool getHasFruits() const;
    bool getHasRipieno() const;
};

#endif // DOLCETTO_H
