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
   metal = LoadTexBMP("Assets/RustyMetal.bmp");

   return 0;
}

// Definition of Shovel class Render function implementation.
void Shovel::Render()
{
   // Enable textures.
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D, metal);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

   glPushMatrix();

   // Apply translation, rotation and scaling.
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
      float y = RADIUS * Sin(theta) + HANDLE_HEIGHT;
      float z = RADIUS * Cos(theta);

      glNormal3f(HANDLE_LEN, y, z);
      glTexCoord2f(0, i % 2);
      glVertex3f(HANDLE_LEN, y, z);
      glTexCoord2f(1, i % 2);
      glVertex3f(-HANDLE_LEN, y, z);
   }
   glEnd();

   glNormal3f(HANDLE_LEN, HANDLE_HEIGHT, 0.0);
   glBegin(GL_TRIANGLE_FAN);
   glTexCoord2f(0.5, 0.5);
   glVertex3f(HANDLE_LEN, HANDLE_HEIGHT, 0.0);

   for (int i = 0; i <= 360; i += 30)
   {
      float sine = Sin(i);
      float cosine = Cos(i);

      glNormal3f(HANDLE_LEN, sine + HANDLE_HEIGHT, cosine);
      glTexCoord2f(0.5 * cosine + 0.5, 0.5 * sine + 0.5);
      glVertex3f(HANDLE_LEN, RADIUS * sine + HANDLE_HEIGHT, RADIUS * cosine);
   }
   glEnd();

   glNormal3f(-HANDLE_LEN, HANDLE_HEIGHT, 0.0);
   glBegin(GL_TRIANGLE_FAN);
   glTexCoord2f(0.5, 0.5);
   glVertex3f(-HANDLE_LEN, HANDLE_HEIGHT, 0.0);

   for (int i = 0; i <= 360; i += 30)
   {
      float sine = Sin(i);
      float cosine = Cos(i);

      glNormal3f(-HANDLE_LEN, sine + HANDLE_HEIGHT, cosine);
      glTexCoord2f(0.5 * cosine + 0.5, 0.5 * sine + 0.5);
      glVertex3f(-HANDLE_LEN, RADIUS * sine + HANDLE_HEIGHT, RADIUS * cosine);
   }
   glEnd();

   // Connect the handle to the shaft.
   glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);
   glNormal3f(HANDLE_LEN, HANDLE_HEIGHT - RADIUS, 0.0);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(HANDLE_LEN, -HANDLE_HEIGHT / 2 + RADIUS, RADIUS);
   glTexCoord2f(0.0, 1.0);
   glVertex3f(HANDLE_LEN, -HANDLE_HEIGHT / 2 + RADIUS, -RADIUS);
   glTexCoord2f(1.0, 0.0);
   glVertex3f(HANDLE_LEN, HANDLE_HEIGHT, -RADIUS);
   glTexCoord2f(1.0, 1.0);
   glVertex3f(HANDLE_LEN, HANDLE_HEIGHT, RADIUS);
   glEnd();

   glNormal3f(HANDLE_LEN, HANDLE_HEIGHT - RADIUS, 0.0);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(-HANDLE_LEN, -HANDLE_HEIGHT / 2 + RADIUS, RADIUS);
   glTexCoord2f(0.0, 1.0);
   glVertex3f(-HANDLE_LEN, -HANDLE_HEIGHT / 2 + RADIUS, -RADIUS);
   glTexCoord2f(1.0, 0.0);
   glVertex3f(-HANDLE_LEN, HANDLE_HEIGHT, -RADIUS);
   glTexCoord2f(1.0, 1.0);
   glVertex3f(-HANDLE_LEN, HANDLE_HEIGHT, RADIUS);
   glEnd();

   glNormal3f(0.0, -HANDLE_HEIGHT / 2 + RADIUS, 0.0);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(-HANDLE_LEN, -HANDLE_HEIGHT / 2 + RADIUS, RADIUS);
   glTexCoord2f(0.0, 1.0);
   glVertex3f(-HANDLE_LEN, -HANDLE_HEIGHT / 2 + RADIUS, -RADIUS);
   glTexCoord2f(1.0, 0.0);
   glVertex3f(HANDLE_LEN, -HANDLE_HEIGHT / 2 + RADIUS, -RADIUS);
   glTexCoord2f(1.0, 1.0);
   glVertex3f(HANDLE_LEN, -HANDLE_HEIGHT / 2 + RADIUS, RADIUS);
   glEnd();

   glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 0);

   // Draw the shaft.
   glBindTexture(GL_TEXTURE_2D, texture);
   glBegin(GL_QUAD_STRIP);
   
   for (int i = 0; i <= 12; i++)
   {
      int theta = i * 30;
      float x = RADIUS * Cos(theta);
      float z = RADIUS * Sin(theta);

      glNormal3f(Cos(theta), -RADIUS, Sin(theta));
      glTexCoord2f(0.0, i * 1.0/12.0);
	  glVertex3f(x, -RADIUS - SHAFT_LEN, z);
      glTexCoord2f(12.0, i * 1.0/12.0);
      glVertex3f(x, -RADIUS, z);
   }
   glEnd();
   
   glNormal3f(0.0, -RADIUS - SHAFT_LEN, 0.0);
   glBegin(GL_TRIANGLE_FAN);
   glTexCoord2f(0.5, 0.5);
   glVertex3f(0.0, -RADIUS - SHAFT_LEN, 0.0);
   
   for (int i = 30; i <= 360; i += 30)
   {
      float cosine = Cos(i);
      float sine = Sin(i);

      glNormal3f(cosine, -RADIUS - SHAFT_LEN, sine);
      glTexCoord2f(0.5 * cosine + 0.5, 0.5 * sine + 0.5);
      glVertex3f(RADIUS * cosine, -RADIUS - SHAFT_LEN, RADIUS * sine);
   }
   glEnd();

   // Draw the Shovel head.
   glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);
   glBindTexture(GL_TEXTURE_2D, metal);

   glNormal3f(0.0, -SHAFT_LEN - HEAD_LEN - RADIUS, -RADIUS);
   glBegin(GL_TRIANGLE_FAN);
   glTexCoord2f(0.5, 0.5);
   glVertex3f(0.0, -SHAFT_LEN - HEAD_LEN - RADIUS, -RADIUS);

   for (int i = 0; i <= 180; i += 30)
   {
      float cosine = Cos(i);
      float sine = Sin(i);

      glNormal3f(cosine + cosine, -SHAFT_LEN - RADIUS, sine);
      glTexCoord2f(0.5 * cosine + 0.5, 0.5 * sine + 0.5);
      glVertex3f(RADIUS * cosine + HEAD_WIDTH * cosine, -SHAFT_LEN - RADIUS, RADIUS * sine);
   }
   glEnd();

   glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 0);

   glBegin(GL_QUAD_STRIP);

   float newRadius = RADIUS + 0.01;

   for (int i = 0; i <= 12; i++)
   {
      int theta = i * 30;
      float cosine = Cos(theta);
      float sine = Sin(theta);

      glNormal3f(cosine, -RADIUS, sine);
      glTexCoord2f(0.0, i % 2);
      glVertex3f(newRadius * cosine, -SHAFT_LEN, newRadius * sine);
      glTexCoord2f(1.0, i % 2);
      glVertex3f(newRadius * cosine, -SHAFT_LEN - RADIUS, newRadius * sine);
   }
   glEnd();

   glNormal3f(0.0, -RADIUS - SHAFT_LEN - 0.2, -RADIUS/2);
   glBegin(GL_TRIANGLE_FAN);
   glTexCoord2f(0.5, 0.5);
   glVertex3f(0.0, -RADIUS - SHAFT_LEN - 0.2, -RADIUS/2);

   for (int i = 30; i <= 360; i += 30)
   {
      float cosine = Cos(i);
      float sine = Sin(i);

      glNormal3f(cosine, -RADIUS - SHAFT_LEN, sine);
      glTexCoord2f(0.5 * cosine + 0.5, 0.5 * sine + 0.5);
      glVertex3f(newRadius * cosine, -RADIUS - SHAFT_LEN, newRadius * sine);
   }
   glEnd();

   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}

// Definition of Shovel class resolveCollision function implementaiton.
void Shovel::resolveCollision(Camera* camera)
{
   // Do stuff here.
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