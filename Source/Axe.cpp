/*
 *   Class definition for Axe class.
 *   Created by Jeff Colgan, October 27, 2021,
 *   CSCI-4229 Computer Graphics : Final Project. 
 */

#include "Axe.h"

// Function definition for Axe class default constructor.
Axe::Axe()
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

// Function definition for Axe class constructor.
Axe::Axe(float x, float y, float z, float dx, float dy, float dz, float rx, float ry, float rz)
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

// Function definition for Axe class Initialize function implementation.
int Axe::Initialize(const char* filename)
{
   this->texture = LoadTexBMP(filename);
   this->metal = LoadTexBMP("rustymetal.bmp");
   // also load metal texture for axe head.

   return 0;
}

// Function definition for Axe class Render function implementation.
void Axe::Render()
{
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D, texture);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

   glPushMatrix();

   glTranslatef(this->posX, this->posY, this->posZ);
   glRotatef(this->rotX, 1, 0, 0);
   glRotatef(this->rotY, 0, 1, 0);
   glRotatef(this->rotZ, 0, 0, 1);
   glScalef(this->scaleX, this->scaleY, this->scaleZ);

   // Draw the handle.

   glBegin(GL_QUAD_STRIP);
   for (int i = 0; i <= 12; i++)
   {
      int theta = i * 30;
      glNormal3f(RAD * Cos(theta), 0.0, RAD * Sin(theta));
      glTexCoord2f(0.0, i * 1.0/12.0);
      glVertex3f(RAD * Cos(theta), 0.0, RAD * Sin(theta));
      glTexCoord2f(12.0, i * 1.0/12.0);
      glVertex3f(RAD * Cos(theta), LENGTH, RAD * Sin(theta));
   }
   glEnd();

   glNormal3f(0.0, LENGTH, 0.0);
   glBegin(GL_TRIANGLE_FAN);
   glTexCoord2f(0.5, 0.5);
   glVertex3f(0.0, LENGTH, 0.0);

   for (int i = 0; i <= 360; i += 30)
   {
      glNormal3f(Cos(i), LENGTH, Sin(i));
      glTexCoord2f(0.5 * Cos(i) + 0.5, 0.5 * Sin(i) + 0.5);
      glVertex3f(RAD * Cos(i), LENGTH, RAD * Sin(i));
   }
   glEnd();

   glNormal3f(0.0, 0.0, 0.0);
   glBegin(GL_TRIANGLE_FAN);
   glTexCoord2f(0.5, 0.5);
   glVertex3f(0.0, 0.0, 0.0);

   for (int i = 0; i <= 360; i += 30)
   {
      glNormal3f(Cos(i), 0.0, Sin(i));
      glTexCoord2f(0.5 * Cos(i) + 0.5, 0.5 * Sin(i) + 0.5);
      glVertex3f(RAD * Cos(i), 0.0, RAD * Sin(i));
   }
   glEnd();

   // Draw the head.

   glPopMatrix();
}

// Function definition for Axe class setPosition function.
void Axe::setPosition(float x, float y, float z)
{
   this->posX = x;
   this->posY = y;
   this->posZ = z;
}

// Function definition for Axe class setScale function.
void Axe::setScale(float x, float y, float z)
{
   this->scaleX = x;
   this->scaleY = y;
   this->scaleZ = z;
}

// Function definition for Axe class setRotation function.
void Axe::setRotation(float x, float y, float z)
{
   this->rotX = x;
   this->rotY = y;
   this->rotZ = z;
}

// Function definition for Axe class getPosX function.
float Axe::getPosX()
{
   return this->posX;
}

// Function definition for Axe class getPosY function.
float Axe::getPosY()
{
   return this->posY;
}

// Function definition for Axe class getPosZ function.
float Axe::getPosZ()
{
   return this->posZ;
}

// Function definition for Axe class getScaleX function.
float Axe::getScaleX()
{
   return this->scaleX;
}

// Function definition for Axe class getScaleY function.
float Axe::getScaleY()
{
   return this->scaleY;
}

// Function definition for Axe class getScaleZ function.
float Axe::getScaleZ()
{
   return this->scaleZ;
}

// Function definition for Axe class getRotX function.
float Axe::getRotX()
{
   return this->rotX;
}

// Function definition for Axe class getRotY function.
float Axe::getRotY()
{
   return this->rotY;
}

// Function definition for Axe class getRotZ function.
float Axe::getRotZ()
{
   return this->rotZ;
}