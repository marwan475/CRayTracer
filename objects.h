#ifndef OBJECTS_H
#define OBJECTS_H

#include "vec3.h"
#include "ray.h"
#include "utility.h"

#include <vector>
#include <memory>

using std::make_shared;
using std::shared_ptr;
using std::vector;

class material;

typedef struct {
  
  vec3 point;
  vec3 normalV;
  double t;
  bool face;
  shared_ptr<material> mat;

} obj_record;

// sets the objects hit loaction record direction of normal vector
void set_face(ray r,vec3 normal,obj_record *record)
{
  record->face = dot(r.dir(),normal) < 0;
  
  if (record->face) record->normalV = normal;
  else record->normalV = SmultiVector(-1,normal);
}

class obj {
  public:
    virtual ~obj() = default;

    virtual bool contact(ray r,double tmin,double tmax,obj_record *record) const = 0;
};

class material {
  public:
    virtual ~material() = default;

    virtual bool matCalc(ray r_in,obj_record rec,vec3* match, ray* scat) const
    {
      return false;
    }
};

class matte : public material {
  public:
    matte(vec3 c)
    {
      color = c;
    }
    
    bool matCalc(ray r_in,obj_record rec,vec3* match,ray* scat) const override
    {
      vec3 dir = addVectors(rec.normalV,randUvec());

      if (near_zero(dir)) dir = rec.normalV;

      *scat = ray(rec.point,dir);
      *match = color;
      return true;
    }

  private:
    vec3 color;
};

class metal : public material {
  public:
    metal(vec3 c)
    {
      color = c;
    }

    bool matCalc(ray r_in,obj_record rec,vec3* match,ray* scat)const override
    {
      vec3 ref = reflect(r_in.dir(),rec.normalV);
      *scat = ray(rec.point,ref);
      *match = color;
      return true;
    }

  private:
    vec3 color;
};

class glass : public material {
  public:
    glass(double ri)
    {
      refraction_i = ri;
    }

    bool matCalc(ray r_in,obj_record rec,vec3* match,ray* scat)const override
    {
      *match = vec3(1.0,1.0,1.0);
      double rid;

      if (rec.face) rid = 1.0/refraction_i;
      else rid = refraction_i;

      vec3 ud = unitVector(r_in.dir());
      double cos = std::fmin(dot(SmultiVector(-1.0,ud),rec.normalV),1.0);
      double sin = std::sqrt(1.0 - cos*cos);

      bool cref = rid * sin > 1.0;
      vec3 direction;

      if (cref || reflectance(cos,rid) > random_double()) direction = reflect(ud,rec.normalV);
      else direction = refract(ud,rec.normalV,rid);

      *scat = ray(rec.point,direction);
      return true;
    }

  private:
    double refraction_i;
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

class Sphere : public obj { public:
    Sphere(vec3 cent, double rad,shared_ptr<material> m)
    {
      Scenter = cent;
      radius = rad;
      mat = m;
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
      record->mat = mat;

      return true;
    }
  private:
    vec3 Scenter;
    double radius;
    shared_ptr<material> mat;
};

#endif
