/*
 *   Cabin class definition.
 *   Created by Jeff Colgan, October 31, 2021,
 *   CSCI-4229 Computer Graphics : Final Project. 
 */

#include "Cabin.h"

// Function definition for Cabin class default constructor.
Cabin::Cabin()
{
   this->posX = 0.0;
   this->posY = 0.0;
   this->posZ = 0.0;

   this->scaleX = 1.0;
   this->scaleY = 1.0;
   this->scaleZ = 1.0;

   this->rotX = 0.0;
   this->rotY = 0.0;
   this->rotZ = 0.0;
}

// Function definition for Cabin class constructor.
Cabin::Cabin(float x, float y, float z, float dx, float dy, float dz, float rx, float ry, float rz)
{
   this->posX = x;
   this->posY = y;
   this->posZ = z;

   this->scaleX = dx;
   this->scaleY = dy;
   this->scaleZ = dz;

   this->rotX = rx;
   this->rotY = ry;
   this->rotZ = rz;
}

void Cabin::vertex(double th, double ph)
{
   double x = Sin(th)*Cos(ph);
   double y = Cos(th)*Cos(ph);
   double z = Sin(ph);

   glNormal3d(x, y, z);
   glVertex3d(x, y, z);
}

// Function definition for Cabin class Initialize function implementation.
int Cabin::Initialize(const char* filename)
{
   this->texture = LoadTexBMP(filename);
   //this->shingles = LoadTexBmp("Shingles.bmp");
   this->wood = LoadTexBMP("Wood.bmp");
   return 0;
}

// Function definition for Cabin class Render function implementation.
void Cabin::Render()
{
   // Enable textures.
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D, texture);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

   glPushMatrix();

   // Apply object's translation, rotation and scaling.
   glTranslatef(this->posX, this->posY, this->posZ);
   glRotatef(this->rotX, 1, 0, 0);
   glRotatef(this->rotY, 0, 1, 0);
   glRotatef(this->rotZ, 0, 0, 1);
   glScalef(this->scaleX, this->scaleY, this->scaleZ);

   // Front wall.
   glNormal3f(0.0, 0.0, -0.5);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(-1.0, -1.0, 1.0);
   glTexCoord2f(this->scaleX, 0.0);
   glVertex3f(1.0, -1.0, 1.0);
   glTexCoord2f(this->scaleX, this->scaleY);
   glVertex3f(1.0, 1.0, 1.0);
   glTexCoord2f(0.0, this->scaleY);
   glVertex3f(-1.0, 1.0, 1.0);
   glEnd();

   // Back Wall.
   glNormal3f(0.0, 0.0, 1.0);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(1.0, -1.0, -1.0);
   glTexCoord2f(this->scaleX, 0.0);
   glVertex3f(-1.0, -1.0, -1.0);
   glTexCoord2f(this->scaleX, this->scaleY);
   glVertex3f(-1.0, 1.0, -1.0);
   glTexCoord2f(0.0, this->scaleY);
   glVertex3f(1.0, 1.0, -1.0);
   glEnd();

   // Left Wall.
   glNormal3f(-0.5, 0.0, 0.0);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(-1.0, -1.0, -1.0);
   glTexCoord2f(this->scaleZ, 0.0);
   glVertex3f(-1.0, -1.0, 1.0);
   glTexCoord2f(this->scaleZ, this->scaleY);
   glVertex3f(-1.0, 1.0, 1.0);
   glTexCoord2f(0.0, this->scaleY);
   glVertex3f(-1.0, 1.0, -1.0); 
   glEnd();

   // Right wall.
   glNormal3f(0.5, 0.0, 0.0);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(1.0, -1.0, 1.0);
   glTexCoord2f(this->scaleZ, 0.0);
   glVertex3f(1.0, -1.0, -1.0);
   glTexCoord2f(this->scaleZ, this->scaleY);
   glVertex3f(1.0, 1.0, -1.0);
   glTexCoord2f(0.0, this->scaleY);
   glVertex3f(1.0, 1.0, 1.0);
   glEnd();

   // Attic Front Wall.
   glNormal3f(0.0, (1.0 + STEEPLE_HEIGHT)/2.0, 1.0);
   glBegin(GL_TRIANGLES);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(-1.0, 1.0, 1.0);
   glTexCoord2f(this->scaleX, 0.0);
   glVertex3f(1.0, 1.0, 1.0);
   glTexCoord2f(this->scaleX/2.0, (STEEPLE_HEIGHT * this->scaleY)/2.0);
   glVertex3f(0.0, 1.0 + STEEPLE_HEIGHT, 1.0);
   glEnd();

   // Attic Back wall.
   glNormal3f(0.0, (1.0 + STEEPLE_HEIGHT)/2.0, -1.0);
   glBegin(GL_TRIANGLES);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(1.0, 1.0, -1.0);
   glTexCoord2f(this->scaleX, 0.0);
   glVertex3f(-1.0, 1.0, -1.0);
   glTexCoord2f(this->scaleX/2.0, (STEEPLE_HEIGHT * this->scaleY)/2.0);
   glVertex3f(0.0, 1.0 + STEEPLE_HEIGHT, -1.0);
   glEnd();

   // Roof.
   glBindTexture(GL_TEXTURE_2D, wood);
   
   glNormal3f((1.0 + OVERHANG)/2.0, (1.0 + STEEPLE_HEIGHT)/2.0, 0.0);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(1.0 + OVERHANG, 0.9, -1.0 - OVERHANG);
   glTexCoord2f(1.0, 0.0);
   glVertex3f(1.0 + OVERHANG, 0.9, 1.0 + OVERHANG);
   glTexCoord2f(1.0, 1.0);
   glVertex3f(0.0, 1.0 + STEEPLE_HEIGHT, 1.0 + OVERHANG);
   glTexCoord2f(0.0, 1.0);
   glVertex3f(0.0, 1.0 + STEEPLE_HEIGHT, -1.0 - OVERHANG);
   glEnd();

   glNormal3f((-1.0 - OVERHANG)/2.0, (1.0 + STEEPLE_HEIGHT)/2.0, 0.0);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(-1.0 - OVERHANG, 0.9, 1.0 + OVERHANG);
   glTexCoord2f(1.0, 0.0);
   glVertex3f(-1.0 - OVERHANG, 0.9, -1.0 - OVERHANG);
   glTexCoord2f(1.0, 1.0);
   glVertex3f(0.0, 1.0 + STEEPLE_HEIGHT, -1.0 - OVERHANG);
   glTexCoord2f(0.0, 1.0);
   glVertex3f(0.0, 1.0 + STEEPLE_HEIGHT, 1.0 + OVERHANG);
   glEnd();

   // Doors and windows.
   //glBindTexture(GL_TEXTURE_2D, wood);

   // Door front face.
   glNormal3f(0.0, -0.75, 1.005);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(-0.05, -1.0, 1.01);
   glTexCoord2f(1.0, 0.0);
   glVertex3f(0.05, -1.0, 1.01);
   glTexCoord2f(1.0, 1.0);
   glVertex3f(0.05, -0.5, 1.01);
   glTexCoord2f(0.0, 1.0);
   glVertex3f(-0.05, -0.5, 1.01);
   glEnd();

   // Door top face.
   glNormal3f(0.0, -0.5, 1.005);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(-0.05, -0.5, 1.01);
   glTexCoord2f(1.0, 0.0);
   glVertex3f(0.05, -0.5, 1.01);
   glTexCoord2f(1.0, 1.0);
   glVertex3f(0.05, -0.5, 1.0);
   glTexCoord2f(0.0, 1.0);
   glVertex3f(-0.05, -0.5, 1.0);
   glEnd();

   // Door left face.
   glNormal3f(-0.05, -0.75, 1.005);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(-0.05, -1.0, 1.0);
   glTexCoord2f(1.0, 0.0);
   glVertex3f(-0.05, -1.0, 1.01);
   glTexCoord2f(1.0, 1.0);
   glVertex3f(-0.05, -0.5, 1.01);
   glTexCoord2f(0.0, 1.0);
   glVertex3f(-0.05, -0.5, 1.0);
   glEnd();

   // Door right face.
   glNormal3f(0.05, -0.75, 1.005);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(0.05, -1.0, 1.01);
   glTexCoord2f(1.0, 0.0);
   glVertex3f(0.05, -1.0, 1.0);
   glTexCoord2f(1.0, 1.0);
   glVertex3f(0.05, -0.5, 1.0);
   glTexCoord2f(0.0, 1.0);
   glVertex3f(0.05, -0.5, 1.01);
   glEnd();

   // Door top hinge.
   glBegin(GL_QUAD_STRIP);
   for (int i = 0; i <= 12; i++)
   {
      int theta = i * 30;
      float x = (-HINGE_RADIUS * Cos(theta)) - 0.055;
      float z = (-HINGE_RADIUS * Sin(theta)) + 1.005;
      glNormal3f(Cos(theta) - 0.055, -HINGE_RADIUS, Sin(theta) + 1.005);
      glTexCoord2f(0.0, i * 1.0/6.0);
      glVertex3f(x, -0.5 - HINGE_HEIGHT, z);
      glTexCoord2f(6.0, i * 1.0/6.0);
      glVertex3f(x, -0.5 - (2.0 * HINGE_HEIGHT), z);
   }
   glEnd();

   glNormal3f(-0.055, -0.5 - HINGE_HEIGHT, 1.005);
   glBegin(GL_TRIANGLE_FAN);
   glTexCoord2f(0.5, 0.5);
   glVertex3f(-0.05, -0.5 - HINGE_HEIGHT, 1.005);

   for (int i = 0; i <= 360; i += 30)
   {
      float x = (-HINGE_RADIUS * Cos(i)) - 0.055;
      float z = (-HINGE_RADIUS * Sin(i)) + 1.005;
      glNormal3f(Cos(i) - 0.055, -0.5 - HINGE_HEIGHT, Sin(i) + 1.005);
      glTexCoord2f(0.5 * Cos(i) + 0.5, 0.5 * Sin(i) + 0.5);
      glVertex3f(x, -0.5 - HINGE_HEIGHT, z);
   }
   glEnd();

   glNormal3f(-0.055, -HINGE_HEIGHT, 1.005);
   glBegin(GL_TRIANGLE_FAN);
   glTexCoord2f(0.5, 0.5);
   glVertex3f(-0.05, -0.5 - (2.0 * HINGE_HEIGHT), 1.005);

   for (int i = 0; i <= 360; i += 30)
   {
      float x = (-HINGE_RADIUS * Cos(i)) - 0.055;
      float z = (-HINGE_RADIUS * Sin(i)) + 1.005;
      glNormal3f(Cos(i) - 0.055, -HINGE_HEIGHT, Sin(i) + 1.005);
      glTexCoord2f(0.5 * Cos(i) + 0.5, 0.5 * Sin(i) + 0.5);
      glVertex3f(x, -0.5 - (2.0 * HINGE_HEIGHT), z);
   }
   glEnd();

   // Door bottom hinge.
   glBegin(GL_QUAD_STRIP);
   for (int i = 0; i <= 12; i++)
   {
      int theta = i * 30;
      float x = (-HINGE_RADIUS * Cos(theta)) - 0.055;
      float z = (-HINGE_RADIUS * Sin(theta)) + 1.005;
      glNormal3f(Cos(theta) - 0.055, -1.0 + HINGE_HEIGHT, Sin(theta) + 1.005);
      glTexCoord2f(0.0, i * 1.0/6.0);
      glVertex3f(x, -1.0 + HINGE_HEIGHT, z);
      glTexCoord2f(6.0, i * 1.0/6.0);
      glVertex3f(x, -1.0 + (2.0 * HINGE_HEIGHT), z);
   }
   glEnd();

   glNormal3f(-0.055, -1.0 + HINGE_HEIGHT, 1.005);
   glBegin(GL_TRIANGLE_FAN);
   glTexCoord2f(0.5, 0.5);
   glVertex3f(-0.055, -1.0 + HINGE_HEIGHT, 1.005);

   for (int i = 0; i <= 360; i += 30)
   {
      float x = (-HINGE_RADIUS * Cos(i)) - 0.055;
      float z = (-HINGE_RADIUS * Sin(i)) + 1.005;
      glNormal3f(Cos(i) - 0.055, -1.0 + HINGE_HEIGHT, Sin(i) + 1.005);
      glTexCoord2f(0.5 * Cos(i) + 0.5, 0.5 * Sin(i) + 0.5);
      glVertex3f(x, -1.0 + HINGE_HEIGHT, z);
   }
   glEnd();

   glNormal3f(-0.055, -1.0 + (2.0 * HINGE_HEIGHT), 1.005);
   glBegin(GL_TRIANGLE_FAN);
   glTexCoord2f(0.5, 0.5);
   glVertex3f(-0.055, -1.0 + (2.0 * HINGE_HEIGHT), 1.005);

   for (int i = 0; i <= 360; i += 30)
   {
      float x = (-HINGE_RADIUS * Cos(i)) - 0.055;
      float z = (-HINGE_RADIUS * Sin(i)) + 1.005;
      glNormal3f(Cos(i) - 0.055, -1.0 + (2.0 * HINGE_HEIGHT), Sin(i) + 1.005);
      glTexCoord2f(0.5 * Cos(i) + 0.5, 0.5 * Sin(i) + 0.5);
      glVertex3f(x, -1.0 + (2.0 * HINGE_HEIGHT), z);
   }
   glEnd();

   // Doorknob.
   glBegin(GL_QUAD_STRIP);
   for (int i = 0; i <= 12; i++)
   {
      int theta = i * 30;
      float x = (KNOB_RADIUS * Cos(theta)) + 0.04;
      float y = (3.0 * KNOB_RADIUS * Sin(theta)) - 0.75;
      glNormal3f(Cos(theta) + 0.04, Sin(theta) - 0.75, (1.01 + KNOB_PROTRUSION)/2.0);
      glTexCoord2f(0.0, i%2);
      glVertex3f(x, y, 1.01);
      glTexCoord2f(1.0, i%2);
      glVertex3f(x, y, 1.01 + KNOB_PROTRUSION);
   }
   glEnd();

   //glTranslatef(0.04, -0.75, 1.01 + KNOB_PROTRUSION);
   //glScalef(0.005, 0.03, 0.005);
   for (int ph = -90; ph < 90; ph += 10)
   {
      glBegin(GL_QUAD_STRIP);
      for (int th = 0; th <= 360; th += 20)
      {
         vertex(th, ph);
         vertex(th, ph+10);
	  }
      glEnd();
   }

   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}

// Function definition for Cabin class setPosition function.
void Cabin::setPosition(float x, float y, float z)
{
   this->posX = x;
   this->posY = y;
   this->posZ = z;
}

// Function definition for Cabin class setScale function.
void Cabin::setScale(float x, float y, float z)
{
   this->scaleX = x;
   this->scaleY = y;
   this->scaleZ = z;
}

// Function definition for Cabin class setRotation function.
void Cabin::setRotation(float x, float y, float z)
{
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