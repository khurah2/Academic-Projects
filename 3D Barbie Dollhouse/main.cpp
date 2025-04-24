/* Athabasca University

   Comp390 - Introduction to Computer Graphics

   Final Project

   Option 1

   @author: Hosty Khurana

   @Student ID: 3623176

   @date: 22nd March 2025

   Program Description: This interactive 3D scene presents a detailed Barbie dollhouse environment demonstrating 
            advanced OpenGL rendering techniques. The implementation features:

            - A dynamically textured background with three selectable views (day/night/classic) 
              rendered on properly UV-mapped quad surfaces

            - Four configurable light sources (top-left yellow, top-right red, bottom-left white, 
              and bottom-right blue by default) with adjustable colors (white/red/blue/yellow) and 
              controllable ambient/diffuse/specular components

            - Five composite 3D objects, each constructed from 5+ geometric primitives:
              * Dollhouse: Cube body with cone roof, sphere base, cube door, and torus peephole
              * Barbie doll: Sphere head, cone dress, cube body/arms, torus eyes, and cone nose/hat
              * Toy car: Cube chassis, octahedron top, torus wheels, sphere headlight, and cube exhaust
              * Tea set: Sphere tabletop, cube legs, teapot, cone sugar, and torus donut
              * Flower pot: Dodecahedron base, cube stems, sphere petals, torus centers, and cone leaves

            - Atmospheric fog effects with adjustable density (low/medium/high) and toggle control,
              creating depth-cueing for enhanced realism

            - Full interactive control through a right-click menu system allowing real-time adjustment
              of all lighting parameters, material properties (gold/silver/copper/neutral), background
              textures, and fog effects

   Program Routines:
                    initialize - Configures OpenGL states, lighting, and materials
                    
                    render - Draws all scene objects with hierarchical transformations
                    
                    display - Manages buffer clearing and camera positioning
                    
                    reshape - Handles viewport and projection matrix updates

                    main - Initializes GLUT, creates window, and registers callbacks

*/

#include "windows.h"
#include "gl/glut.h"
#include "math.h"
#include "menu.h"
#include "background.h"
#include "composite3dObjects.h"

// initialize - Sets up the OpenGL environment
void initialize() {
    // Set background color (will be overridden by texture)
    glClearColor(0.5, 0.7, 0.5, 0.0);

    // Enable depth testing for proper 3D rendering
    glEnable(GL_DEPTH_TEST);

    // Enable lighting system and all four light sources
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glEnable(GL_LIGHT3);

    // Configure light 0 (top-left, yellow by default)
    glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, yellow_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, yellow_light);

    // Configure light 1 (top-right, red by default)
    glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, red_light);
    glLightfv(GL_LIGHT1, GL_SPECULAR, red_light);

    // Configure light 2 (bottom-left, white by default)
    glLightfv(GL_LIGHT2, GL_POSITION, light_position2);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, white_light);
    glLightfv(GL_LIGHT2, GL_SPECULAR, white_light);

    // Configure light 3 (bottom-right, blue by default)
    glLightfv(GL_LIGHT3, GL_POSITION, light_position3);
    glLightfv(GL_LIGHT3, GL_DIFFUSE, blue_light);
    glLightfv(GL_LIGHT3, GL_SPECULAR, blue_light);

    // Set global ambient light level
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
}

// render - Draws all scene objects with proper positioning
void render() {
    // Draw background image (handles its own texture/enable states)
    glPushMatrix();
    drawImage();
    glPopMatrix();

    // Draw dollhouse (gray, scaled up, positioned back in scene)
    glColor3f(0.4, 0.4, 0.4);
    glPushMatrix();
    glTranslatef(0.0, 0.0, -5.0);  // Position toward back
    glScalef(2.0, 2.0, 2.0);       // Scale up size
    drawBarbieHouse();              // Render house composite object
    glPopMatrix();

    // Draw car (positioned left front)
    glPushMatrix();
    glTranslatef(-9.0, -2.5, 5.0); // Left side position
    drawCar();                      // Render car composite object
    glPopMatrix();

    // Draw flower pot (scaled down, positioned right front)
    glPushMatrix();
    glTranslatef(11.0, -5.5, -3.0); // Right side position
    glScalef(0.8, 0.8, 0.8);       // Scale down size
    drawFlowerPot();                // Render flower pot composite
    glPopMatrix();

    // Draw tea table (positioned center front)
    glPushMatrix();
    glTranslatef(-2.0, -9.0, 6.0); // Center front position
    drawTeaTable();                 // Render table composite
    glPopMatrix();

    // Draw Barbie doll (positioned right front)
    glPushMatrix();
    glTranslatef(6.0, -7.0, 6.0);  // Right front position
    drawBarbie();                   // Render doll composite
    glPopMatrix();
}

// display - Main rendering callback
void display(void) {
    // Clear color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Reset modelview matrix
    glLoadIdentity();

    // Set camera position (looking at origin from z=30)
    gluLookAt(0.0, 0.0, 30.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // Render all scene objects
    render();

    // Swap buffers for smooth animation
    glutSwapBuffers();
}

// reshape - Window resize callback
void reshape(int w, int h) {
    // Set viewport to entire window
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);

    // Set projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Define perspective frustum
    glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 40.0);

    // Return to modelview matrix mode
    glMatrixMode(GL_MODELVIEW);
}

// main - Program entry point
void main(int argc, char** argv) {
    // Initialize GLUT
    glutInit(&argc, argv);

    // Set display mode (double buffer, RGB, depth)
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    // Set window size and position
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);

    // Create window
    int windowHandle = glutCreateWindow("Assignment 3 - Program 1");
    glutSetWindow(windowHandle);

    // Initialize OpenGL settings
    initialize();

    // Create interactive menu system
    createMenu();

    // Load default background texture (day scene)
    makeImage("day.bmp");
    initializeImage();

    // Register callback functions
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    // Enter main event loop
    glutMainLoop();
}