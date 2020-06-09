#include "inputexception.h"

inputException::inputException(QString  e):
    errore(e)
{
}

QString inputException::getErrore() const{
    return errore;
}
