#include <stdio.h>
#include <stdlib.h>
#include "vec3.h"
#include "ray.h"
#include "camera.h"
#include <windows.h>

const char WindowClassName[] = "Window"; 

LRESULT CALLBACK WindowProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
  return DefWindowProc(hwnd, msg, wParam, lParam);
}

// main function for renderer
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
  // window creation
  int rtrc; 

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

  HWND hWindow = CreateWindowEx(
		    WS_EX_CLIENTEDGE, 
		    WindowClassName, // name of our window class
		    "test", // title for our window
		    WS_OVERLAPPEDWINDOW, 
		    CW_USEDEFAULT, // X cord of window
		    CW_USEDEFAULT, // Y cor dof window
		    1600, //width
		    1000, //height
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
  
  obj_list scene;

  scene.add(make_shared<Sphere>(vec3(0,0,-1), 0.5));
  scene.add(make_shared<Sphere>(vec3(0,-100.5,-1), 100));

  camera cam = camera(16.0/9.0,400,2.0,1.0,vec3(0,0,0));

  cam.render(scene);


  return 0;
}
