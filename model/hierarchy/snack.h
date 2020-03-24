#ifndef SNACK_H
#define SNACK_H
#include "piatto.h"

class Snack : public Piatto
{
private:
    bool isConfezionato;

public:
    Snack(std::string = "", double = 0.0, double = 0.0, categoria = normale, bool = false, bool = false, bool = true);

    bool getIsConfezionato() const;
};

#endif // SNACK_H
