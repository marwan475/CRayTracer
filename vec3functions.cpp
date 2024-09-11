#include "vec3.h"

// Prints out vector [x,y,z]
void printVector(FILE *stream,vec3& v)
{
  fprintf(stream,"%f %f %f\n",v.x(),v.y(),v.z());
}

// adds 2 vectors and returns a new one
vec3 addVectors(vec3& v1,vec3& v2)
{
  return vec3(v1.x() + v2.x(),v1.y() + v2.y(),v1.z() + v2.z());
}

// subtracts 2 vectors and returns a new one
vec3 subtractVectors(vec3& v1,vec3& v2)
{
  return vec3(v1.x() - v2.x(),v1.y() - v2.y(),v1.z() - v2.z());
}

// multiplys 2 vectors and returns a new one
vec3 multiVectors(vec3& v1,vec3& v2)
{
  return vec3(v1.x() * v2.x(),v1.y() * v2.y(),v1.z() * v2.z());
}

// scalar multiplys a vector and returns a new one
vec3 SmultiVector(double s,vec3& v)
{
  return vec3(s*v.x(),s*v.y(),s*v.z());
}

// scalar divides a vector and returns a new one
vec3 SdivideVector(double s,vec3& v)
{
  return vec3(v.x()/s,v.y()/s,v.z()/s);
}

// returns the dot product of 2 vectors
double dot(vec3& v1,vec3& v2) {
    return v1.x() * v2.x()
         + v1.y() * v2.y()
         + v1.z() * v2.z();
}

// returns crossproduct of 2 vectors
vec3 crossproduct(vec3& v1, vec3& v2) {
    return vec3(v1.y() * v2.z() - v1.z() * v2.y(),
                v1.z() * v2.x() - v1.x() * v2.z(),
                v1.x() * v2.y() - v1.y() * v2.x());
}

// returns unit vector of a vector
vec3 unitVector(vec3 v)
{
  return SdivideVector(v.length(),v);
}
