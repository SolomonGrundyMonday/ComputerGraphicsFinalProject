/*
 *   Skybox class definition.
 *   Created by Jeff Colgan, November 2, 2021.
 *   Computer Graphics: Final Project. 
 */

#include "Skybox.h"

// Skybox class default constructor definition.
Skybox::Skybox()
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

// Skybox class constructor defintion.
Skybox::Skybox(float x, float y, float z, float dx, float dy, float dz, float rx, float ry, float rz)
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

// Skybox class Initialize function implementation definition.
int Skybox::Initialize(const char* filename)
{
   this->texture = LoadTexBMP(filename);
}

// Skybox class Render function implementation definition.
void Skybox::Render()
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

   // Draw "roof"

   // Draw "left wall"

   // Draw "right wall"

   // Draw "back wall"
 
   // Draw "front wall"

   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}

// Skybox class setPosition function definition.
void Skybox::setPosition(float x, float y, float z)
{
   this->posX = x;
   this->posY = y;
   this->posZ = z;
}

// Skybox class setScale function definition.
void Skybox::setScale(float x, float y, float z)
{
   this->scaleX = x;
   this->scaleY = y;
   this->scaleZ = z;
}

// Skybox class setRotation function definition.
void Skybox::setRotation(float x, float y, float z)
{
   this->rotX = x;
   this->rotY = y;
   this->rotZ = z;
}

// Skybox class getPosX function definition.
float Skybox::getPosX()
{
   return this->posX;
}

// Skybox class getPosY function definition.
float Skybox::getPosY()
{
   return this->posY;
}

// Skybox class getPosZ function definition.
float Skybox::getPosZ()
{
   return this->posZ;
}

// Skybox class getScaleX function definition.
float Skybox::getScaleX()
{
   return this->scaleX;
}

// Skybox class getScaleY function definition.
float Skybox::getScaleY()
{
   return this->scaleY;
}

// Skybox class getScaleZ function definition.
float Skybox::getScaleZ()
{
   return this->scaleZ;
}

// Skybox class getRotX function definition.
float Skybox::getRotX()
{
   return this->rotX;
}

// Skybox class getRotY function definition.
float Skybox::getRotY()
{
   return this->rotY;
}

// Skybox class getRotZ function definition.
float Skybox::getRotZ()
{
   return this->rotZ;
}