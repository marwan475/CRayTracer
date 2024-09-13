#ifndef OBJECTS_H
#define OBJECTS_H

#include "vec3.h"
#include "ray.h"

#include <vector>
#include <memory>

using namespace std;

typedef struct {
  
  vec3 point;
  vec3 normalV;
  double t;
  bool face;

} obj_record;

// sets the objects hit loaction record direction of normal vector
void set_face(ray r,vec3 normal,obj_record *record)
{
  record->face = dot(r.dir(),normal);
  
  if (record->face) record->normalV = normal;
  else record->normalV = SmultiVector(-1,normal);
}

class obj {
  public:
    virtual ~obj() = default;

    virtual bool contact(ray r,double tmin,double tmax,obj_record *record) const = 0;
};

class obj_list : public obj {
  public:
    vector<shared_ptr<obj>> objects;

    obj_list(){}
    
    void add(shared_ptr<obj> object) {objects.push_back(object);}

    void clear() {objects.clear();}

    bool contact(ray r,double tmin,double tmax,obj_record *record) const override
    {
      obj_record rec;
      bool cont = false;
      double closest = tmax;

      for ( auto o : objects) {
        if (o->contact(r,tmin,closest,&rec)){
	  cont = true;
	  closest = rec.t;
	  *record = rec;
	}
      } 

      return cont;
    }
};

class Sphere : public obj {
  public:
    Sphere(vec3 cent, double rad)
    {
      Scenter = cent;
      radius = rad;
    }

    bool contact(ray r, double tmin, double tmax,obj_record *record) const override
    {
      // Quadratic formula	    
      vec3 oc = subtractVectors(Scenter,r.org());
      double a = dot(r.dir(),r.dir());
      double b = dot(r.dir(),oc);
      double c = dot(oc,oc) - (radius*radius);
      double d = b*b - a*c; // discriminant
      double sd = sqrt(d);

      if (d < 0) return false; // no real solutions

      double rt = (b - sd) / a; // root
      if (rt <= tmin || tmax <= rt){
        rt = (b + sd) / a;
	if ( rt <= tmin || tmax <= rt) return false;
      } 

      record->t = rt;
      record->point = r.get(rt);
      vec3 normal = SdivideVector(radius,subtractVectors(record->point,Scenter));
      set_face(r,normal,record);

      return true;
    }
  private:
    vec3 Scenter;
    double radius;
};

#endif
