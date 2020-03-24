#ifndef SANDWICH_H
#define SANDWICH_H
#include "piatto.h"

enum size {small, medium, big};

class Sandwich : public Piatto
{
private:
    size sizeType;
    bool isTramezzino; //se il panino è un tramezzino viene applicata una riduzione sul prezzo

public:
    Sandwich(std::string = "", double = 0.0, double = 0.0, categoria = normale, bool = false, bool = false, size = medium, bool = false);
    size getSizeType() const;
    bool getIsTramezzino() const;
};

#endif // SANDWICH_H
