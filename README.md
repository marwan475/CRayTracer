# CRayTracer
Raytracer written in C++ to learn computer graphics

ppm file format source: https://netpbm.sourceforge.net/doc/ppm.html

3D vector source: https://www.nagwa.com/en/explainers/653193529121/

Current design:
- camera casts ray on each pixel in the viewport

- ray is checked to see if it has made contact with any objects

- color of the pixel is determined based on the normal vector of the ray and object

- if no object is hit the color of the pixel is based on the background
