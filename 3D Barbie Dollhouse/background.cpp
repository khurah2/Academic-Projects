/* Athabasca University

   Comp390 - Introduction to Computer Graphics

   Final Project

   Option 1

   @author: Hosty Khurana

   @Student ID: 3623176

   @date: 22nd March 2025

   Purpose: This file implements background texture loading and rendering functionality for OpenGL. It provides functions to load BMP image files,
   convert them to OpenGL textures, and display them as a background quad. The implementation handles texture memory allocation, OpenGL texture
   parameter configuration, and proper lighting/texturing state management during rendering.

   File Routines:
                makeImage - Loads a BMP image file from disk, reads its pixel data, and converts it to RGBA format suitable for OpenGL texturing.

                initializeImage - Initializes OpenGL texture objects with the loaded image data, setting appropriate texture parameters including
                wrapping modes and filtering.

                drawImage - Renders the textured background as a full-screen quad at a fixed depth, managing texture and lighting states to ensure
                proper integration with the rest of the scene.

*/

#include "background.h"
#include <iostream>
#include <fstream>

// Global variables for texture handling
GLubyte* l_texture;          // Pointer to store texture data
BITMAPFILEHEADER fileheader;  // Structure for BMP file header
BITMAPINFOHEADER infoheader;  // Structure for BMP info header
RGBTRIPLE rgb;               // Structure to hold RGB values of a pixel
GLuint texName;              // Texture name/id for OpenGL

using namespace std;

// Function to load and process an image file
void makeImage(std::string fn) {
    int i, j = 0;
    FILE* l_file;
    const char* filename = fn.c_str();  // Convert filename to C-style string

    // Open image file in binary read mode
    fopen_s(&l_file, filename, "rb");
    if (l_file == NULL) return;  // Exit if file couldn't be opened

    // Read BMP file header and info header
    fread(&fileheader, sizeof(fileheader), 1, l_file);
    fseek(l_file, sizeof(fileheader), SEEK_SET);
    fread(&infoheader, sizeof(infoheader), 1, l_file);

    // Allocate memory for texture data (4 bytes per pixel: RGBA)
    l_texture = (GLubyte*)malloc(infoheader.biWidth * infoheader.biHeight * 4);
    memset(l_texture, 0, infoheader.biWidth * infoheader.biHeight * 4);

    // Read pixel data from BMP file and convert to RGBA format
    j = 0;
    for (i = 0; i < infoheader.biWidth * infoheader.biHeight; i++) {
        fread(&rgb, sizeof(rgb), 1, l_file);  // Read RGB triplet from file

        // Store RGBA values in texture array
        l_texture[j + 0] = (GLubyte)rgb.rgbtRed;    // Red component
        l_texture[j + 1] = (GLubyte)rgb.rgbtGreen;  // Green component
        l_texture[j + 2] = (GLubyte)rgb.rgbtBlue;   // Blue component
        l_texture[j + 3] = (GLubyte)255;            // Alpha value (fully opaque)
        j += 4;  // Move to next pixel position in texture array
    }

    fclose(l_file);  // Close the file
}

// Function to initialize OpenGL texture with the loaded image
void initializeImage() {
    // Set pixel storage mode
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // Generate and bind a texture object
    glGenTextures(1, &texName);
    glBindTexture(GL_TEXTURE_2D, texName);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    // Create the texture from the loaded image data
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
        infoheader.biWidth, infoheader.biHeight,
        0, GL_RGBA, GL_UNSIGNED_BYTE,
        l_texture);
}

// Function to draw the textured background quad
void drawImage() {
    // Disable lighting for background and enable texturing
    glDisable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texName);

    // Draw a quad with texture coordinates
    glBegin(GL_QUADS);
    glTexCoord2d(0.0, 0.0); glVertex3f(-25.0, -25.0, -5.0);  // Bottom-left
    glTexCoord2d(0.0, 1.0); glVertex3f(-25.0, 25.0, -5.0);   // Top-left
    glTexCoord2d(1.0, 1.0); glVertex3f(25.0, 25.0, -5.0);    // Top-right
    glTexCoord2d(1.0, 0.0); glVertex3f(25.0, -25.0, -5.0);   // Bottom-right
    glEnd();

    // Clean up - disable texturing and re-enable lighting
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
}