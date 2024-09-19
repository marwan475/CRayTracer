#ifndef UTILITY_H
#define UTILITY_H

#include <cmath>
#include <cstdlib>

const double pi = 3.1415926535897932385;

inline double degrees_to_radians(double degrees) 
{
    return degrees * pi / 180.0;
}

inline double random_double() 
{
    // Returns a random real in [0,1).
    return std::rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max) 
{
    // Returns a random real in [min,max).
    return min + (max-min)*random_double();
}

inline double clamp(double x,double min,double max)
{
  if (x < min) return min;
  if (x > max) return max;
  return x;
}

vec3 sample_square() 
{
  // Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
  return vec3(random_double() - 0.5, random_double() - 0.5, 0);
}

#endif
