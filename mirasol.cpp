#include <QtGui>
#include <QtWidgets>

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  QWidget window;
  QLineEdit *inpline;
  QPushButton *button;
  window.resize(320,240);
  window.setWindowTitle(QApplication::translate("main", "Mirasol"));
  window.show();
  inpline=new QLineEdit(&window);
  inpline->show();
  button = new QPushButton(QApplication::translate("main", "Show number"), &window);
  button->move(216,0);
  button->show();
  return app.exec();
}
