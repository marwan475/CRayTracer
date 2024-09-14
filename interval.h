#ifndef INTERVAL_H
#define INTERVAL_H

class interval {
  public:
    double  min,max;

    interval(double mn,double mx)
    {
      min = mn;
      max = mx;
    }

    double size()
    {
      return max - min;
    }

    bool contains(double x)
    {
      return min <= x && x <= max;
    }

    bool surrounds(double x) const {
        return min < x && x < max;
    }
}

#endif
