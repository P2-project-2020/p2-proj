#ifndef INPUTEXCEPTION_H
#define INPUTEXCEPTION_H


#include <QString>

class inputException
{
    QString  errore;
public:
    inputException(QString ="");

    QString getErrore() const;
};

#endif // INPUTEXCEPTION_H
