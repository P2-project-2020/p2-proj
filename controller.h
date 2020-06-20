#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "view/inputexception.h"
#include "view/menu.h"
#include "view/QTableViews/Magazzino/magazzinoView.h"
#include "view/QTableViews/Carrello/carrelloView.h"
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
    carrelloView *Vcarrello;//Vista gestione carrello
    QBoxLayout *mainLayout;
    QHBoxLayout *headerLayout;
    QHBoxLayout *statusBar;//La statusBar inferiore che emula il comportamente della QStatusBar
    QLabel *itemCounter;//Mostra in tempo reale il numero di strumenti presenti
    QLabel *saveStatus;//Mostra in tempo reale lo stato dei dati ( salvati o meno)
    QString currentFile;//Il file di lavoro corrente
    QPushButton* loadSample;
    QPushButton* printTable;
    QPushButton* viewDetails;
public:
    Controller(Model*, QWidget * = nullptr);
    // Rileva il tentativo di chiusura della finestra, chiede se salvare i dati in caso essi non lo siano
    void closeEvent(QCloseEvent *event);
    QString getCurrentFile() const;
    void resetMagazzino();
    void resetCarrello();
    void printPdfTable(const QString);
public slots:
    void slotSave();
    void slotLoad();
    void slotLoadSample();
    void slotInserisci();
    void slotAddToCart();
    void slotUpdatePage();//Aggiorna statusBar e tabelle
    void slotDeleteMagazzinoItem();
    void slotDeleteCarrelloItem();
    void slotResetMagazzino();
    void slotResetCarrello();
    void slotResetTables();
    void slotDataChanged();
    void slotPrint();
    void slotViewDetails();
};
#endif // CONTROLLER_H
