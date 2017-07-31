#include <QtWidgets>
#include "dotcanvas.h"

class MirasolWidget: public QMainWindow
{
  Q_OBJECT
public:
  DotCanvas *dotcanvas;
  QToolBar *toolbar;
  MirasolWidget(QWidget *parent=0);
public slots:
  void setnumber(int num);
  void setnumber(const QString &newtext);
private:
  int numDots;
};
