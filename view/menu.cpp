#include "menu.h"

Menu::Menu(QWidget* p):
    parent(p),
    menu(new QMenu("File",this))
{
    nuovo = new QAction("Nuovo", menu);
         nuovo->setShortcut(Qt::CTRL | Qt::Key_N);
    load = new QAction("Carica", menu);
        load->setShortcut(Qt::CTRL | Qt::Key_O);
    save = new QAction("Salva", menu);
        save->setShortcut(Qt::CTRL | Qt::Key_S);
    saveAs = new QAction("Salva con nome", menu);
        saveAs->setShortcut(Qt::CTRL | Qt::SHIFT | Qt::Key_S);
    exit = new QAction("Esci", menu);
         exit->setShortcut(Qt::CTRL | Qt::Key_W);
    print = new QAction("Stampa", menu);

    // Setup
    addMenu(menu);
        menu->addAction(nuovo);
        menu->addAction(nuovo);
        menu->addAction(print);
        menu->addAction(save);
        menu->addAction(saveAs);
        menu->addAction(exit);

    connect(nuovo,SIGNAL(triggered()),parent, SLOT(slotResetTables()));
    connect(print,SIGNAL(triggered()),parent, SLOT(slotPrint()));
    connect(load,SIGNAL(triggered()),parent, SLOT(slotLoad()));
    connect(saveAs,SIGNAL(triggered()),parent,SLOT(slotSave()));
    connect(exit,SIGNAL(triggered()),parent,SLOT(close()));
    //Save su controller poiche' necessita del file corrente
}

QMenu* Menu::getMenu() const{
    return menu;
}

QAction *Menu::getSave() const{
    return save;
}

QAction *Menu::getSaveAs() const{
    return saveAs;
}

QAction *Menu::getPrint() const{
    return print;
}


QAction *Menu::getLoad() const{
    return load;
}

QAction *Menu::getExit() const{
    return exit;
}

