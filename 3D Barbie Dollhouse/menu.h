#ifndef MENU_H
#define MENU_H

#include "gl/glut.h"

// Light position arrays
extern GLfloat light_position0[];
extern GLfloat light_position1[];
extern GLfloat light_position2[];
extern GLfloat light_position3[];

// Light color arrays
extern GLfloat white_light[];
extern GLfloat red_light[];
extern GLfloat blue_light[];
extern GLfloat yellow_light[];

// Light properties
extern GLfloat lmodel_ambient[];
extern GLfloat lmodel_diffuse[];
extern GLfloat lmodel_specular[];

// Material properties for different materials
extern GLfloat gold_ambient[];
extern GLfloat gold_diffuse[];
extern GLfloat gold_specular[];
extern GLfloat gold_shininess[];

extern GLfloat copper_ambient[];
extern GLfloat copper_diffuse[];
extern GLfloat copper_specular[];
extern GLfloat copper_shininess[];

extern GLfloat silver_ambient[];
extern GLfloat silver_diffuse[];
extern GLfloat silver_specular[];
extern GLfloat silver_shininess[];

extern GLfloat neutral_ambient[];
extern GLfloat neutral_specular[];
extern GLfloat neutral_diffuse[];
extern GLfloat neutral_shininess[];

extern GLfloat fogColor[];

// Menu identifiers
extern GLint light0Menu, light1Menu, light2Menu, light3Menu, materialProperties, lightMenu, backgroundMenu, fogMenu, fogIntensityMenu;

// Function prototypes
void mainMenu(GLint option);
void light0_Operations(GLint option);
void light1_Operations(GLint option);
void light2_Operations(GLint option);
void light3_Operations(GLint option);
void lightMenu_Operation(GLint option);
void materialPropertyOperations(GLint option);
void backgroundMenu_Operations(GLint option);
void fogMenu_Operations(GLint option);
void fogIntensityMenu_Operations(GLint option);
void createMenu();

#endif // MENU_H
