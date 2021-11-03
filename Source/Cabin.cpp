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

// Function definition for Cabin class Initialize function implementation.
int Cabin::Initialize(const char* filename)
{
   this->texture = LoadTexBMP("Bricks.bmp");
   this->shingles = LoadTexBmp("Shingles.bmp");
   this->trim = LoadTexBMP("WoodTrim.bmp");
}

// Function definition for Cabin class Render function implementation.
void Cabin::Render()
{
   // Enable textures.
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D, texture);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

   glPushMatrix();

   // Apply object's translation, rotation and scaling.
   glTranslatef(this->posX, this->posY, this->posZ);
   glRotatef(this->rotX, 1, 0, 0);
   glRotatef(this->rotY, 0, 1, 0);
   glRotatef(this->rotZ, 0, 0, 1);
   glScalef(this->scaleX, this->scaleY, this->scaleZ);

   // Walls.

   // Roof.

   // Trim panels.

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