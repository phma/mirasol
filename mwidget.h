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
public slots:
  void setnumber(int num);
  void setnumber(const QString &newtext);
private:
  int numDots;
  DotPixmap *pixmap;
};
