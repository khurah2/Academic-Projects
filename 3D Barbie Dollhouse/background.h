#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "gl/glut.h"
#include <string>

// Global Varibales
extern GLubyte* l_texture;
extern BITMAPFILEHEADER fileheader;
extern BITMAPINFOHEADER infoheader;
extern RGBTRIPLE rgb;
extern GLuint texName;

// Function Declaration
void makeImage(const std::string fn);
void initializeImage();
void drawImage();

#endif


