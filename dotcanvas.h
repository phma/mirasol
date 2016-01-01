#include <QtWidgets>
#include <vector>
#include "xy.h"

class DotCanvas: public QWidget
{
public:
  DotCanvas(QWidget *parent=0);
  void setPen(const QPen &qpen);
  void setBrush(const QBrush &qbrush);
public slots:
protected:
  void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
private:
  QPen pen;
  QBrush brush;
  std::vector<xy> dots;
};
