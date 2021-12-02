/*
 *   Cabin class definition.
 *   Created by Jeff Colgan, October 31, 2021,
 *   CSCI-4229 Computer Graphics : Final Project. 
 */

#include "Cabin.h"

// Function definition for Cabin class default constructor.
Cabin::Cabin()
{
   // Set object translation coordinates.
   this->posX = 0.0;
   this->posY = 0.0;
   this->posZ = 0.0;

   // Set object's scaling.
   this->scaleX = 1.0;
   this->scaleY = 1.0;
   this->scaleZ = 1.0;

   // Set object's rotation about each axis.
   this->rotX = 0.0;
   this->rotY = 0.0;
   this->rotZ = 0.0;
}

// Function definition for Cabin class constructor.
Cabin::Cabin(float x, float y, float z, float dx, float dy, float dz, float rx, float ry, float rz)
{
   // Set object translation coordinates.
   this->posX = x;
   this->posY = y;
   this->posZ = z;

   // Set object's scaling.
   this->scaleX = dx;
   this->scaleY = dy;
   this->scaleZ = dz;

   // Set object's rotation about each axis.
   this->rotX = rx;
   this->rotY = ry;
   this->rotZ = rz;
}

// Function definition for Cabin class Initialize function implementation.
int Cabin::Initialize(const char* filename)
{
   this->texture = LoadTexBMP(filename);
   this->shingles = LoadTexBMP("Assets/Shingles.bmp");
   this->wood = LoadTexBMP("Assets/Door.bmp");
   this->metal = LoadTexBMP("Assets/Metal.bmp");
   this->shutters = LoadTexBMP("Assets/Shutters.bmp");

   return 0;
}

// Function definition for Cabin class Render function implementation.
void Cabin::Render()
{
   // Enable textures.
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D, texture);
   glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.0);
   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

   glPushMatrix();

   // Apply object's translation, rotation and scaling.
   glTranslatef(this->posX, this->posY, this->posZ);
   glRotatef(this->rotX, 1, 0, 0);
   glRotatef(this->rotY, 0, 1, 0);
   glRotatef(this->rotZ, 0, 0, 1);
   glScalef(this->scaleX, this->scaleY, this->scaleZ);

   // Front and back walls. (Tesselated to improve lighing effects on large polygons)
   // Idea borrowed from contents of https://www.glprogramming.com/red/chapter05.html.
   for (int i = -this->scaleX; i < this->scaleX; i++)
   {
      for (int j = -this->scaleY; j < this->scaleY; j++)
      {
         float minX = i / this->scaleX;
         float maxX = (i + 1) / this->scaleX;
         float minY = j / this->scaleY;
         float maxY = (j + 1) / this->scaleY;

         // Front wall segment
         glNormal3f((maxX - minX) / 2.0, (maxY - minY) / 2.0, 1.0);
         glBegin(GL_QUADS);
         glTexCoord2f(0.0, 0.0);
         glVertex3f(minX, minY, 1.0);
         glTexCoord2f(1.0, 0.0);
         glVertex3f(maxX, minY, 1.0);
         glTexCoord2f(1.0, 1.0);
         glVertex3f(maxX, maxY, 1.0);
         glTexCoord2f(0.0, 1.0);
         glVertex3f(minX, maxY, 1.0);
         glEnd();

         // Back Wall segment.
         glNormal3f((maxX - minX) / 2.0, (maxY - minY) / 2.0, -1.0);
         glBegin(GL_QUADS);
         glTexCoord2f(0.0, 0.0);
         glVertex3f(maxX, minY, -1.0);
         glTexCoord2f(1.0, 0.0);
         glVertex3f(minX, minY, -1.0);
         glTexCoord2f(1.0, 1.0);
         glVertex3f(minX, maxY, -1.0);
         glTexCoord2f(0.0, 1.0);
         glVertex3f(maxX, maxY, -1.0);
         glEnd();
      }
   }

   // Left and Right walls.  (Tesselated to improve lighing effects on large polygons)
   // Idea borrowed from contents of https://www.glprogramming.com/red/chapter05.html.
   for (int i = -this->scaleZ; i < this->scaleZ; i++)
   {
      for (int j = -this->scaleY; j < this->scaleY; j++)
      {
         float minZ = i / this->scaleZ;
         float maxZ = (i + 1) / this->scaleZ;
         float minY = j / this->scaleY;
         float maxY = (j + 1) / this->scaleY;

         // Left Wall segment.
         glNormal3f(-1.0, (maxY - minY) / 2.0, (maxZ - minZ) / 2.0);
         glBegin(GL_QUADS);
         glTexCoord2f(0.0, 0.0);
         glVertex3f(-1.0, minY, minZ);
         glTexCoord2f(this->scaleZ, 0.0);
         glVertex3f(-1.0, minY, maxZ);
         glTexCoord2f(this->scaleZ, this->scaleY);
         glVertex3f(-1.0, maxY, maxZ);
         glTexCoord2f(0.0, this->scaleY);
         glVertex3f(-1.0, maxY, minZ); 
         glEnd();

         // Right wall segment.
         glNormal3f(1.0, (maxY - minY) / 2.0, (maxZ - minZ) / 2.0);
         glBegin(GL_QUADS);
         glTexCoord2f(0.0, 0.0);
         glVertex3f(1.0, minY, maxZ);
         glTexCoord2f(this->scaleZ, 0.0);
         glVertex3f(1.0, minY, minZ);
         glTexCoord2f(this->scaleZ, this->scaleY);
         glVertex3f(1.0, maxY, minZ);
         glTexCoord2f(0.0, this->scaleY);
         glVertex3f(1.0, maxY, maxZ);
         glEnd();
      }
   }

   // Attic Front Wall.
   glNormal3f(0.0, STEEPLE_HEIGHT, 1.0);
   glBegin(GL_TRIANGLES);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(-1.0, 1.0, 1.0);
   glTexCoord2f(this->scaleX, 0.0);
   glVertex3f(1.0, 1.0, 1.0);
   glTexCoord2f(this->scaleX/2.0, (STEEPLE_HEIGHT * this->scaleY)/2.0);
   glVertex3f(0.0, 1.0 + STEEPLE_HEIGHT, 1.0);
   glEnd();

   // Attic Back wall.
   glNormal3f(0.0, 1.0 + (STEEPLE_HEIGHT/2.0), -1.0);
   glBegin(GL_TRIANGLES);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(1.0, 1.0, -1.0);
   glTexCoord2f(this->scaleX, 0.0);
   glVertex3f(-1.0, 1.0, -1.0);
   glTexCoord2f(this->scaleX/2.0, (STEEPLE_HEIGHT * this->scaleY)/2.0);
   glVertex3f(0.0, 1.0 + STEEPLE_HEIGHT, -1.0);
   glEnd();

   glBindTexture(GL_TEXTURE_2D, shingles);

   // Roof right segment.
   glNormal3f((1.0 + OVERHANG) / 2.0, (1.0 + STEEPLE_HEIGHT) / 2.0, 0.0);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(1.0 + OVERHANG, 0.9, -1.0 - OVERHANG);
   glTexCoord2f(this->scaleZ, 0.0);
   glVertex3f(1.0 + OVERHANG, 0.9, 1.0 + OVERHANG);
   glTexCoord2f(this->scaleZ, 2.0);
   glVertex3f(0.0, 1.0 + STEEPLE_HEIGHT, 1.0 + OVERHANG);
   glTexCoord2f(0.0, 2.0);
   glVertex3f(0.0, 1.0 + STEEPLE_HEIGHT, -1.0 - OVERHANG);
   glEnd();

   // Roof left segment.
   glNormal3f((-1.0 - OVERHANG) / 2.0, (1.0 + STEEPLE_HEIGHT) / 2.0, 0.0);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(-1.0 - OVERHANG, 0.9, 1.0 + OVERHANG);
   glTexCoord2f(this->scaleZ, 0.0);
   glVertex3f(-1.0 - OVERHANG, 0.9, -1.0 - OVERHANG);
   glTexCoord2f(this->scaleZ, 2.0);
   glVertex3f(0.0, 1.0 + STEEPLE_HEIGHT, -1.0 - OVERHANG);
   glTexCoord2f(0.0, 2.0);
   glVertex3f(0.0, 1.0 + STEEPLE_HEIGHT, 1.0 + OVERHANG);
   glEnd();

   // Door front face.
   glBindTexture(GL_TEXTURE_2D, wood);
   glNormal3f(0.0, -0.4, 1.005);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(-0.1, -1.0, 1.01);
   glTexCoord2f(1.0, 0.0);
   glVertex3f(0.1, -1.0, 1.01);
   glTexCoord2f(1.0, 1.0);
   glVertex3f(0.1, -0.2, 1.01);
   glTexCoord2f(0.0, 1.0);
   glVertex3f(-0.1, -0.2, 1.01);
   glEnd();

   // Door top face.
   glNormal3f(0.0, -0.2, 1.005);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(-0.1, -0.2, 1.01);
   glTexCoord2f(1.0, 0.0);
   glVertex3f(0.1, -0.2, 1.01);
   glTexCoord2f(1.0, 1.0);
   glVertex3f(0.1, -0.2, 1.0);
   glTexCoord2f(0.0, 1.0);
   glVertex3f(-0.1, -0.2, 1.0);
   glEnd();

   // Door left face.
   glNormal3f(-0.05, -0.75, 1.005);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(-0.1, -1.0, 1.0);
   glTexCoord2f(1.0, 0.0);
   glVertex3f(-0.1, -1.0, 1.01);
   glTexCoord2f(1.0, 1.0);
   glVertex3f(-0.1, -0.2, 1.01);
   glTexCoord2f(0.0, 1.0);
   glVertex3f(-0.1, -0.2, 1.0);
   glEnd();

   // Door right face.
   glNormal3f(0.05, -0.75, 1.005);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(0.1, -1.0, 1.01);
   glTexCoord2f(1.0, 0.0);
   glVertex3f(0.1, -1.0, 1.0);
   glTexCoord2f(1.0, 1.0);
   glVertex3f(0.1, -0.2, 1.0);
   glTexCoord2f(0.0, 1.0);
   glVertex3f(0.1, -0.2, 1.01);
   glEnd();

   // Attic window shutter.
   glBindTexture(GL_TEXTURE_2D, shutters);
   glNormal3f(0.0, (1.0 + STEEPLE_HEIGHT)/2.0, 1.01);
   glBegin(GL_TRIANGLE_FAN);
   glTexCoord2f(0.5, 0.5);
   glVertex3f(0.0, (1.0 + STEEPLE_HEIGHT)/2.0, 1.01);

   for (int i = 0; i <= 360; i += 30)
   {
      float x = 0.05 * Cos(i);
      float y = 3.0 * 0.05 * Sin(i) + ((1.0 + STEEPLE_HEIGHT)/2.0);

      glNormal3f(Cos(i), Sin(i), 1.01);
      glTexCoord2f(0.5 * Cos(i) + 0.5, 0.5 * Sin(i) + 0.5);
      glVertex3f(x, y, 1.01);
   }
   glEnd();

   // Attic window frame.
   glBegin(GL_QUAD_STRIP);
   for (int i = 0; i <= 12; i++)
   {
      int theta = i * 30;
      float x = 0.05 * Cos(theta);
      float y = 3.0 * 0.05 * Sin(theta) + ((1.0 + STEEPLE_HEIGHT)/2.0);

      glNormal3f(Cos(theta), Sin(theta), 1.0);
      glTexCoord2f(0.0, i * 1.0/6.0);
      glVertex3f(x, y, 1.0);
      glTexCoord2f(12.0, i * 1.0/6.0);
      glVertex3f(x, y, 1.01);
   }
   glEnd();

   drawWindow(-1.0, -0.4, -0.55);
   drawWindow(-1.0, -0.4, 0.55);
   drawWindow(1.0, -0.4, -0.55);
   drawWindow(1.0, -0.4, 0.55);

   // Door top hinge.
   glBindTexture(GL_TEXTURE_2D, metal);
   glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.5);
   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, gold);
   glBegin(GL_QUAD_STRIP);
   for (int i = 0; i <= 12; i++)
   {
      int theta = i * 30;
      float x = (-HINGE_RADIUS * Cos(theta)) - 0.105;
      float z = (-HINGE_RADIUS * Sin(theta)) + 1.005;

      glNormal3f(-Cos(theta), -0.2 - HINGE_HEIGHT, -Sin(theta));
      glTexCoord2f(0.0, i * 1.0/6.0);
      glVertex3f(x, -0.2 - HINGE_HEIGHT, z);
      glTexCoord2f(6.0, i * 1.0/6.0);
      glVertex3f(x, -0.2 - (2.0 * HINGE_HEIGHT), z);
   }
   glEnd();

   glNormal3f(-0.105, -0.2 - HINGE_HEIGHT, 1.005);
   glBegin(GL_TRIANGLE_FAN);
   glTexCoord2f(0.5, 0.5);
   glVertex3f(-0.1, -0.2 - HINGE_HEIGHT, 1.005);

   for (int i = 0; i <= 360; i += 30)
   {
      float x = (-HINGE_RADIUS * Cos(i)) - 0.105;
      float z = (-HINGE_RADIUS * Sin(i)) + 1.005;

      glNormal3f(Cos(i) - 0.105, -0.2 - HINGE_HEIGHT, Sin(i) + 1.005);
      glTexCoord2f(0.5 * Cos(i) + 0.5, 0.5 * Sin(i) + 0.5);
      glVertex3f(x, -0.2 - HINGE_HEIGHT, z);
   }
   glEnd();

   glNormal3f(-0.105, -HINGE_HEIGHT, 1.005);
   glBegin(GL_TRIANGLE_FAN);
   glTexCoord2f(0.5, 0.5);
   glVertex3f(-0.1, -0.2 - (2.0 * HINGE_HEIGHT), 1.005);

   for (int i = 0; i <= 360; i += 30)
   {
      float x = (-HINGE_RADIUS * Cos(i)) - 0.105;
      float z = (-HINGE_RADIUS * Sin(i)) + 1.005;

      glNormal3f(Cos(i) - 0.105, -HINGE_HEIGHT, Sin(i) + 1.005);
      glTexCoord2f(0.5 * Cos(i) + 0.5, 0.5 * Sin(i) + 0.5);
      glVertex3f(x, -0.2 - (2.0 * HINGE_HEIGHT), z);
   }
   glEnd();

   // Door bottom hinge.
   glBegin(GL_QUAD_STRIP);
   for (int i = 0; i <= 12; i++)
   {
      int theta = i * 30;
      float x = (-HINGE_RADIUS * Cos(theta)) - 0.105;
      float z = (-HINGE_RADIUS * Sin(theta)) + 1.005;

      glNormal3f(-Cos(theta), -1.0 + (2.0 * HINGE_HEIGHT), -Sin(theta));
      glTexCoord2f(0.0, i * 1.0/6.0);
      glVertex3f(x, -1.0 + HINGE_HEIGHT, z);
      glTexCoord2f(6.0, i * 1.0/6.0);
      glVertex3f(x, -1.0 + (2.0 * HINGE_HEIGHT), z);
   }
   glEnd();

   glNormal3f(-0.105, -1.0 + HINGE_HEIGHT, 1.005);
   glBegin(GL_TRIANGLE_FAN);
   glTexCoord2f(0.5, 0.5);
   glVertex3f(-0.105, -1.0 + HINGE_HEIGHT, 1.005);

   for (int i = 0; i <= 360; i += 30)
   {
      float x = (-HINGE_RADIUS * Cos(i)) - 0.105;
      float z = (-HINGE_RADIUS * Sin(i)) + 1.005;

      glNormal3f(Cos(i) - 0.105, -1.0 + HINGE_HEIGHT, Sin(i) + 1.005);
      glTexCoord2f(0.5 * Cos(i) + 0.5, 0.5 * Sin(i) + 0.5);
      glVertex3f(x, -1.0 + HINGE_HEIGHT, z);
   }
   glEnd();

   glNormal3f(-0.105, -1.0 + (2.0 * HINGE_HEIGHT), 1.005);
   glBegin(GL_TRIANGLE_FAN);
   glTexCoord2f(0.5, 0.5);
   glVertex3f(-0.105, -1.0 + (2.0 * HINGE_HEIGHT), 1.005);

   for (int i = 0; i <= 360; i += 30)
   {
      float x = (-HINGE_RADIUS * Cos(i)) - 0.105;
      float z = (-HINGE_RADIUS * Sin(i)) + 1.005;

      glNormal3f(Cos(i) - 0.105, -1.0 + (2.0 * HINGE_HEIGHT), Sin(i) + 1.005);
      glTexCoord2f(0.5 * Cos(i) + 0.5, 0.5 * Sin(i) + 0.5);
      glVertex3f(x, -1.0 + (2.0 * HINGE_HEIGHT), z);
   }
   glEnd();

   // Door handle.
   glBegin(GL_QUAD_STRIP);
   for (int i = 0; i <= 12; i++)
   {
      int theta = i * 30;
      float x = (KNOB_RADIUS * Cos(theta)) + 0.075;
      float y = (3.0 * KNOB_RADIUS * Sin(theta)) - 0.65;

      glNormal3f(Cos(theta) + 0.04, Sin(theta) - 0.65, (1.01 + KNOB_PROTRUSION)/2.0);
      glTexCoord2f(0.0, i%2);
      glVertex3f(x, y, 1.01);
      glTexCoord2f(1.0, i%2);
      glVertex3f(x, y, 1.01 + KNOB_PROTRUSION);
   }
   glEnd();

   // Door handle front face.
   glNormal3f(0.075, -0.65, 1.01 + KNOB_PROTRUSION);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(0.07, -0.65 - 3.0 * KNOB_RADIUS, 1.01 + KNOB_PROTRUSION);
   glTexCoord2f(1.0, 0.0);
   glVertex3f(0.08, -0.65 - 3.0 * KNOB_RADIUS, 1.01 + KNOB_PROTRUSION);
   glTexCoord2f(1.0, 1.0);
   glVertex3f(0.08, -0.65 + 3.0 * KNOB_RADIUS, 1.01 + KNOB_PROTRUSION);
   glTexCoord2f(0.0, 1.0);
   glVertex3f(0.07, -0.65 + 3.0 * KNOB_RADIUS, 1.01 + KNOB_PROTRUSION);
   glEnd();

   // Door handle back face.
   glNormal3f(0.075, -0.65, 1.011 + KNOB_PROTRUSION);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(0.07, -0.65 - 3.0 * KNOB_RADIUS, 1.011 + KNOB_PROTRUSION);
   glTexCoord2f(1.0, 0.0);
   glVertex3f(0.08, -0.65 - 3.0 * KNOB_RADIUS, 1.011 + KNOB_PROTRUSION);
   glTexCoord2f(1.0, 1.0);
   glVertex3f(0.08, -0.65 + 3.0 * KNOB_RADIUS, 1.011 + KNOB_PROTRUSION);
   glTexCoord2f(0.0, 1.0);
   glVertex3f(0.07, -0.65 + 3.0 * KNOB_RADIUS, 1.011 + KNOB_PROTRUSION);
   glEnd();

   // Door handle right face.
   glNormal3f(0.08, -0.65, 1.0105 + KNOB_PROTRUSION);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(0.08, -0.65 - 3.0 * KNOB_RADIUS, 1.011 + KNOB_PROTRUSION);
   glTexCoord2f(1.0, 0.0);
   glVertex3f(0.08, -0.65 - 3.0 * KNOB_RADIUS, 1.01 + KNOB_PROTRUSION);
   glTexCoord2f(1.0, 1.0);
   glVertex3f(0.08, -0.65 + 3.0 * KNOB_RADIUS, 1.01 + KNOB_PROTRUSION);
   glTexCoord2f(0.0, 1.0);
   glVertex3f(0.08, -0.65 + 3.0 * KNOB_RADIUS, 1.011 + KNOB_PROTRUSION);
   glEnd();

   // Door handle left face.
   glNormal3f(0.07, -0.65, 1.0105 + KNOB_PROTRUSION);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(0.07, -0.65 - 3.0 * KNOB_RADIUS, 1.01 + KNOB_PROTRUSION);
   glTexCoord2f(1.0, 0.0);
   glVertex3f(0.07, -0.65 - 3.0 * KNOB_RADIUS, 1.011 + KNOB_PROTRUSION);
   glTexCoord2f(1.0, 1.0);
   glVertex3f(0.07, -0.65 + 3.0 * KNOB_RADIUS, 1.011 + KNOB_PROTRUSION);
   glTexCoord2f(0.0, 1.0);
   glVertex3f(0.07, -0.65 + 3.0 * KNOB_RADIUS, 1.01 + KNOB_PROTRUSION);
   glEnd();

   // Door handle top face.
   glNormal3f(0.075, (-0.75 + 3.0 * KNOB_RADIUS)/2.0, 1.0105 + KNOB_PROTRUSION);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(0.07, -0.65 + 3.0 * KNOB_RADIUS, 1.011 + KNOB_PROTRUSION);
   glTexCoord2f(1.0, 0.0);
   glVertex3f(0.08, -0.65 + 3.0 * KNOB_RADIUS, 1.011 + KNOB_PROTRUSION);
   glTexCoord2f(1.0, 1.0);
   glVertex3f(0.08, -0.65 + 3.0 * KNOB_RADIUS, 1.01 + KNOB_PROTRUSION);
   glTexCoord2f(0.0, 1.0);
   glVertex3f(0.07, -0.65 + 3.0 * KNOB_RADIUS, 1.01 + KNOB_PROTRUSION);
   glEnd();

   // Door handle bottom face.
   glNormal3f(0.075, (-0.75 - 3.0 * KNOB_RADIUS)/2.0, 1.0105 + KNOB_PROTRUSION);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(0.07, -0.65 - 3.0 * KNOB_RADIUS, 1.01 + KNOB_PROTRUSION);
   glTexCoord2f(1.0, 0.0);
   glVertex3f(0.08, -0.65 - 3.0 * KNOB_RADIUS, 1.01 + KNOB_PROTRUSION);
   glTexCoord2f(1.0, 1.0);
   glVertex3f(0.08, -0.65 - 3.0 * KNOB_RADIUS, 1.011 + KNOB_PROTRUSION);
   glTexCoord2f(0.0, 1.0);
   glVertex3f(0.07, -0.65 - 3.0 * KNOB_RADIUS, 1.011 + KNOB_PROTRUSION);
   glEnd();

   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}

// Function definition for drawWindow helper function.
void Cabin::drawWindow(float x, float y, float z)
{
   float leftBottomCornerY;
   float leftBottomCornerZ;
   float rightBottomCornerY;
   float rightBottomCornerZ;
   float leftTopCornerY;
   float leftTopCornerZ;
   float rightTopCornerY;
   float rightTopCornerZ;
   float windowLocationX;
   float normalX;

   if (x < 0.0)
   {
      windowLocationX = x - (2.0 * WINDOW_DEPTH);
      normalX = x - WINDOW_DEPTH;
   }
   else
   {
      x = 1.0;
      windowLocationX = x + (2.0 * WINDOW_DEPTH);
      normalX = x + WINDOW_DEPTH;
   }
      
   leftBottomCornerY = y - WINDOW_HEIGHT;
   rightBottomCornerY = y - WINDOW_HEIGHT;
   leftTopCornerY = y + WINDOW_HEIGHT;
   rightTopCornerY = y + WINDOW_HEIGHT;

   if (z < 0.0)
   {
      leftBottomCornerZ = z - WINDOW_WIDTH;
      rightBottomCornerZ = z + WINDOW_WIDTH;
      leftTopCornerZ = z - WINDOW_WIDTH;
      rightTopCornerZ = z + WINDOW_WIDTH;
   }
   else
   {
      leftBottomCornerZ = z + WINDOW_WIDTH;
      rightBottomCornerZ = z - WINDOW_WIDTH;
      leftTopCornerZ = z + WINDOW_WIDTH;
      rightTopCornerZ = z - WINDOW_WIDTH;
   }

   // Window shutters.
   glNormal3f(windowLocationX, y, z);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(windowLocationX, leftBottomCornerY, leftBottomCornerZ);
   glTexCoord2f(1.0, 0.0);
   glVertex3f(windowLocationX, rightBottomCornerY, rightBottomCornerZ);
   glTexCoord2f(1.0, 1.0);
   glVertex3f(windowLocationX, rightTopCornerY, rightTopCornerZ);
   glTexCoord2f(0.0, 1.0);
   glVertex3f(windowLocationX, leftTopCornerY, leftTopCornerZ);
   glEnd();

   // Window bottom frame.
   glNormal3f(normalX, leftTopCornerY, z);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(windowLocationX, leftBottomCornerY, leftBottomCornerZ);
   glTexCoord2f(1.0, 0.0);
   glVertex3f(windowLocationX, leftBottomCornerY, rightBottomCornerZ);
   glTexCoord2f(1.0, 1.0);
   glVertex3f(x, leftBottomCornerY, rightBottomCornerZ);
   glTexCoord2f(0.0, 1.0);
   glVertex3f(x, leftBottomCornerY, leftBottomCornerZ);
   glEnd();

   // Window top frame.
   glNormal3f(normalX, leftBottomCornerY, z);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(x, leftTopCornerY, leftBottomCornerZ);
   glTexCoord2f(1.0, 0.0);
   glVertex3f(x, leftTopCornerY, rightBottomCornerZ);
   glTexCoord2f(1.0, 1.0);
   glVertex3f(windowLocationX, rightTopCornerY, rightBottomCornerZ);
   glTexCoord2f(0.0, 1.0);
   glVertex3f(windowLocationX, rightTopCornerY, leftBottomCornerZ);
   glEnd();

   // Window left frame.
   glNormal3f(normalX, y, rightBottomCornerZ);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(x, leftBottomCornerY, rightBottomCornerZ);
   glTexCoord2f(1.0, 0.0);
   glVertex3f(windowLocationX, leftBottomCornerY, rightBottomCornerZ);
   glTexCoord2f(1.0, 1.0);
   glVertex3f(windowLocationX, leftTopCornerY, rightBottomCornerZ);
   glTexCoord2f(0.0, 1.0);
   glVertex3f(x, leftTopCornerY, rightBottomCornerZ);
   glEnd();

   // Window right frame.
   glNormal3f(normalX, y, leftBottomCornerZ);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(windowLocationX, leftTopCornerY, leftBottomCornerZ);
   glTexCoord2f(1.0, 0.0);
   glVertex3f(x, leftTopCornerY, leftBottomCornerZ);
   glTexCoord2f(1.0, 1.0);
   glVertex3f(x, leftBottomCornerY, leftBottomCornerZ);
   glTexCoord2f(0.0, 1.0);
   glVertex3f(windowLocationX, leftBottomCornerY, leftBottomCornerZ);
   glEnd();
}

// Function definition for Cabin class getSide helper function.
wall Cabin::getSide(Camera* camera)
{
   // Compute the relative x, z coordinates and convert to object coordinates.
   float cosine = Cos(this->rotY);
   float sine = Sin(this->rotY);
   float camX = camera->getEyeX() - this->posX;
   float camZ = camera->getEyeZ() - this->posZ;
   float objX = (camX * cosine) - (camZ * sine);
   float objZ = (camZ * cosine) + (camX * sine);

   float diffXMin = objX - (-this->scaleX - 0.75);
   float diffXMax = (this->scaleX + 0.75) - objX;
   float diffZMin = objZ - (-this->scaleZ - 0.75);
   float diffZMax = (this->scaleZ + 0.75) - objZ;

   // Determine which wall of the hitbox is experiencing the collision.
   bool left = diffXMin < diffXMax && diffXMin < diffZMin && diffXMin < diffZMax;
   bool right = diffXMax < diffXMin && diffXMax < diffZMin && diffXMax < diffZMax;
   bool front = diffZMin < diffZMax && diffZMin < diffXMin && diffZMin < diffXMax;
   bool back = diffZMax < diffZMin && diffZMax < diffXMin && diffZMax < diffXMax;

   // Return the appropriate wall.
   if (front)
      return FRONT;
   else if (back)
      return BACK;
   else if (left)
      return LEFT;
   else if (right)
      return RIGHT;
   else
      return NONE;
}

// Function definition for Cabin class detectCollision function.
bool Cabin::detectCollision(Camera* camera)
{
   // Compute the relative x, z coordinates and convert to object coordinates.
   float cosine = Cos(this->rotY);
   float sine = Sin(this->rotY);
   float camX = camera->getEyeX() - this->posX;
   float camZ = camera->getEyeZ() - this->posZ;
   float objX = (camX * cosine) - (camZ * sine);
   float objZ = (camZ * cosine) + (camX * sine);

   // Compute x and z maximum and minimum (with offset to prevent Camera clipping).
   float minX = -this->scaleX - 0.75;
   float maxX = this->scaleX + 0.75;
   float minZ = -this->scaleZ - 0.75;
   float maxZ = this->scaleZ + 0.75;

   // Determine if the Camera is colliding with the x, z components of the hitbox.
   bool xCollide = objX > minX && objX < maxX;
   bool zCollide = objZ > minZ && objZ < maxZ;

   return xCollide && zCollide;
}

// Function definition for Cabin class resolveCollision function implementation.
void Cabin::resolveCollision(Camera* camera)
{
   // Compute relative x, z coordinate and convert to object coordinates.
   float cosine = Cos(this->rotY);
   float sine = Sin(this->rotY);
   float camX = camera->getEyeX() - this->posX;
   float camZ = camera->getEyeZ() - this->posZ;
   float objX = (camX * cosine) - (camZ * sine);
   float objZ = (camZ * cosine) + (camX * sine);

   // Compute minimum, maximum x and z values.
   float minX = -this->scaleX - 0.75;
   float maxX = this->scaleX + 0.75;
   float minZ = -this->scaleZ - 0.75;
   float maxZ = this->scaleZ + 0.75;

   wall collision = getSide(camera);

   if (collision == FRONT)
   {
      float newX, newZ;

      newX = objX;
      newZ = minZ;

      // Undo transformation and convert back to world coordinates (transform matrix inverse courtesy of Symbolab).
      newX = -(newX * cosine / (-sine * sine - cosine * cosine)) - (newZ * sine / (-sine * sine - cosine * cosine));
      newZ = (objX * sine / (-sine * sine - cosine * cosine)) - (newZ * cosine / (-sine * sine - cosine * cosine));
      newX += this->posX;
      newZ += this->posZ;

      // Update Camera position.
      camera->setEyePos(newX, camera->getEyeY(), newZ);
   }
   else if (collision == BACK)
   {
      float newX, newZ;

      newX = objX;
      newZ = maxZ;

      // Undo transformation and convert back to world coordinates (transform matrix inverse courtesy of Symbolab).
      newX = -(newX * cosine / (-sine * sine - cosine * cosine)) - (newZ * sine / (-sine * sine - cosine * cosine));
      newZ = (objX * sine / (-sine * sine - cosine * cosine)) - (newZ * cosine / (-sine * sine - cosine * cosine));
      newX += this->posX;
      newZ += this->posZ;

      // Update Camera position.
      camera->setEyePos(newX, camera->getEyeY(), newZ);
   }
   else if (collision == LEFT)
   {
      float newX, newZ;

      newX = minX;
      newZ = objZ;

      // Undo transformation and convert back to world coordinates (transform matrix inverse courtesy of Symbolab).
      newZ = (newX * sine / (-sine * sine - cosine * cosine)) - (newZ * cosine / (-sine * sine - cosine * cosine));
      newX = -(newX * cosine / (-sine * sine - cosine * cosine)) - (objZ * sine / (-sine * sine - cosine * cosine));
      newX += this->posX;
      newZ += this->posZ;

      // Update Camera position.
      camera->setEyePos(newX, camera->getEyeY(), newZ);
   }
   else if (collision == RIGHT)
   {
      float newX, newZ;

      newX = maxX;
      newZ = objZ;

      // Undo transformation and convert back to world coordinates (transform matrix inverse courtesy of Symbolab).
      newZ = (newX * sine / (-sine * sine - cosine * cosine)) - (newZ * cosine / (-sine * sine - cosine * cosine));
      newX = -(newX * cosine / (-sine * sine - cosine * cosine)) - (objZ * sine / (-sine * sine - cosine * cosine));
      newX += this->posX;
      newZ += this->posZ;

      // Update Camera position.
      camera->setEyePos(newX, camera->getEyeY(), newZ);
   }
}

// Function definition for Cabin class setPosition function.
void Cabin::setPosition(float x, float y, float z)
{
   // Set object translation coordinates.
   this->posX = x;
   this->posY = y;
   this->posZ = z;
}

// Function definition for Cabin class setScale function.
void Cabin::setScale(float x, float y, float z)
{
   // Set object's scaling.
   this->scaleX = x;
   this->scaleY = y;
   this->scaleZ = z;
}

// Function definition for Cabin class setRotation function.
void Cabin::setRotation(float x, float y, float z)
{
   // Set object's rotation about each axis.
   this->rotX = x;
   this->rotY = y;
   this->rotZ = z;
}

// Function definition for Cabin class getPosX function.
float Cabin::getPosX()
{
   return this->posX;
}

// Function definition for Cabin class getPosY function.
float Cabin::getPosY()
{
   return this->posY;
}

// Function definition for Cabin class getPosZ function.
float Cabin::getPosZ()
{
   return this->posZ;
}

// Function definition for Cabin class getScaleX function.
float Cabin::getScaleX()
{
   return this->scaleX;
}

float Cabin::getScaleY()
{
   return this->scaleY;
}

// Function definition for Cabin class getScaleZ function.
float Cabin::getScaleZ()
{
   return this->scaleZ;
}

// Function definition for Cabin class getRotX function.
float Cabin::getRotX()
{
   return this->rotX;
}

// Function definition for Cabin class getRotY function.
float Cabin::getRotY()
{
   return this->rotY;
}

// Function definition for Cabin class getRotZ function.
float Cabin::getRotZ()
{
   return this->rotZ;
}