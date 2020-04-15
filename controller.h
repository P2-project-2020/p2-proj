#ifndef CONTROLLER_H
#define CONTROLLER_H

//#include "View/inputexception.h"
#include "View/menu.h"
//#include "View/viewpiante.h"
//#include "View/viewshop.h"
//#include "View/viewinserisci.h"
#include "Model/model.h"
#include <QVBoxLayout>
#include <QStatusBar>



class Controller : public QWidget
{   Q_OBJECT
private:
    Menu *menuBar;
    Model *core;//Il modello contenente i dati
    //QTabWidget *pagine;
   // viewShop *Vshop;//Vista gestione shop
    //viewPiante *Vpiante;//Vista gestione piante
    //QBoxLayout *mainLayout;
    //QHBoxLayout *headerLayout;
    //QHBoxLayout *statusBar;//La statusBar inferiore che emula il comportamente della QStatusBar
    QLabel *itemCounter;//TMostra in tempo reale il numero di piante/prodotti presenti
    QLabel *saveStatus;//Mostra in tempo reale lo stato dei dati ( salvati o meno)
    QString currentFile;//Il file di lavoro corrente
public:
    Controller(Model*, QWidget * = nullptr);
    // Rileva il tentativo di chiusura della finestra, chiede se salvare i dati in caso essi non lo siano
    void closeEvent(QCloseEvent *event);
    QString getCurrentFile() const;
    void resetMagazzino();
    void resetCarrello();
public slots:
    void slotSave();
    void slotLoad();
    void slotInserisci();
    void slotUpdatePage();//Aggiorna statusBar e tabelle
    void slotDeleteProdotto();
    void slotDeletePianta();
    void slotResetProdotti();
    void slotResetPiante();
    void slotResetTables();
    void slotDataChanged();
};
#endif // CONTROLLER_H
