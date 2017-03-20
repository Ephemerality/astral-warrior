#ifndef GLPNG_H
#define GLPNG_H
#include <GL/glut.h>
#include <GL/gl.h>
#include <png.h>
GLuint png_texture_load(const char * file_name, int * width, int * height, GLuint texture);
#endif
