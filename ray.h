#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray {
  public:
    ray(vec3& origin,vec3& direction)
    {
      oirgin = SmultiVector(1,origin);
      direction = SmultiVector(1,direction);
    }

    vec3 org()
    {
      return origin;
    }

    vec3 dir()
    {
      return direction;
    }

    vec3 get(double n)
    {
      return addVectors(origin,SmultiVector(n,direction));
    }

  private:
    // orgin point of ray [x,y,z]
    vec3 origin;
    
    // direction of ray [x,y,z]
    vec3 direction;

}

#endif
