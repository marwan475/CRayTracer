#include <stdio.h>
#include <stdlib.h>

// main function for renderer
int main(){
  
  int i;
  int j;

  // rgb values;
  int r;
  int g;
  int b;

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
      r = i;
      g = j;
      b = (i + j)/2;

      //rgb values of each pixel in ppm format
      printf("%d %d %d\n",r,g,b);
    } 
  }

  fprintf(stderr,"\nComplete");


  return 0;
}
