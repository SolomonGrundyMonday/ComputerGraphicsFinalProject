/*
 *   Shovel class definition.
 *
 *   Created by Jeff Colgan, October 26, 2021,
 *   CSCI-4229 Computer Graphics: Final Project. 
 */
#include "Shovel.h"

// Definition of Shovel class default constructor.
Shovel::Shovel()
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

// Definition of Shovel class constructor.
Shovel::Shovel(float x, float y, float z, float dx, float dy, float dz, float rx, float ry, float rz)
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

// Definition of Shovel class Initialize function implementation.
int Shovel::Initialize(const char* filename)
{
   texture = LoadTexBMP(filename);
   metal = LoadTexBMP("rustymetal.bmp");

   return 0;
}

// Definition of Shovel class Render function implementation.
void Shovel::Render()
{
   
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D, metal);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

   glPushMatrix();

   glTranslated(this->posX, this->posY, this->posZ);
   glRotated(this->rotX, 1, 0, 0);
   glRotated(this->rotY, 0, 1, 0);
   glRotated(this->rotZ, 0, 0, 1);
   glScaled(this->scaleX, this->scaleY, this->scaleZ);

   glBegin(GL_QUAD_STRIP);

   // Draw the handle.
   for (int i = 0; i < 12; i++)
   {
      int theta = i * 30;
      glNormal3f(RADIUS * Cos(theta), RADIUS * Sin(theta) + HANDLE_HEIGHT, HANDLE_LEN);
      glTexCoord2f(0, i % 2);
      glVertex3f(RADIUS * Cos(theta), RADIUS * Sin(theta) + HANDLE_HEIGHT, HANDLE_LEN);
      glTexCoord2f(1, i % 2);
      glVertex3f(RADIUS * Cos(theta), RADIUS * Sin(theta) + HANDLE_HEIGHT, -HANDLE_LEN);
   }
   glEnd();

   glNormal3f(0.0, HANDLE_HEIGHT, HANDLE_LEN);
   glBegin(GL_TRIANGLE_FAN);
   glTexCoord2f(0.5, 0.5);
   glVertex3f(0.0, HANDLE_HEIGHT, HANDLE_LEN);

   for (int i = 0; i <= 360; i += 30)
   {
      glTexCoord2f(0.5 * Cos(i) + 0.5, 0.5 * Sin(i) + 0.5);
      glVertex3f(RADIUS * Cos(i), RADIUS * Sin(i) + HANDLE_HEIGHT, HANDLE_LEN);
   }
   glEnd();

   glNormal3f(0.0, HANDLE_HEIGHT, -HANDLE_LEN);
   glBegin(GL_TRIANGLE_FAN);
   glTexCoord2f(0.5, 0.5);
   glVertex3f(0.0, HANDLE_HEIGHT, -HANDLE_LEN);

   for (int i = 0; i <= 360; i += 30)
   {
      glTexCoord2f(0.5 * Cos(i) + 0.5, 0.5 * Sin(i) + 0.5);
      glVertex3f(RADIUS * Cos(i), RADIUS * Sin(i) + HANDLE_HEIGHT, -HANDLE_LEN);
   }
   glEnd();

   // Connect the handle to the shaft.
   glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(RADIUS, -HANDLE_HEIGHT / 2 + RADIUS, HANDLE_LEN);
   glTexCoord2f(0.0, 1.0);
   glVertex3f(-RADIUS, -HANDLE_HEIGHT / 2 + RADIUS, HANDLE_LEN);
   glTexCoord2f(1.0, 0.0);
   glVertex3f(-RADIUS, HANDLE_HEIGHT, HANDLE_LEN);
   glTexCoord2f(1.0, 1.0);
   glVertex3f(RADIUS, HANDLE_HEIGHT, HANDLE_LEN);
   glEnd();

   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(RADIUS, -HANDLE_HEIGHT / 2 + RADIUS, -HANDLE_LEN);
   glTexCoord2f(0.0, 1.0);
   glVertex3f(-RADIUS, -HANDLE_HEIGHT / 2 + RADIUS, -HANDLE_LEN);
   glTexCoord2f(1.0, 0.0);
   glVertex3f(-RADIUS, HANDLE_HEIGHT, -HANDLE_LEN);
   glTexCoord2f(1.0, 1.0);
   glVertex3f(RADIUS, HANDLE_HEIGHT, -HANDLE_LEN);
   glEnd();

   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(RADIUS, -HANDLE_HEIGHT / 2 + RADIUS, -HANDLE_LEN);
   glTexCoord2f(0.0, 1.0);
   glVertex3f(-RADIUS, -HANDLE_HEIGHT / 2 + RADIUS, -HANDLE_LEN);
   glTexCoord2f(1.0, 0.0);
   glVertex3f(-RADIUS, -HANDLE_HEIGHT / 2 + RADIUS, HANDLE_HEIGHT);
   glTexCoord2f(1.0, 1.0);
   glVertex3f(RADIUS, -HANDLE_HEIGHT / 2 + RADIUS, HANDLE_HEIGHT);
   glEnd();

   glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 0);

   // Draw the shaft.
   glBindTexture(GL_TEXTURE_2D, texture);
   glBegin(GL_QUAD_STRIP);
   
   for (int i = 0; i <= 12; i++)
   {
      int theta = i * 30;
      glNormal3f(Cos(theta), -RADIUS, Sin(theta));
      glTexCoord2f(0.0, i * 1.0/12.0);
	  glVertex3f(RADIUS * Cos(theta), -RADIUS - SHAFT_LEN, RADIUS * Sin(theta));
      glTexCoord2f(12.0, i * 1.0/12.0);
      glVertex3f(RADIUS * Cos(theta), -RADIUS, RADIUS * Sin(theta));
   }
   glEnd();
   
   glNormal3f(0.0, -RADIUS - SHAFT_LEN, 0.0);
   glBegin(GL_TRIANGLE_FAN);
   glTexCoord2f(0.5, 0.5);
   
   for (int i = 30; i <= 360; i += 30)
   {
      glNormal3f(Cos(i), -RADIUS - SHAFT_LEN, Sin(i));
      glTexCoord2f(0.5 * Cos(i) + 0.5, 0.5 * Sin(i) + 0.5);
      glVertex3f(RADIUS * Cos(i), -RADIUS - SHAFT_LEN, RADIUS * Sin(i));
   }
   glEnd();

   // More badness here.
   // Draw the Shovel head.
   glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);
   glBindTexture(GL_TEXTURE_2D, metal);

   glNormal3f(0.0, -SHAFT_LEN - HEAD_LEN, 0.0);
   glBegin(GL_TRIANGLE_FAN);
   glTexCoord2f(0.5, 0.5);
   glVertex3f(0.0, -SHAFT_LEN - HEAD_LEN, 0.0);

   for (int i = 0; i <= 180; i += 30)
   {
      glNormal3f(RADIUS * Cos(i) + HEAD_LEN * Cos(i), -SHAFT_LEN, RADIUS * Sin(i));
      glTexCoord2f(0.5 * Cos(i) + 0.5, 0.5 * Sin(i) + 0.5);
      glVertex3f(RADIUS * Cos(i) + HEAD_LEN * Cos(i), -SHAFT_LEN, RADIUS * Sin(i));
   }
   glEnd();

   glPopMatrix();
}

// Definition of Shovel class setPosition function.
void Shovel::setPosition(float x, float y, float z)
{
   this->posX = x;
   this->posY = y;
   this->posZ = z;
}

// Definition of Shovel class setScale function.
void Shovel::setScale(float x, float y, float z)
{
   this->scaleX = x;
   this->scaleY = y;
   this->scaleZ = z;
}

// Definition of Shovel class setRotation function.
void Shovel::setRotation(float x, float y, float z)
{
   this->rotX = x;
   this->rotY = y;
   this->rotZ = z;
}

// Definition of Shovel class getPosX function.
float Shovel::getPosX()
{
   return this->posX;
}

// Definition of Shovel class getPosY function.
float Shovel::getPosY()
{
   return this->posY;
}

// Definition of Shovel class getPosZ function.
float Shovel::getPosZ()
{
   return this->posZ;
}

// Definition of Shovel class getScaleX function.
float Shovel::getScaleX()
{
   return this->scaleX;
}

// Definition of Shovel class getScaleY function.
float Shovel::getScaleY()
{
   return this->scaleY;
}

// Definition of Shovel class getScaleZ function.
float Shovel::getScaleZ()
{
   return this->scaleZ;
}

// Definition of Shovel class getRotX function.
float Shovel::getRotX()
{
   return this->rotX;
}

// Definition of Shovel class getRotY function.
float Shovel::getRotY()
{
   return this->rotY;
}

// Definition of Shovel class getRotZ function.
float Shovel::getRotZ()
{
   return this->rotZ;
}