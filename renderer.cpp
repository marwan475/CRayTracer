#include <stdio.h>
#include <stdlib.h>
#include "vec3.h"
#include "ray.h"
#include "camera.h"
#include <windows.h>


const char WindowClassName[] = "Window"; 

camera* camp;

obj_list scene;

LRESULT CALLBACK WindowProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
  switch(msg){
       case WM_KEYDOWN:
              {

              if ((int)wParam == 87){
	        (*camp).move(0);
	      }

	      if ((int)wParam == 65){
                (*camp).move(1);
              }
 
	      if ((int)wParam == 83){
                (*camp).move(2);
              }

	      if ((int)wParam == 68){
                (*camp).move(3);
              }

	      if ((int)wParam == 38){
                (*camp).move(4);
              }

	      if ((int)wParam == 40){
                (*camp).move(5);
              }

	      if ((int)wParam == 81){
	        (*camp).move(6);
	      }

	      if ((int)wParam == 69){
	        (*camp).move(7);
	      }

	      if ((int)wParam == 32){
	        (*camp).render(scene);
	      }

	      if ((int)wParam == 39){
	        (*camp).change(1);
	      }

	      if ((int)wParam == 37){
	        (*camp).change(0);
	      }

              break;
              }
      case WM_CLOSE:
	      DestroyWindow(hwnd);
	      break;
      case WM_DESTROY:
	      PostQuitMessage(0);
	      break;
      default:
	      return DefWindowProc(hwnd, msg, wParam, lParam);
    }


  return DefWindowProc(hwnd, msg, wParam, lParam);
}

// main function for renderer
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
  // window creation
  int rtrc;
  MSG msg; 

  WNDCLASSEX wc    = {0};  
  wc.cbSize        = sizeof(wc);
  wc.style         = CS_HREDRAW | CS_VREDRAW;
  wc.lpfnWndProc   = WindowProc;
  wc.hInstance     = hInstance;
  wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
  wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
  wc.lpszClassName = WindowClassName;
  
  //registering our window class
  rtrc = RegisterClassEx(&wc);

  if (!rtrc){
    fprintf(stderr,"Failed to register window class");
    return 0;
  }

  int width = 400;
  double aspect_ratio = 16.0/9.0;
  double fov = 90;
  int samples = 100;
  int type = 0;
  int max_depth = 50;
      
  int height = int(width/aspect_ratio);

  HWND hWindow = CreateWindowEx(
		    WS_EX_CLIENTEDGE, 
		    WindowClassName, // name of our window class
		    "Ray Tracer", // title for our window
		    WS_OVERLAPPEDWINDOW, 
		    CW_USEDEFAULT, // X cord of window
		    CW_USEDEFAULT, // Y cor dof window
		    width + 20, //width
		    height + 43, //height
		    NULL, 
		    NULL, 
		    hInstance, 
		    NULL 
		    );

  //Showing window on screen
  ShowWindow(hWindow,nCmdShow);
  //Updating the window
  UpdateWindow(hWindow);

  // scene creation

  // left sphere matte
  scene.add(make_shared<Sphere>(vec3(-2,0,-1), 0.5,make_shared<matte>(vec3(0.8,0.6,0.2))));

  // right sphere metal
  scene.add(make_shared<Sphere>(vec3(2,0,-3), 0.5,make_shared<metal>(vec3(0.8,0.8,0.8))));

  // middle sphere glass
  scene.add(make_shared<Sphere>(vec3(0,0,-2),0.4,make_shared<glass>(1.00/1.50)));

  // ground sphere
  scene.add(make_shared<Sphere>(vec3(0,-100.5,-1), 100,make_shared<matte>(vec3(0.8,0.8,0.0))));

  // type = 0  for normal render, type = 1 for antialaising
  camera cam = camera(hWindow,aspect_ratio,width,fov,samples,type,max_depth);

  camp = &cam;

  cam.render(scene);

  while(GetMessage(&msg,NULL,0,0) > 0){ 
      TranslateMessage(&msg);
      DispatchMessage(&msg); //send msg to window
  }


  return 0;
}
