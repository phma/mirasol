#include <QMainWindow>
#include <vector>
#include "dotcanvas.h"
#include "maction.h"

class MirasolWidget: public QMainWindow
{
  Q_OBJECT
public:
  DotCanvas *dotcanvas;
  QToolBar *toolbar;
  std::vector<MirasolAction *> actions;
  MirasolWidget(QWidget *parent=0);
  ~MirasolWidget();
  void makeActions();
  void unmakeActions();
signals:
  void numberChanged(int num);
  void kindChanged(int kind);
public slots:
  void setNumber(int num);
  void setNumber(const QString &newtext);
  void prepareSetKind(int kind);
  void setKind(bool checked);
private:
  int numDots;
  int maxNumDots;
  int kindDots;
  int preKindDots; // set by one signal in preparation for another signal, which has no argument
  DotPixmap *pixmap;
};
