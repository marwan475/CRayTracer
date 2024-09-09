#include <stdio.h>
#include <stdlib.h>

// main function for renderer
int main(){
  
  int i;
  int j;

  // rgb values;
  double r;
  double g;
  double b;
  int ri;
  int gi;
  int bi;  

  int width = 256;
  int height = 256;

  printf("P3\n%d %d\n255\n",width,height);

  for ( j = 0; j < height;j++){
    for (i = 0; i < width;i++){
      r = double(i) / (width - 1);
      g = double(j) / (height -1);
      b = 0.0;

      ri = int(255.99 * r);
      gi = int(255.99 * g);
      bi = int(255.99 * b);

      printf("%d %d %d\n",ri,gi,bi);
    } 
  }


  return 0;
}
