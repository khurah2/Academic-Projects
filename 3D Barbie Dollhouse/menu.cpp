/* Athabasca University

   Comp390 - Introduction to Computer Graphics

   Final Project

   Option 1

   @author: Hosty Khurana

   @Student ID: 3623176

   @date: 22nd March 2025

   Purpose: Controls 3D scene lighting with 4 configurable lights, material properties (gold/silver/copper), background images, and fog 
   effects via right-click menu. Demonstrates OpenGL lighting concepts.

   File Routines:
                mainMenu - Handles the main menu quit operation
                
                light0_Operations - Controls the 0th light source
                
                light1_Operations - Controls the 1st light source
                
                light2_Operations - Controls the 2nd light source
                
                light3_Operations - Controls the 3rd light source
                
                materialPropertyOperations - Applies different material properties to objects
                
                backgroundMenu_Operations - Handles background image switching
                
                fogMenu_Operations - Controls fog effects
                
                fogIntensityMenu_Operations - Adjusts fog density
                
                createMenu - Sets up the complete menu hierarchy
*/

#include "menu.h"
#include "gl/glut.h"
#include <iostream>
#include "background.h"

// Light positions (x,y,z,w) - directional lights (w=0)
GLfloat light_position0[] = { -20.0, 10.0, 10.0, 0.0 }; // Top left light (yellow default)
GLfloat light_position1[] = { 20.0, 10.0, 10.0, 0.0 };  // Top right light (red default)
GLfloat light_position2[] = { -20.0, -10.0, 10.0, 0.0 }; // Bottom left light (white default)
GLfloat light_position3[] = { 20.0, -10.0, 10.0, 0.0 }; // Bottom right light (blue default)

// Light color definitions (RGBA values)
GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat red_light[] = { 1.0, 0.0, 0.0, 1.0 };
GLfloat blue_light[] = { 0.0, 0.0, 1.0, 1.0 };
GLfloat yellow_light[] = { 1.0, 1.0, 0.0, 1.0 };

// Global lighting parameters
GLfloat lmodel_ambient[] = { 0.1, 0.1, 0.1, 1.0 };  // Base ambient light level
GLfloat lmodel_diffuse[] = { 0.3, 0.3, 0.3, 1.0 };  // Base diffuse light level
GLfloat lmodel_specular[] = { 0.9, 0.9, 0.9, 1.0 }; // Base specular light level

// Fog effect parameters
GLfloat fogColor[] = { 0.6, 0.6, 0.6, 1.0 };       // Gray fog color

// Material property definitions (ambient, diffuse, specular, shininess)
// Gold material properties
GLfloat gold_ambient[] = { 0.24725, 0.1995, 0.0745, 1.0 };
GLfloat gold_diffuse[] = { 0.75164, 0.60648, 0.22658, 1.0 };
GLfloat gold_specular[] = { 0.628281, 0.555802, 0.366065, 1.0 };
GLfloat gold_shininess[] = { 51.2 };

// Copper material properties
GLfloat copper_ambient[] = { 0.2295, 0.08825, 0.0275, 1.0 };
GLfloat copper_diffuse[] = { 0.5508, 0.2118, 0.066, 1.0 };
GLfloat copper_specular[] = { 0.580594, 0.223257, 0.0695701, 1.0 };
GLfloat copper_shininess[] = { 51.2 };

// Silver material properties
GLfloat silver_ambient[] = { 0.19225, 0.19225, 0.19225, 1.0 };
GLfloat silver_diffuse[] = { 0.50754, 0.50754, 0.50754, 1.0 };
GLfloat silver_specular[] = { 0.508273, 0.508273, 0.508273, 1.0 };
GLfloat silver_shininess[] = { 51.2 };

// Neutral/default material properties
GLfloat neutral_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
GLfloat neutral_specular[] = { 0.1, 0.1, 0.1, 1.0 };
GLfloat neutral_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
GLfloat neutral_shininess[] = { 20.0 };

// Menu handles (IDs for menu items)
GLint light0Menu, light1Menu, light2Menu, light3Menu;  // Individual light control menus
GLint materialProperties, lightMenu;                   // Material and light main menus
GLint backgroundMenu, fogMenu, fogIntensityMenu;       // Background and fog effect menus

// Main menu callback - handles quit operation
void mainMenu(GLint option) {
    if (option == 0) {
        exit(0);  // Exit the program
    }
}

// Light 0 (top left) control callback
void light0_Operations(GLint option) {
    switch (option) {
    case 0:  // Turn off light
        glDisable(GL_LIGHT0);
        break;
    case 1:  // White light
        glEnable(GL_LIGHT0);
        glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
        glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
        break;
    case 2:  // Red light
        glEnable(GL_LIGHT0);
        glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, red_light);
        glLightfv(GL_LIGHT0, GL_SPECULAR, red_light);
        break;
    case 3:  // Blue light
        glEnable(GL_LIGHT0);
        glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, blue_light);
        glLightfv(GL_LIGHT0, GL_SPECULAR, blue_light);
        break;
    case 4:  // Yellow light
        glEnable(GL_LIGHT0);
        glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, yellow_light);
        glLightfv(GL_LIGHT0, GL_SPECULAR, yellow_light);
        break;
    }
    glutPostRedisplay();  // Refresh display
}

// Light 1 (top right) control callback
void light1_Operations(GLint option) {
    switch (option) {
    case 0: // Turn off light
        glDisable(GL_LIGHT1);
        break;
    case 1: // White light
        glEnable(GL_LIGHT1);
        glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, white_light);
        glLightfv(GL_LIGHT1, GL_SPECULAR, white_light);
        break;
    case 2: // Red light
        glEnable(GL_LIGHT1);
        glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, red_light);
        glLightfv(GL_LIGHT1, GL_SPECULAR, red_light);
        break;
    case 3: // Blue light
        glEnable(GL_LIGHT1);
        glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, blue_light);
        glLightfv(GL_LIGHT1, GL_SPECULAR, blue_light);
        break;
    case 4: // Yellow light
        glEnable(GL_LIGHT1);
        glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, yellow_light);
        glLightfv(GL_LIGHT1, GL_SPECULAR, yellow_light);
        break;
    }
    glutPostRedisplay();
}

// Light 2 (bottom left) control callback
void light2_Operations(GLint option) {
    switch (option) {
    case 0: // Turn off light
        glDisable(GL_LIGHT2);
        break;
    case 1: // White light
        glEnable(GL_LIGHT2);
        glLightfv(GL_LIGHT2, GL_POSITION, light_position2);
        glLightfv(GL_LIGHT2, GL_DIFFUSE, white_light);
        glLightfv(GL_LIGHT2, GL_SPECULAR, white_light);
        break;
    case 2: // Red light
        glEnable(GL_LIGHT2);
        glLightfv(GL_LIGHT2, GL_POSITION, light_position2);
        glLightfv(GL_LIGHT2, GL_DIFFUSE, red_light);
        glLightfv(GL_LIGHT2, GL_SPECULAR, red_light);
        break;
    case 3: // Blue light
        glEnable(GL_LIGHT2);
        glLightfv(GL_LIGHT2, GL_POSITION, light_position2);
        glLightfv(GL_LIGHT2, GL_DIFFUSE, blue_light);
        glLightfv(GL_LIGHT2, GL_SPECULAR, blue_light);
        break;
    case 4: // Yellow light
        glEnable(GL_LIGHT2);
        glLightfv(GL_LIGHT2, GL_POSITION, light_position2);
        glLightfv(GL_LIGHT2, GL_DIFFUSE, yellow_light);
        glLightfv(GL_LIGHT2, GL_SPECULAR, yellow_light);
        break;
    }
    glutPostRedisplay();
}

// Light 3 (bottom right) control callback
void light3_Operations(GLint option) {
    switch (option) {
    case 0: // Turn off light
        glDisable(GL_LIGHT3);
        break;
    case 1: // White light
        glEnable(GL_LIGHT3);
        glLightfv(GL_LIGHT3, GL_POSITION, light_position3);
        glLightfv(GL_LIGHT3, GL_DIFFUSE, white_light);
        glLightfv(GL_LIGHT3, GL_SPECULAR, white_light);
        break;
    case 2: // Red light
        glEnable(GL_LIGHT3);
        glLightfv(GL_LIGHT3, GL_POSITION, light_position3);
        glLightfv(GL_LIGHT3, GL_DIFFUSE, red_light);
        glLightfv(GL_LIGHT3, GL_SPECULAR, red_light);
        break;
    case 3: // Blue light
        glEnable(GL_LIGHT3);
        glLightfv(GL_LIGHT3, GL_POSITION, light_position3);
        glLightfv(GL_LIGHT3, GL_DIFFUSE, blue_light);
        glLightfv(GL_LIGHT3, GL_SPECULAR, blue_light);
        break;
    case 4: // Yellow light
        glEnable(GL_LIGHT3);
        glLightfv(GL_LIGHT3, GL_POSITION, light_position3);
        glLightfv(GL_LIGHT3, GL_DIFFUSE, yellow_light);
        glLightfv(GL_LIGHT3, GL_SPECULAR, yellow_light);
        break;
    }
    glutPostRedisplay();
}

// Light menu operations (placeholder)
void lightMenu_Operation(GLint option) {
    if (option == 0) {
        exit(0);
    }
}

// Material property selection callback
void materialPropertyOperations(GLint option) {
    switch (option) {
    case 0:  // Gold material
        glMaterialfv(GL_FRONT, GL_AMBIENT, gold_ambient);
        glMaterialfv(GL_FRONT, GL_SPECULAR, gold_specular);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, gold_diffuse);
        glMaterialfv(GL_FRONT, GL_SHININESS, gold_shininess);
        break;
    case 1:  // Silver material
        glMaterialfv(GL_FRONT, GL_AMBIENT, silver_ambient);
        glMaterialfv(GL_FRONT, GL_SPECULAR, silver_specular);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, silver_diffuse);
        glMaterialfv(GL_FRONT, GL_SHININESS, silver_shininess);
        break;
    case 2:  // Copper material
        glMaterialfv(GL_FRONT, GL_AMBIENT, copper_ambient);
        glMaterialfv(GL_FRONT, GL_SPECULAR, copper_specular);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, copper_diffuse);
        glMaterialfv(GL_FRONT, GL_SHININESS, copper_shininess);
        break;
    case 3:  // Neutral material
        glMaterialfv(GL_FRONT, GL_AMBIENT, neutral_ambient);
        glMaterialfv(GL_FRONT, GL_SPECULAR, neutral_specular);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, neutral_diffuse);
        glMaterialfv(GL_FRONT, GL_SHININESS, neutral_shininess);
        break;
    }
    glutPostRedisplay();
}

// Background image selection callback
void backgroundMenu_Operations(GLint option) {
    switch (option) {
    case 0:  // Day background
        makeImage("day.bmp");
        initializeImage();
        glutPostRedisplay();
        break;
    case 1:  // Night background
        makeImage("night.bmp");
        initializeImage();
        glutPostRedisplay();
        break;
    case 2:  // Classic background
        makeImage("classic.bmp");
        initializeImage();
        glutPostRedisplay();
        break;
    }
}

// Fog effect toggle callback
void fogMenu_Operations(GLint option) {
    switch (option) {
    case 0:  // Enable fog
        glFogfv(GL_FOG_COLOR, fogColor);
        glFogf(GL_FOG_DENSITY, 0.02);
        glEnable(GL_FOG);
        break;
    case 1:  // Disable fog
        glDisable(GL_FOG);
        break;
    }
    glutPostRedisplay();
}

// Fog intensity adjustment callback
void fogIntensityMenu_Operations(GLint option) {
    switch (option) {
    case 0:  // Low density
        glFogfv(GL_FOG_COLOR, fogColor);
        glFogf(GL_FOG_DENSITY, 0.02);
        glEnable(GL_FOG);
        break;
    case 1:  // Medium density
        glFogfv(GL_FOG_COLOR, fogColor);
        glFogf(GL_FOG_DENSITY, 0.05);
        glEnable(GL_FOG);
        break;
    case 2:  // High density
        glFogfv(GL_FOG_COLOR, fogColor);
        glFogf(GL_FOG_DENSITY, 0.1);
        glEnable(GL_FOG);
        break;
    }
    glutPostRedisplay();
}

// Creates the complete menu hierarchy
void createMenu() {
    // Create individual light control menus
    light0Menu = glutCreateMenu(light0_Operations);
    glutAddMenuEntry("off", 0);
    glutAddMenuEntry("White light", 1);
    glutAddMenuEntry("Red light", 2);
    glutAddMenuEntry("Blue light", 3);
    glutAddMenuEntry("Yellow light", 4);

    light1Menu = glutCreateMenu(light1_Operations);
    glutAddMenuEntry("off", 0);
    glutAddMenuEntry("White light", 1);
    glutAddMenuEntry("Red light", 2);
    glutAddMenuEntry("Blue light", 3);
    glutAddMenuEntry("Yellow light", 4);

    light2Menu = glutCreateMenu(light2_Operations);
    glutAddMenuEntry("off", 0);
    glutAddMenuEntry("White light", 1);
    glutAddMenuEntry("Red light", 2);
    glutAddMenuEntry("Blue light", 3);
    glutAddMenuEntry("Yellow light", 4);

    light3Menu = glutCreateMenu(light3_Operations);
    glutAddMenuEntry("off", 0);
    glutAddMenuEntry("White light", 1);
    glutAddMenuEntry("Red light", 2);
    glutAddMenuEntry("Blue light", 3);
    glutAddMenuEntry("Yellow light", 4);

    // Create main light menu that combines all individual light controls
    lightMenu = glutCreateMenu(lightMenu_Operation);
    glutAddSubMenu("Light 1", light0Menu);
    glutAddSubMenu("Light 2", light1Menu);
    glutAddSubMenu("Light 3", light2Menu);
    glutAddSubMenu("Light 4", light3Menu);
    glutAddMenuEntry("Quit", 0);

    // Create material properties menu
    materialProperties = glutCreateMenu(materialPropertyOperations);
    glutAddMenuEntry("Gold", 0);
    glutAddMenuEntry("Silver", 1);
    glutAddMenuEntry("Copper", 2);
    glutAddMenuEntry("Neutral", 3);

    // Create background selection menu
    backgroundMenu = glutCreateMenu(backgroundMenu_Operations);
    glutAddMenuEntry("Day", 0);
    glutAddMenuEntry("Night", 1);
    glutAddMenuEntry("classic", 2);

    // Create fog intensity submenu
    fogIntensityMenu = glutCreateMenu(fogIntensityMenu_Operations);
    glutAddMenuEntry("Low", 0);
    glutAddMenuEntry("Medium", 1);
    glutAddMenuEntry("High", 2);

    // Create main fog menu
    fogMenu = glutCreateMenu(fogMenu_Operations);
    glutAddMenuEntry("Enable Fog", 0);
    glutAddMenuEntry("Disable Fog", 1);
    glutAddSubMenu("Intensity", fogIntensityMenu);

    // Create root menu that combines all features
    glutCreateMenu(mainMenu);
    glutAddSubMenu("Lights", lightMenu);
    glutAddSubMenu("Material Properties", materialProperties);
    glutAddSubMenu("Background Images", backgroundMenu);
    glutAddSubMenu("Atmospheric Effect", fogMenu);
    glutAddMenuEntry("Quit", 0);

    // Attach menu to right mouse button
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}