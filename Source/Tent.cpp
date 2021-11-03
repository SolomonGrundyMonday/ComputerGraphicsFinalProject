#include "Tent.h"

// Function definition for Tent object default constructor.
Tent::Tent()
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

// Function definition for Tent object constructor.
Tent::Tent(float x, float y, float z, float dx, float dy, float dz, float rx, float ry, float rz)
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

// Function definition for Tent object Initialize function implementation.
int Tent::Initialize(const char* filename)
{
   this->texture = LoadTexBMP(filename);
}

// Function definition for Tent object Render function implementation.
void Tent::Render()
{
   // Enable textures.
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D, texture);

   glPushMatrix();

   // Apply translation, rotation and scaling.
   glTranslatef(this->posX, this->posY, this->posZ);
   glRotatef(this->rotX, 1, 0, 0);
   glRotatef(this->rotY, 0, 1, 0);
   glRotatef(this->rotZ, 0, 0, 1);
   glScalef(this->scaleX, this->scaleY, this->scaleZ);

   // Draw Tent walls.

   // Draw Tent flaps.

   // Draw Tent roof.

   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}

// Function definition for Tent object setPosition function.
void Tent::setPosition(float x, float y, float z)
{
   this->posX = x;
   this->posY = y;
   this->posZ = z;
}

// Function definition for Tent object setScale function.
void Tent::setScale(float x, float y, float z)
{
   this->scaleX = x;
   this->scaleY = y;
   this->scaleZ = z;
}

// Function definition for Tent object setRotation function.
void Tent::setRotation(float x, float y, float z)
{
   this->rotX = x;
   this->rotY = y;
   this->rotZ = z;
}

// Function definition for Tent object getPosX function.
float Tent::getPosX()
{
   return this->posX;
}

// Function definition for Tent object getPosY function.
float Tent::getPosY()
{
   return this->posY;
}

// Function definition for Tent object getPosZ function.
float Tent::getPosZ()
{
   return this->posZ;
}

// Function definition for Tent object getScaleX function.
float Tent::getScaleX()
{
   return this->scaleX;
}

// Function definition for Tent object getScaleY function.
float Tent::getScaleY()
{
   return this->scaleY;
}

// Function definition for Tent object getScaleZ function.
float Tent::getScaleZ()
{
   return this->scaleZ;
}

// Function definition for Tent object getRotX function.
float Tent::getRotX()
{
   return this->rotX;
}

// Function definition for Tent object getRotY function.
float Tent::getRotY()
{
   return this->rotY;
}

// Function definition for Tent object getRotZ function.
float Tent::getRotZ()
{
   return this->rotZ;
}