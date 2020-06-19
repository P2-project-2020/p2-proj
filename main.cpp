#include <QApplication>
#include "model/model.h"
#include "controller.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Controller* c = new Controller(new Model());
    c->show();

    a.setWindowIcon(QIcon(":/images/res/logo.png"));

    return a.exec();
}
