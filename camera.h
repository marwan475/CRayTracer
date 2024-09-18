#ifndef CAMERA_H
#define CAMERA_H

#include <limits>
#include "objects.h"
#include <windows.h>
#include "utility.h"

using std::numeric_limits;

class camera {
  public:

    camera(HWND hwnd,double ar, int w,double fv)
    {
      width = w;
      aspect_ratio = ar;
      
      height = int(width/aspect_ratio);

      fov = fv;
      double theta = degrees_to_radians(fov);
      h = std::tan(theta/2);

      ccenter = vec3(-2,2,1);
      look = vec3(0,0,-1);
      vup = vec3(0,1,0);

      focal_length = subtractVectors(ccenter,look).length();

      viewport_h = 2*h*focal_length;
      viewport_w = viewport_h*(double(width)/double(height));

      dw = unitVector(subtractVectors(ccenter,look));
      du = unitVector(crossproduct(vup,dw));
      dv = crossproduct(dw,du);
 
      viewport_u = SmultiVector(viewport_w,du);
      viewport_v = SmultiVector(viewport_h,SmultiVector(-1,dv)); 

      delta_u = SdivideVector(width,viewport_u); // change between pixels horizotanlly
      delta_v = SdivideVector(height,viewport_v);// change between pixels vertically

      vp_upperleft = subtractVectors(subtractVectors(subtractVectors(ccenter,SmultiVector(focal_length,dw)),SdivideVector(2,viewport_u)),SdivideVector(2,viewport_v));  

      pixel_location = addVectors(vp_upperleft,SmultiVector(0.5,addVectors(delta_u,delta_v)));

      hWindow = hwnd;

      check = 0;


    }

    void move(int mvcode)
    {
      switch(mvcode)
      {
        case 0: // w
          ccenter.vec[2]--;
	  break;
	case 1: // a
	  ccenter.vec[0]--;
	  break;
	case 2: // s
          ccenter.vec[2]++;
	  break;
        case 3: // d
	  ccenter.vec[0]++;
	  break;
	case 4: // up
          ccenter.vec[1]++;
	  break;
	case 5: // down
	  ccenter.vec[1]--;
	  break;
	      
      }
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
	if (check==0){
          fprintf(stderr,"\rRendering %f percent complete",(double(j)/double(height))*100);
          fflush(stderr);
	}
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
     check++;
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
    double fov;
    double h;

    vec3 look;
    vec3 vup;
    vec3 du,dv,dw;

    // rate of change between pixels
    vec3 delta_u;
    vec3 delta_v;

    // upper left pixel location
    vec3 vp_upperleft;
    vec3 pixel_location;

    // handle to window
    HWND hWindow;

    int check;

};

#endif
