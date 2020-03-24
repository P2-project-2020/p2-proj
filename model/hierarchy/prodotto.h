#ifndef PRODOTTO_H
#define PRODOTTO_H
#include <string>

class Prodotto{
	
	std::string nome,
		descrizione,
		ingredienti,
		codice_prodotto;		// Questo penso abbia senso inizializzarlo con un metodo nel costruttore

	double kcal, prezzo;

	static void setCodice();	// per ora statico, pensavo di farlo in modo che "guardi" tutti i prodotti presenti o una cosa simile
	
public:
	Prodotto(const std::string& _nome, double _prezzo);
	virtual ~Prodotto() = default;
	
	/* Forse i metodi qua sotto andranno rivisti, potremmo pensare ad avere il menù come 
	   file (json o altro formato) che una volta parsato imposta questi campi */
	void setDescrizione(const std::string& desc);
	void setIngredienti(const std::string& ingr);

	/* Ha senso che sia virtuale puro perchè cosi per le bibite può ritornare la marca, 
	   mentre per i piatti solo il nome del piatto, nell'ottica di fare gli scontrini */ 
	virtual std::string getNome() const = 0; 
	/* anche in questo caso, magari non vogliamo che ritorni solo il prezzo nei figli
	   (tipo, coctail con limone: +50€ per il limone) */
	virtual double getPrezzo() const = 0;
	/* penso sempre agli scontrini dove mette "senza pane, formaggio, ecc" nei toast al mac donald*/
	virtual std::string dettaglio() const = 0;
};

#endif /* PRODOTTO_H */
