#include <QApplication>
#include <QDialog>
#include "ui_corda.h"
#include "corda.hpp"
int main(int argc, char *argv[])
{
QApplication app(argc, argv);
corda* ui = new corda;
ui->show();
return app.exec();
}
