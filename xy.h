
#ifndef XY_H
#define XY_H
class xy
{
public:
  xy(double e,double n);
  xy();
  double getx() const;
  double gety() const;
  double length() const;
  bool isfinite() const;
  bool isnan() const;
  void _roscat(xy tfrom,int ro,double sca,xy cis,xy tto);
  virtual void roscat(xy tfrom,int ro,double sca,xy tto); // rotate, scale, translate
  friend xy operator+(const xy &l,const xy &r);
  friend xy operator+=(xy &l,const xy &r);
  friend xy operator-(const xy &l,const xy &r);
  friend xy operator-(const xy &r);
  friend xy operator*(const xy &l,double r);
  friend xy operator*(double l,const xy &r);
  friend xy operator/(const xy &l,double r);
  friend xy operator/=(xy &l,double r);
  friend bool operator!=(const xy &l,const xy &r);
  friend bool operator==(const xy &l,const xy &r);
  friend xy turn90(xy a);
  friend xy turn(xy a,int angle);
  friend double dist(xy a,xy b);
  friend int dir(xy a,xy b);
  friend double dot(xy a,xy b);
  friend double area3(xy a,xy b,xy c);
protected:
  double x,y;
};
#endif
