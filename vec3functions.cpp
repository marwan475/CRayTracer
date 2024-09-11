#include<"vec3.h".

// Prints out vector [x,y,z]
void printVector(FILE *stream,vec3 v)
{
  fprintf(stream,"[%f,%f,%f]",v.x(),v.y(),v.z());
}

// adds 2 vectors and returns a new one
vec3 addVectors(vec3 v1,vec3 v2)
{
  return vec3(v1.x() + v2.x(),v1.y() + v2.y(),v1.z() +v2.z());
}


