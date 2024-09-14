#include <stdio.h>
#include <stdlib.h>
#include "vec3.h"
#include "ray.h"
#include "camera.h"

// main function for renderer
int main(){

  // scene creation
  
  obj_list scene;

  scene.add(make_shared<Sphere>(vec3(0,0,-1), 0.5));
  scene.add(make_shared<Sphere>(vec3(0,-100.5,-1), 100));

  camera cam = camera(16.0/9.0,400,2.0,1.0,vec3(0,0,0));

  cam.render(scene);


  return 0;
}
