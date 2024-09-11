#include <stdio.h>
#include <stdlib.h>
#include "vec3.h"

// main function for renderer
int main(){
  
  int i;
  int j;

  // rgb values;
  vec3 v;

  int width = 256;
  int height = 256;

  // ppm file header
  printf("P3\n%d %d\n255\n",width,height);

  // formating rgb
  for ( j = 0; j < height;j++){
    // progress tracker
    fprintf(stderr,"\rRendering %f percent complete",(double(j)/double(height))*100);
    fflush(stderr);
    for (i = 0; i < width;i++){
      v = vec3(255.99*(double(i)/width),255.99*(double(j)/height),0);
      printVector(stdout,v);
      //rgb values of each pixel in ppm format
    } 
  }

  fprintf(stderr,"\nComplete");


  return 0;
}
