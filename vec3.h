#ifndef VEC3_H
#define VEC3_H

#include <stdio.h>
#include <stdlib.h>

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
    void add_vector(vec3& v){
      vec3[0] += v.e[0];
      vec3[1] += v.e[1];
      vec3[2] += v.e[2];
    }
    
    // scalar multiply vector
    void scalar_multiply(double n){
      vec3[0] *= n;
      vec3[1] *= n;
      vec3[2] *= n;
    }

    // subtract vector
    void subtract_vector(vec3& v){
      vec3[0] -= v.e[0];
      vec3[1] -= v.e[1];
      vec3[2] -= v.e[2];
    }

    // divide vector
    void scalar_divide(double n){
      vec3[0] /= n;
      vec3[1] /= n;
      vec3[2] /= n;
    }

    // length/magnitude of vector
    double length(){
      return sqrt(vec3[0]*vec3[0] + vec3[1]*vec3[1] + vec3[2]*vec3[2]);
    }
};

#endif
