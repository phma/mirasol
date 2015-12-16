#include <QtWidgets>

class MirasolWidget: public QWidget
{
public:
  QLineEdit *inpline;
  QPushButton *button;
  MirasolWidget(QWidget *parent=0);
public slots:
  void setnumber(const QString &newtext);
};
