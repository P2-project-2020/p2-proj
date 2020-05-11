#ifndef CONTROLLER_H
#define CONTROLLER_H

//#include "view/inputexception.h"
#include "view/menu.h"
#include "view/magazzinoView.h"
#include "model/model.h"
#include <QVBoxLayout>
#include <QStatusBar>
#include <QLabel>
#include <QTabWidget>




class Controller : public QWidget
{   Q_OBJECT
private:
    Menu *menuBar;
    Model *core;//Il modello contenente i dati
    QTabWidget *pagine;
    magazzinoView *Vmagazzino;//Vista gestione magazzino
    // ordiniView *Vordini;//Vista gestione ordini
    // carrelloView *Vcarrello;//Vista gestione carrello
    QBoxLayout *mainLayout;
    QHBoxLayout *headerLayout;
    QHBoxLayout *statusBar;//La statusBar inferiore che emula il comportamente della QStatusBar
    QLabel *itemCounter;//TMostra in tempo reale il numero di piante/prodotti presenti
    QLabel *saveStatus;//Mostra in tempo reale lo stato dei dati ( salvati o meno)
    QString currentFile;//Il file di lavoro corrente
public:
    Controller(Model*, QWidget * = nullptr);
    // Rileva il tentativo di chiusura della finestra, chiede se salvare i dati in caso essi non lo siano
    //void closeEvent(QCloseEvent *event);
    QString getCurrentFile() const;
    void resetMagazzino();
    void resetCarrello();
    void resetOrdini();
public slots:
    //void slotSave();
    //void slotLoad();
   // void slotInserisci();
    void slotUpdatePage();//Aggiorna statusBar e tabelle
   // void slotDeleteMagazzinoItem();
   // void slotDeleteCarrelloItem();
   // void slotDeleteOrdiniItem();
    void slotResetMagazzino();
    void slotResetCarrello();
    void slotResetOrdini();
    //void slotResetTables();
    void slotDataChanged();
};
#endif // CONTROLLER_H
