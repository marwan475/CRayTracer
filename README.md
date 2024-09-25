# CRayTracer
Raytracer written in C++ to learn computer graphics

ppm file format source: https://netpbm.sourceforge.net/doc/ppm.html

3D vector source: https://www.nagwa.com/en/explainers/653193529121/

Current design:
- camera casts ray on each pixel in the viewport

- ray is checked to see if it has made contact with any objects

- color of the pixel is determined based on the normal vector of the ray and object

- if no object is hit the color of the pixel is based on the background

## Showcase

### Pre-rendered image

![alt text](https://github.com/marwan475/CRayTracer/blob/main/Raytracer%20images/Screenshot%202024-09-24%20205903.png?raw=true)

### Pre-rendered image after moving the camera

![alt text](https://github.com/marwan475/CRayTracer/blob/main/Raytracer%20images/Screenshot%202024-09-24%20205820.png?raw=true)

### Rendered image with pixel sample size of 100

![alt text](https://github.com/marwan475/CRayTracer/blob/main/Raytracer%20images/Screenshot%202024-09-24%20205750.png?raw=true)
