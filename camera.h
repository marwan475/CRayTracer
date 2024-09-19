#ifndef CAMERA_H
#define CAMERA_H

#include <limits>
#include "objects.h"
#include <windows.h>
#include "utility.h"

using std::numeric_limits;

class camera {
  public:

    camera(HWND hwnd,double ar, int w,double fv,int samp,int tt,int depth)
    {
      width = w;
      aspect_ratio = ar;
      
      height = int(width/aspect_ratio);

      fov = fv;
      double theta = degrees_to_radians(fov);
      h = std::tan(theta/2);

      ccenter = vec3(0,0,1);
      look = vec3(0,0,-1);
      vup = vec3(0,1,0);

      samples = samp;

      sample_scale = 1.0/samples;

      hWindow = hwnd;

      hWdc = GetDC(hWindow);

      type = tt;

      max_depth = depth;


    }

    void move(int mvcode)
    {
      switch(mvcode)
      {
        case 0: // w
          look.vec[1]++;
	  break;
	case 1: // a
	  ccenter.vec[0]--;
	  break;
	case 2: // s
          look.vec[1]--;
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
	case 6: // down
	  look.vec[0]--;
	  break;
	case 7: // down
	  look.vec[0]++;
	  break;
	      
      }

    }


    void render(obj_list scene)
    {
      int i;
      int j;      
      vec3 c = vec3(0,0,0);

      calc();
      
      for ( j = 0; j < height;j++){
        for (i = 0; i < width;i++){

	  if (type == 0){ 
	    ray r = get_ray(i,j);

            // color from current ray
            c = ray_color(r,scene);
	  }

	  if (type == 1){
	    for (int s = 0; s < samples; s++){
	      ray r = get_rayMAX(i,j);
	      c = addVectors(c,ray_colorMAX(r,scene,max_depth));

	    }
	    c = SmultiVector(sample_scale,c);
	  }

	  // displaying pixel
	  Display(c,i,j);
       }
     }
    }

    // gets ray basic
    ray get_ray(int i,int j)
    {
      // curent pixel
      vec3 center = addVectors(pixel_location,addVectors(SmultiVector(i,delta_u),SmultiVector(j,delta_v)));
      // ray diriciton to the current pixel
      vec3 ray_direction = subtractVectors(center,ccenter);

      // current ray
      return ray(ccenter,ray_direction);
    }

    // gets the ray of position [i,j] with MAX quality
    ray get_rayMAX(int i,int j)
    {
      vec3 offset = sample_square();
      
      vec3 pixel_sample = addVectors(pixel_location,addVectors(SmultiVector(i+offset.x(),delta_u),SmultiVector(j+offset.y(),delta_v)));
      
      vec3 ray_dir = subtractVectors(pixel_sample,ccenter);
      
      return ray(ccenter,ray_dir);      
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

    // determines color of pixel that ray hits MAX Quality
    vec3 ray_colorMAX(ray r,obj_list scene,int depth)
    {
      if (depth <=0) return vec3(0,0,0);

      obj_record rec;
      if (scene.contact(r,0.001,numeric_limits<double>::infinity(),&rec)){
        vec3 dir = addVectors(rec.normalV,randUvec());
	return SmultiVector(0.5,ray_colorMAX(ray(rec.point,dir),scene,depth-1));
      }


      // Ray hit background
      vec3 ud = unitVector(r.dir());
      double n = 0.7*(ud.y() + 1.0);
      return addVectors(SmultiVector(1.0-n,vec3(1.0,1.0,1.0)),SmultiVector(n,vec3(1.0,0.7,0.5)));
    }

    // displays pixel
    void Display(vec3 c,int i,int j)
    {
      COLORREF rgb;

      

      int rb = int(255 * clamp(linear_to_gamma(c.x()),0.0000,0.9999));
      int gb = int(255 * clamp(linear_to_gamma(c.y()),0.0000,0.9999));
      int bb = int(255 * clamp(linear_to_gamma(c.z()),0.0000,0.9999));

      rgb = RGB(rb,gb,bb);
      SetPixel(hWdc,i,j,rgb);
    }

    // changes render type MAX graphics or LOW
    void change(int t)
    {
      type = t;
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
    int samples;
    double sample_scale;
    int max_depth;

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
    HDC hWdc;

    int type;

    void calc()
    {
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
    }

};

#endif
