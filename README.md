# CRayTracer
Semi-real-time Ray tracer written in C++, only using base C libraries and Win32API for displaying to screen and keyboard input

## Features

- adding spheres to the scene
  - give location in 3d space
  - radius
  - material
- 3 different materials for spheres
  - matte
  - metal
  - glass
- moveable camera using keyboard inputs
- render in low-quality mode or high-quality mode

## Current design:
- camera casts ray on each pixel in the viewport

- ray is checked to see if it has made contact with any objects

- color of the pixel is determined based on the normal vector of the ray and object

- if no object is hit the color of the pixel is based on the background

## Future additions
- adding Quads instead of only spheres
- improving/optimizing the speed of rendering
  - Bounding Volume Hierarchies
  - Multithreaded rendering
  - GPU hardware acceleration using OpenCL
- Light sources
- Code documentation

## Settings

### Camera
- FOV
- Starting position
  
### Image
- width
- aspect ratio
- pixel sample size

*note (higher value for width and pixel sample size = higher quality image but also slower rendering time)

## Showcase

### Pre-rendered image

![alt text](https://github.com/marwan475/CRayTracer/blob/main/Raytracer%20images/Screenshot%202024-09-24%20205903.png?raw=true)

### Pre-rendered image after moving the camera

![alt text](https://github.com/marwan475/CRayTracer/blob/main/Raytracer%20images/Screenshot%202024-09-24%20205820.png?raw=true)

### Rendered image with pixel sample size of 100

![alt text](https://github.com/marwan475/CRayTracer/blob/main/Raytracer%20images/Screenshot%202024-09-24%20205750.png?raw=true)
