/*
 *   Lantern class definition.
 *
 *   Created by Jeff Colgan, November 5, 2021.
 *   Computer Graphics: Final Project. 
 */
#include "Lantern.h"

// Function definition for Lantern class default constructor.
Lantern::Lantern()
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

// Function definition for Lantern class constructor.
Lantern::Lantern(float x, float y, float z, float dx, float dy, float dz, float rx, float ry, float rz)
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

// Function definition for Lantern class Initialize function implementation.
int Lantern::Initialize(const char* filename)
{
   this->texture = LoadTexBMP(filename);
}

// Function definition for Lantern class Render function implementation.
void Lantern::Render()
{
   // Enable textures.
   glEnable(GL_TEXTURES_2D);
   glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D, texture);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

   glPushMatrix();

   // Apply translation, rotation and scaling.
   glTranslatef(this->posX, this->posY, this->posZ);
   glRotatef(this->rotX, 1, 0, 0);
   glRotatef(this->rotY, 0, 1, 0);
   glRotatef(this->rotZ, 0, 0, 1);
   glScalef(this->scaleX, this->scaleY, this->scaleZ);

   // Draw object.

   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}

// Function definition for Lantern class setPosition function.
void Lantern::setPosition(float x, float y, float z)
{
   this->posX = x;
   this->posY = y;
   this->posZ = z;
}

// Function definition for Lantern class setScale function.
void Lantern::setScale(float x, float y, float z)
{
   this->scaleX = x;
   this->scaleY = y;
   this->scaleZ = z;
}

// Function definition for Lantern class setRotation function.
void Lantern::setRotation(float x, float y, float z)
{
   this->rotX = x;
   this->rotY = y;
   this->rotZ = z;
}

// Function definition for Lantern class getPosX function.
float Lantern::getPosX()
{
   return this->posX;
}

// Function definition for Lantern class getPosY function.
float Lantern::getPosY()
{
   return this->posY;
}

// Function definition for Lantern class getPosZ function.
float Lantern::getPosZ()
{
   return this->posZ;
}

// Function definition for Lantern class getScaleX function.
float Lantern::getScaleX()
{
   return this->scaleX;
}

// Function definition for Lantern class getScaleY function.
float Lantern::getScaleY()
{
   return this->scaleY;
}

// Function definition for Lantern class getScaleZ function.
float Lantern::getScaleZ()
{
   return this->scaleZ;
}

// Function definition for Lantern class getRotX function.
float Lantern::getRotX()
{
   return this->rotX;
}

// Function definition for Lantern class getRotY function.
float Lantern::getRotY()
{
   return this->rotY;
}

// Function definition for Lantern class getRotZ function.
float Lantern::getRotZ()
{
   return this->rotZ;
}