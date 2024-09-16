#ifndef CAMERA_H
#define CAMERA_H

#include <limits>
#include "objects.h"
#include <windows.h>

using std::numeric_limits;

class camera {
  public:

    camera(HWND hwnd,double ar, int w,double vh,double fl,vec3 cc)
    {
      width = w;
      aspect_ratio = ar;
      
      height = int(width/aspect_ratio);

      viewport_h = vh;
      viewport_w = viewport_h*(double(width)/double(height));

      focal_length = fl;
      ccenter = cc;
 
      viewport_u = vec3(viewport_w,0,0); // horizontal vector of viewport
      viewport_v = vec3(0,-viewport_h,0); // negative vertical vector of viewport

      delta_u = SdivideVector(width,viewport_u); // change between pixels horizotanlly
      delta_v = SdivideVector(height,viewport_v);// change between pixels vertically

      vp_upperleft = subtractVectors(subtractVectors(subtractVectors(ccenter,vec3(0,0,focal_length)),SdivideVector(2,viewport_u)),SdivideVector(2,viewport_v));  

      pixel_location = addVectors(vp_upperleft,SmultiVector(0.5,addVectors(delta_u,delta_v)));

      hWindow = hwnd;

    }


    void render(obj_list scene)
    {
      int i;
      int j;      
      vec3 center;
      vec3 ray_direction;
      vec3 c;

      COLORREF rgb;

      HDC hWdc = GetDC(hWindow);
      
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
          c = ray_color(r,scene);
	  c = SmultiVector(255,c);

          //rgb values of each pixel in ppm format
          rgb = RGB(c.x(),c.y(),c.z());
	  SetPixel(hWdc,i,j,rgb);
       }
     }
     fprintf(stderr,"\nComplete");
    }

    // determines color of pixel that ray hits
    vec3 ray_color(ray r,obj_list scene)
    {
      obj_record rec;
      if (scene.contact(r,0,numeric_limits<double>::infinity(),&rec)){
        return SmultiVector(0.5,addVectors(rec.normalV,vec3(1,1,1)));
      }
  

      // Ray hit background	
      vec3 ud = unitVector(r.dir());
      double n = 0.7*(ud.y() + 1.0);
      return addVectors(SmultiVector(1.0-n,vec3(1.0,1.0,1.0)),SmultiVector(n,vec3(1.0,0.7,0.5)));
    }

  private:
    double aspect_ratio;
    int width;
    int height;
    double viewport_h;
    double viewport_w;
    double focal_length; // distance from camera to viewport
    vec3 ccenter; // camera center
    vec3 viewport_u; 
    vec3 viewport_v;

    // rate of change between pixels
    vec3 delta_u;
    vec3 delta_v;

    // upper left pixel location
    vec3 vp_upperleft;
    vec3 pixel_location;

    // handle to window
    HWND hWindow;

};

#endif
