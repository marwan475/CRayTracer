#ifndef OBJECTS_H
#define OBJECTS_H

#include "vec3.h"
#include "ray.h"

typedef struct {
  
  vec3 point;
  vec3 normalV;
  double t;

} obj_record;

class Sphere {
  public:
    Sphere(vec3 cent, double rad)
    {
      Scenter = cent;
      radius = rad;
    }

    bool contact(ray r, double tmin, double tmax,obj_record *record)
    {
      // Quadratic formula	    
      vec3 oc = subtractVectors(Scenter,r.org());
      double a = dot(r.dir(),r.dir());
      double b = dot(r.dir(),oc);
      double c = dot(oc,oc) - (radius*radius);
      double d = b*b - a*c; // discriminant
      double sd = sqrt(d);

      if (d < 0) return false; // no real solutions

      double r = (b - sd) / a; // root
      if (r <= tmin || tmax <= r){
        r = (b + sd) / a;
	if ( r <= tmin || tmax <= r) return false;
      } 

      record->t = root;
      record->point = r.get(r);
      record->normalV = SdivideVector(radius,subtractVectors(record->point,Scenter));

      return true;
    }
  private:
    vec3 Scenter;
    double radius;
}

#endif
