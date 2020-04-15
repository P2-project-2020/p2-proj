#include <QApplication>
#include "Model/model.h"
#include "controller.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Controller* c = new Controller(new Model());
    c->show();

    //a.setWindowIcon(QIcon(":/res/img/logo.ico"));

    return a.exec();
}
