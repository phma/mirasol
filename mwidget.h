#include <QtWidgets>
#include "dotcanvas.h"

class MirasolWidget: public QWidget
{
  Q_OBJECT
public:
  QLineEdit *inpline;
  QPushButton *button;
  DotCanvas *dotcanvas;
  MirasolWidget(QWidget *parent=0);
public slots:
  void setnumber(const QString &newtext);
};
