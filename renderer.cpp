#include <stdio.h>
#include <stdlib.h>
#include "vec3.h"
#include "ray.h"

// checks if ray hits a sphere (sphere center,sphere radius,ray)
double Sphere(vec3 Scenter,double radius,ray r)
{
  vec3 oc = subtractVectors(Scenter,r.org());
  double a = dot(r.dir(),r.dir());
  double b = -2.0*dot(r.dir(),oc);
  double c = dot(oc,oc) - (radius*radius);
  double d = b*b -4*a*c;
  
  if (d < 0) return -1.0;
  else return (-b - sqrt(d))/(2.0*a);
}

// determines color of pixel that ray hits
vec3 ray_color(ray r)
{
  // checks if ray hits a sphere	
  double n = Sphere(vec3(0,0,-1),0.5,r); 
  if ( n > 0.0){
    vec3 N = unitVector(addVectors(r.get(n),vec3(1,0,0)));
    return SmultiVector(0.5,addVectors(N,vec3(1,1,1)));
  }	

  // Ray hit background	
  vec3 ud = unitVector(r.dir());
  double a = 0.7*(ud.y() + 1.0);
  return addVectors(SmultiVector(1.0-a,vec3(1.0,1.0,1.0)),SmultiVector(a,vec3(1.0,0.7,0.5)));
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

  // what the camera sees
  double viewport_h = 2.0;
  double viewport_w = viewport_h*(double(width)/double(height));

  // distance camera to viewport
  double focal_length = 1.0;

  // camera location
  vec3 ccenter = vec3(0,0,0);

  // viewport vectors
  vec3 viewport_u = vec3(viewport_w,0,0); // horizontal vector of viewport
  vec3 viewport_v = vec3(0,-viewport_h,0); // negative vertical vector of viewport

  // delta vectors
  vec3 delta_u = SdivideVector(width,viewport_u); // change between pixels horizotanlly
  vec3 delta_v = SdivideVector(height,viewport_v);// change between pixels vertically

  // finding upper left pixel location, as image is rendered from the (0,0) location
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
      
      // curent pixel	    
      center = addVectors(pixel_location,addVectors(SmultiVector(i,delta_u),SmultiVector(j,delta_v)));
      // ray diriciton to the current pixel
      ray_direction = subtractVectors(center,ccenter);

      // current ray
      ray r = ray(ccenter,ray_direction);

      // color from current ray
      c = ray_color(r);

      //rgb values of each pixel in ppm format
      printVector(stdout,SmultiVector(255.99,c));
    } 
  }

  fprintf(stderr,"\nComplete");


  return 0;
}
