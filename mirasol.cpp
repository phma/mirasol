#include <QtGui>
#include <QtWidgets>
#include "mwidget.h"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  MirasolWidget window;
  window.show();
  return app.exec();
}
