#ifndef VEC3_H
#define VEC3_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// 3d vector class
class vec3{
  public:
    double vec[3];

    vec3(){
      int i ;
      for (i = 0;i<3;i++){
        vec[i] = 0;
      }
    }

    vec3(double v1,double v2,double v3){
      vec[0] = v1;
      vec[1] = v2;
      vec[2] = v3;
    }

    // returns x position of vector
    double x(){
      return vec[0];
    } 

    // returns y position of vector
    double y(){
      return vec[1];
    }

    // returns z position of vector
    double z(){
      return vec[2];
    }

    // add vector
    void add_vector(vec3 v){
      vec[0] += v.x();
      vec[1] += v.y();
      vec[2] += v.z();
    }
    
    // scalar multiply vector
    void scalar_multiply(double n){
      vec[0] *= n;
      vec[1] *= n;
      vec[2] *= n;
    }

    // subtract vector
    void subtract_vector(vec3 v){
      vec[0] -= v.x();
      vec[1] -= v.y();
      vec[2] -= v.z();
    }

    // divide vector
    void scalar_divide(double n){
      vec[0] /= n;
      vec[1] /= n;
      vec[2] /= n;
    }

    // length/magnitude of vector
    double length(){
      return sqrt(vec[0]*vec[0] + vec[1]*vec[1] + vec[2]*vec[2]);
    }
};

void printVector(FILE *stream,vec3 v);
vec3 addVectors(vec3 v1,vec3 v2);
vec3 subtractVectors(vec3 v1,vec3 v2);
vec3 multiVectors(vec3 v1,vec3 v2);
vec3 SmultiVector(double s,vec3 v);
vec3 SdivideVector(double s,vec3 v);
double dot(vec3 v1,vec3 v2);
vec3 crossproduct(vec3 v1, vec3 v2);
vec3 unitVector(vec3 v);
vec3 reflect(vec3 v,vec3 u);
vec3 refract(vec3 uv,vec3 n,double et);

#endif
