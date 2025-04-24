/* Athabasca University

   Comp390 - Introduction to Computer Graphics

   Final Project

   Option 1

   @author: Hosty Khurana

   @Student ID: 3623176

   @date: 22nd March 2025


   Purpose: Contains functions to draw various 3D objects (Barbie doll, house, furniture, etc.)
            using GLUT primitives. Demonstrates hierarchical modeling and transformations.


   File Routines:
               drawBarbieHouse() - Creates a dollhouse with cube body, cone roof, and door
               
               drawTeaTable()    - Builds a table with teapot, sugar cone, and donut
               
               drawBarbie()      - Models a doll with face, dress, and articulated limbs
               
               drawFlowerPot()   - Constructs a pot with stems, flowers, and leaves
               
               drawCar()         - Assembles a toy car with body, wheels, and details
 */

#include <GL/glut.h>
#include "composite3dObjects.h"

// Draws a Barbie doll house with roof, base, door, and peephole
void drawBarbieHouse() {
    // Main body of the house (cube)
    glutSolidCube(5);

    // Roof (cone rotated and positioned above cube)
    glPushMatrix();
    glTranslatef(0.0, 2.5, 1.0);  // Position above house
    glRotatef(-90.0, 1.0, 0.0, 0.0); // Rotate to point downward
    glutSolidCone(4, 4, 32, 32);  // Cone roof
    glPopMatrix();

    // Base (flattened sphere under house)
    glPushMatrix();
    glTranslatef(0.0, -3.0, 0.0); // Position below house
    glScalef(1.0, 0.2, 1.0);      // Flatten in Y-axis
    glutSolidSphere(4, 32, 32);    // Base sphere
    glPopMatrix();

    // Door (scaled cube at front of house)
    glPushMatrix();
    glTranslatef(0.0, -0.3, 5.0); // Position at front
    glScalef(0.5, 1.0, 0.2);      // Scale to door proportions
    glutSolidCube(3);              // Door cube
    glPopMatrix();

    // Peephole (torus on door)
    glPushMatrix();
    glTranslatef(0.0, 0.0, 6.0);  // Position slightly in front of door
    glutSolidTorus(0.1, 0.2, 10, 10); // Ring-shaped peephole
    glPopMatrix();
}

// Draws a tea table with legs, teapot, sugar, and donut
void drawTeaTable() {
    // Table top (flattened sphere)
    glPushMatrix();
    glScalef(1.0, 0.2, 1.0);      // Flatten in Y-axis
    glutSolidSphere(4, 32, 32);    // Table surface
    glPopMatrix();

    // Table leg 1 (left)
    glPushMatrix();
    glScalef(0.2, 1.2, 1.0);      // Scale to leg proportions
    glTranslatef(-8.0, -1.5, 2.0); // Position left side
    glutSolidCube(2);              // Leg cube
    glPopMatrix();

    // Table leg 2 (right)
    glPushMatrix();
    glScalef(0.2, 1.2, 1.0);      // Scale to leg proportions
    glTranslatef(8.0, -1.5, 2.0); // Position right side
    glutSolidCube(2);              // Leg cube
    glPopMatrix();

    // Teapot
    glPushMatrix();
    glTranslatef(-1.0, 1.2, 0.0); // Position on table
    glutSolidTeapot(1);            // Classic GLUT teapot
    glPopMatrix();

    // Sugar pile (cone)
    glPushMatrix();
    glTranslatef(1.2, 1.0, 3.0);  // Position on table
    glRotatef(-90, 1.0, 0.0, 0.0); // Rotate to point upward
    glutSolidCone(1, 1, 16, 16);   // Sugar cone
    glPopMatrix();

    // Donut (torus)
    glPushMatrix();
    glTranslatef(-1.5, 1.5, 5.0); // Position on table
    glRotatef(90, 1.0, 0.0, 0.0); // Rotate to lie flat
    glScalef(1.5, 1.5, 1.5);      // Scale up size
    glutSolidTorus(0.1, 0.2, 10, 10); // Donut shape
    glPopMatrix();
}

// Draws a Barbie doll with face, body, dress, and limbs
void drawBarbie() {
    // Head (sphere)
    glPushMatrix();
    glutSolidSphere(1.5, 32, 32);  // Head sphere
    glPopMatrix();

    // Eye 1 (left)
    glPushMatrix();
    glTranslatef(-1.0, 0.6, 2.0);  // Position left eye
    glutSolidTorus(0.1, 0.2, 10, 10); // Eye ring
    glPopMatrix();

    // Eye 2 (right)
    glPushMatrix();
    glTranslatef(0.0, 0.6, 2.0);   // Position right eye
    glutSolidTorus(0.1, 0.2, 10, 10); // Eye ring
    glPopMatrix();

    // Nose (small cone)
    glPushMatrix();
    glTranslatef(-0.5, 0.0, 2.0);  // Position between eyes
    glutSolidCone(0.2, 0.1, 10, 10); // Nose cone
    glPopMatrix();

    // Cap (cone on head)
    glPushMatrix();
    glTranslatef(-0.5, 1.5, 2.0);  // Position on head
    glRotatef(-90.0, 1.0, 0.0, 0.0); // Rotate to point downward
    glutSolidCone(1.2, 1.0, 10, 10); // Cap cone
    glPopMatrix();

    // Body (stretched cube)
    glPushMatrix();
    glTranslatef(0.0, -2.0, 0.0);  // Position below head
    glScalef(0.5, 3.0, 1.0);       // Scale to body proportions
    glutSolidCube(1.5);             // Body cube
    glPopMatrix();

    // Dress (cone skirt)
    glPushMatrix();
    glTranslatef(0.0, -6.0, 0.4);  // Position below body
    glRotatef(-90.0, 1.0, 0.0, 0.0); // Rotate to point downward
    glutSolidCone(2.0, 4.0, 10, 10); // Dress cone
    glPopMatrix();

    // Arm 1 (left)
    glPushMatrix();
    glTranslatef(-1.5, -2.5, 0.0); // Position left side
    glRotatef(-65, 0.0, 0.0, 1.0);  // Rotate outward
    glScalef(0.5, 2.0, 0.5);       // Scale to arm proportions
    glutSolidCube(1.5);             // Arm cube
    glPopMatrix();

    // Arm 2 (right)
    glPushMatrix();
    glTranslatef(1.5, -2.5, 0.0);  // Position right side
    glRotatef(65, 0.0, 0.0, 1.0);   // Rotate outward
    glScalef(0.5, 2.0, 0.5);       // Scale to arm proportions
    glutSolidCube(1.5);             // Arm cube
    glPopMatrix();
}

// Draws a flower pot with stems, flowers, and leaves
void drawFlowerPot() {
    // Pot (dodecahedron rotated)
    glPushMatrix();
    glScalef(1.5, 1.0, 1.0);      // Scale pot shape
    glRotatef(90, 1.0, 0.0, 0.0);  // Rotate to stand upright
    glutSolidDodecahedron();        // 12-sided pot
    glPopMatrix();

    // Stem 1 (left)
    glPushMatrix();
    glTranslatef(-1.5, 2.5, 0.0);  // Position left side
    glRotatef(45.0, 0.0, 0.0, 1.0); // Angle outward
    glScalef(0.5, 2.0, 0.5);       // Scale to stem proportions
    glutSolidCube(1.5);             // Stem cube
    glPopMatrix();

    // Stem 2 (right)
    glPushMatrix();
    glTranslatef(1.5, 2.5, 0.0);   // Position right side
    glRotatef(-45.0, 0.0, 0.0, 1.0); // Angle outward
    glScalef(0.5, 2.0, 0.5);       // Scale to stem proportions
    glutSolidCube(1.5);             // Stem cube
    glPopMatrix();

    // Flower 1 center (left)
    glPushMatrix();
    glTranslatef(-3.0, 4.0, 1.0);  // Position at stem end
    glutSolidTorus(0.1, 0.2, 10, 10); // Flower center
    glPopMatrix();

    // Flower 1 petals (4 spheres around center)
    glPushMatrix();
    glTranslatef(-3.0, 4.8, 1.0);  // Top petal
    glutSolidSphere(0.5, 10, 10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2.2, 4.0, 1.0);  // Right petal
    glutSolidSphere(0.5, 10, 10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-3.8, 4.0, 1.0);  // Left petal
    glutSolidSphere(0.5, 10, 10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-3.0, 3.2, 1.0);  // Bottom petal
    glutSolidSphere(0.5, 10, 10);
    glPopMatrix();

    // Leaf (left stem)
    glPushMatrix();
    glTranslatef(-2.5, 1.6, 1.0);  // Position along stem
    glRotatef(90, 0.0, 1.0, 0.0);  // Orient leaf
    glRotatef(-45, 1.0, 0.0, 0.0); // Angle leaf
    glutSolidCone(0.5, 1.0, 10, 10); // Leaf shape
    glPopMatrix();

    // Flower 2 center (right)
    glPushMatrix();
    glTranslatef(3.0, 4.0, 1.0);   // Position at stem end
    glutSolidTorus(0.1, 0.2, 10, 10); // Flower center
    glPopMatrix();

    // Flower 2 petals (4 spheres around center)
    glPushMatrix();
    glTranslatef(3.0, 4.8, 1.0);   // Top petal
    glutSolidSphere(0.5, 10, 10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.2, 4.0, 1.0);   // Left petal
    glutSolidSphere(0.5, 10, 10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3.8, 4.0, 1.0);   // Right petal
    glutSolidSphere(0.5, 10, 10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3.0, 3.2, 1.0);   // Bottom petal
    glutSolidSphere(0.5, 10, 10);
    glPopMatrix();

    // Leaf (right stem)
    glPushMatrix();
    glTranslatef(2.5, 1.6, 1.0);   // Position along stem
    glRotatef(-90, 0.0, 1.0, 0.0); // Orient leaf
    glRotatef(-45, 1.0, 0.0, 0.0); // Angle leaf
    glutSolidCone(0.5, 1.0, 10, 10); // Leaf shape
    glPopMatrix();
}

// Draws a toy car with body, top, wheels, and details
void drawCar() {
    // Main body (stretched cube)
    glPushMatrix();
    glTranslatef(0.0, 0.0, 1.0);  // Position above ground
    glScalef(1.5, 0.5, 0.5);      // Scale to car proportions
    glutSolidCube(4);              // Body cube
    glPopMatrix();

    // Car top (octahedron)
    glPushMatrix();
    glTranslatef(0.0, 1.0, 0.0);  // Position on body
    glScalef(2.0, 2.0, 2.0);      // Scale to size
    glutSolidOctahedron();         // 8-sided top
    glPopMatrix();

    // Wheel 1 (left rear)
    glPushMatrix();
    glTranslatef(-1.5, -1.2, 2.0); // Position left side
    glutSolidTorus(0.2, 0.4, 10, 10); // Wheel torus
    glPopMatrix();

    // Wheel 2 (right rear)
    glPushMatrix();
    glTranslatef(1.5, -1.2, 2.0); // Position right side
    glutSolidTorus(0.2, 0.4, 10, 10); // Wheel torus
    glPopMatrix();

    // Headlight (sphere)
    glPushMatrix();
    glTranslatef(3.3, 0.3, 1.0);  // Position at front
    glScalef(0.5, 1.0, 1.0);      // Scale to light shape
    glutSolidSphere(0.5, 10, 10);  // Light sphere
    glPopMatrix();

    // Exhaust pipe (small cube)
    glPushMatrix();
    glTranslatef(-4.2, -0.8, 0.0); // Position at rear
    glScalef(1.5, 0.8, 1.0);      // Scale to pipe shape
    glutSolidCube(0.5);            // Exhaust cube
    glPopMatrix();

    // Smoke (dodecahedron particles)
    glPushMatrix();
    glTranslatef(-5.5, -0.8, 0.0); // Position behind exhaust
    glScalef(0.2, 0.2, 0.2);      // Scale to smoke size
    glRotatef(90, 1.0, 0.0, 0.0); // Orient smoke
    glutSolidDodecahedron();       // Smoke particle 1

    glTranslatef(-5.5, -0.8, 0.0); // Second smoke position
    glScalef(1.2, 1.2, 1.0);      // Slightly larger
    glutSolidDodecahedron();       // Smoke particle 2
    glPopMatrix();
}