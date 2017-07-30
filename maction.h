#include <QtWidgets>

class MirasolAction: public QAction
{
  Q_OBJECT
public:
  MirasolAction(QObject *parent=nullptr,int kind=0);
  void activate(ActionEvent event);
public slots:
  void setKind(int kind); // sets checked if kind matches myKind
  void setNumber(int num); // sets enabled if num is my kind of number
signals:
  void kindChanged(int kind); // emitted on activate(triggered)
private:
  int myKind;
};
