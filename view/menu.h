#ifndef MENU_H
#define MENU_H

#include <QMenuBar>
#include <QWidget>

class Menu : public QMenuBar
{  Q_OBJECT
    QWidget *parent;
    QMenu* menu ;
    QAction *nuovo;
    QAction *save;
    QAction *saveAs;
    QAction* load ;
    QAction* exit;
public:
    Menu(QWidget* p = nullptr);
    QMenu *getMenu() const;
    QAction *getSave() const;
    QAction *getSaveAs() const;
    QAction *getLoad() const;
    QAction *getExit() const;
};

#endif // View of Menu bar
