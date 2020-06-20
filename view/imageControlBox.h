#pragma once

#include <QWidget>
#include <QLabel>
#include <QImage>
#include <QVBoxLayout>
#include <iostream>
#include "toolboxrow.h"
#include "imageView.h"

/**
  
   Questo è il widget principale, si occupa di chiamare ImageView e roolboxRow che invece gesticono 
   rispettivamente l'immagine e i controlli relativi.
   Può essere creato direttamente passandogli la path (assoluta) dell'immagine da mostrare.
   i metodi sono più o meno auto-esplicativi.
  
   - toolboxRow ::  si occupa di mostrare i dialoghi per settare l'immagine, ed emette (quando scelta) la path
   per la nuova immagine scelta, rimbalzata tramite `signal_setImage(const QString&)'.
  
   -  `slot_removeImage()' si occupa di rimuovere la preview, serve a notificare il controller che l'associazione
   oggetto-immagine va rotta. Va connesso con connect.

*/

class ImageControlBox : public QWidget{
     Q_OBJECT;

     ImageView* image;
     toolboxRow* toolbox;
     QVBoxLayout* layout;
     bool imageIsSet;
	
public:
     ImageControlBox(const QString& = "", QWidget* = Q_NULLPTR);
     ~ImageControlBox();
     bool setImage(const QString&);
     bool setPreviewSize(int,int);

signals:
     void signal_removeImage();
     void signal_setImage(const QString&);
								 
public slots:
     void slot_setImage(const QString&);
     void slot_removeImage();
};
