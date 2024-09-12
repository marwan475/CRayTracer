#include <stdio.h>
#include <stdlib.h>
#include "vec3.h"
#include "ray.h"

vec3 ray_color(ray r)
{
  vec3 ud = unitVector(r.dir());
  double a = 0.5*(ud.y() + 1.0);
  return SmultiVector(255.99,addVectors(SmultiVector(1.0-a,vec3(1.0,1.0,1.0)),SmultiVector(a,vec3(0.5,0.7,1.0))));
}

// main function for renderer
int main(){
  
  int i;
  int j;

  vec3 center;
  vec3 ray_direction;

  vec3 c;

  // image dimensions
  double aspect_ratio = 16.0/9.0;

  int width = 400;
  int height = int(width/aspect_ratio);

  // Camera
  double viewport_h = 2.0;
  double viewport_w = viewport_h*(double(width)/double(height));

  double focal_length = 1.0;

  vec3 ccenter = vec3(0,0,0);

  // viewport vectors
  vec3 viewport_u = vec3(viewport_w,0,0);
  vec3 viewport_v = vec3(0,-viewport_h,0);

  // delta vectors
  vec3 delta_u = SdivideVector(width,viewport_u);
  vec3 delta_v = SdivideVector(height,viewport_v);

  // finding view port upper left pixel on image

  vec3 vp_upperleft = subtractVectors(subtractVectors(subtractVectors(ccenter,vec3(0,0,focal_length)),SdivideVector(2,viewport_u)),SdivideVector(2,viewport_v));  

  vec3 pixel_location = addVectors(vp_upperleft,SmultiVector(0.5,addVectors(delta_u,delta_v)));

  // ppm file header
  printf("P3\n%d %d\n255\n",width,height);

  // formating rgb
  for ( j = 0; j < height;j++){
    // progress tracker
    fprintf(stderr,"\rRendering %f percent complete",(double(j)/double(height))*100);
    fflush(stderr);
    for (i = 0; i < width;i++){
      center = addVectors(pixel_location,addVectors(SmultiVector(i,delta_u),SmultiVector(j,delta_v)));
      ray_direction = subtractVectors(center,ccenter);

      ray r = ray(ccenter,ray_direction);

      c = ray_color(r);

      //rgb values of each pixel in ppm format
      printVector(stdout,c);
    } 
  }

  fprintf(stderr,"\nComplete");


  return 0;
}
