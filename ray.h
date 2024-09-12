#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray {
  public:
    ray(vec3& origin,vec3& direction)
    {
      orig = SmultiVector(1,origin);
      dire = SmultiVector(1,direction);
    }

    vec3 org()
    {
      return orig;
    }

    vec3 dir()
    {
      return dire;
    }

    vec3 get(double n)
    {
      return addVectors(orig,SmultiVector(n,dire));
    }

  private:
    // orgin point of ray [x,y,z]
    vec3 orig;
    
    // direction of ray [x,y,z]
    vec3 dire;

};

#endif
