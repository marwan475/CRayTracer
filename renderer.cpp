#include <stdio.h>
#include <stdlib.h>
#include "vec3.h"
#include "ray.h"
#include "camera.h"
#include <windows.h>

const char WindowClassName[] = "Window"; 

camera* camp;

LRESULT CALLBACK WindowProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
  switch(msg){
       case WM_KEYDOWN:
              {

              if ((int)wParam == 87){
	        printf("W KEY PRESSED\n");
	      }

	      if ((int)wParam == 65){
                printf("A KEY PRESSED\n");
              }
 
	      if ((int)wParam == 83){
                printf("S KEY PRESSED\n");
              }

	      if ((int)wParam == 68){
                printf("D KEY PRESSED\n");
              }

	      if ((int)wParam == 38){
                printf("UP KEY PRESSED\n");
              }

	      if ((int)wParam == 40){
                printf("DOWN KEY PRESSED\n");
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
  double viewport_h = 2.0;
  double focal_length = 1.0;
      
  int height = int(width/aspect_ratio);

  HWND hWindow = CreateWindowEx(
		    WS_EX_CLIENTEDGE, 
		    WindowClassName, // name of our window class
		    "test", // title for our window
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
  
  obj_list scene;

  scene.add(make_shared<Sphere>(vec3(0,0,-1), 0.5));
  scene.add(make_shared<Sphere>(vec3(0,-100.5,-1), 100));

  camera cam = camera(hWindow,aspect_ratio,width,viewport_h,focal_length,vec3(0,0,0));

  cam.render(scene);

  while(GetMessage(&msg,NULL,0,0) > 0){ 
      TranslateMessage(&msg);
      DispatchMessage(&msg); //send msg to window
  }


  return 0;
}
