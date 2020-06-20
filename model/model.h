#ifndef MODEL_H
#define MODEL_H

#include "hierarchy/strumento.h"
#include "container.h"

/* Model rappresenta la classe che gestisce l'interazione tra la gerarchia ( o modello di dati )
e il resto dell'applicazione */

class Model
{

private:
    Container<Strumento*>* magazzino;
    Container<Strumento*>* carrello;
    bool saved;
public:
    Model();
    ~Model();

// Pusha su list e sulla rispettiva lista in base al tipo
    void magazzino_push_end(Strumento*);
    void carrello_push_end(Strumento*);

//Ritorna elemento in un Container sulla base di un indice
    Strumento* magazzinoAt(unsigned int =0);
    Strumento* carrelloAt(unsigned int =0);
//Ritorna elemento in un Container sulla base di un indice

    /*Iteratori sui contenitori del model */
    Container<Strumento*>::iterator magazzino_begin();
    Container<Strumento*>::iterator magazzino_end();
    Container<Strumento*>::iterator carrello_begin();
    Container<Strumento*>::iterator carrello_end();
    Container<Strumento*>::const_iterator magazzino_cbegin() const;
    Container<Strumento*>::const_iterator magazzino_cend() const;
    Container<Strumento*>::const_iterator carrello_cbegin() const;
    Container<Strumento*>::const_iterator carrello_cend() const;
    /*Iteratori sui contenitori del model */



//Cancellazione singola o multipla
    void eraseMagazzino(unsigned int);
    void eraseCarrello(unsigned int);
    void eraseMagazzino(unsigned int, unsigned int);
    void eraseCarrello(unsigned int, unsigned int);
//Cancellazione singola o multipla

    //Svuotano completamente i Container
    void resetMagazzino();
    void resetCarrello();
    //Svuotano completamente i Container

/* Salvataggio e caricamento dati dell'applicazione */
    void serializeData(QJsonObject&);
    bool unserializeData(const QJsonObject&);

    bool isDataSaved() const;
    void setDataSaved(bool);

    unsigned int getMagazzinoSize() const;
    unsigned int getCarrelloSize() const;


};

#endif // MODEL_H
