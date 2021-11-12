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
   return 0;
}

// Function definition for Tent object Render function implementation.
void Tent::Render()
{
   float textureRatio = 1.0/12.0;

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

   // Draw Tent front wall.
   glNormal3f(-0.8, 0.0, 1.0);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(-1.0, -1.0, 1.0);
   glTexCoord2f(this->scaleX, 0.0);
   glVertex3f(-0.4, -1.0, 1.0);
   glTexCoord2f(this->scaleX, this->scaleY);
   glVertex3f(-0.4, 1.0, 1.0);
   glTexCoord2f(0.0, this->scaleY);
   glVertex3f(-1.0, 1.0, 1.0);
   glEnd();

   glNormal3f(0.8, 0.0, 1.0);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(0.4, -1.0, 1.0);
   glTexCoord2f(this->scaleX, 0.0);
   glVertex3f(1.0, -1.0, 1.0);
   glTexCoord2f(this->scaleX, this->scaleY);
   glVertex3f(1.0, 1.0, 1.0);
   glTexCoord2f(0.0, this->scaleY);
   glVertex3f(0.4, 1.0, 1.0);
   glEnd();

   glNormal3f(0.0, 0.6, 1.0);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(-0.4, 0.2, 1.0);
   glTexCoord2f(this->scaleX, 0.0);
   glVertex3f(0.4, 0.2, 1.0);
   glTexCoord2f(this->scaleX, this->scaleY);
   glVertex3f(0.4, 1.0, 1.0);
   glTexCoord2f(0.0, this->scaleY);
   glVertex3f(-0.4, 1.0, 1.0);
   glEnd();

   // Draw Tent back wall.
   glNormal3f(0.0, 0.0, -1.0);
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

   // Draw Tent left wall.
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

   // Draw Tent Right wall.
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

   // Draw Tent roof.
   glNormal3f(0.0, (1.5/2.0), 1.0);
   glBegin(GL_TRIANGLES);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(-1.0, 1.0, 1.0);
   glTexCoord2f(this->scaleX, 0.0);
   glVertex3f(1.0, 1.0, 1.0);
   glTexCoord2f(this->scaleX/2.0, (0.5 * this->scaleY)/2.0);
   glVertex3f(0.0, 1.5, 1.0);
   glEnd();

   glNormal3f(0.0, 1.5/2.0, -1.0);
   glBegin(GL_TRIANGLES);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(1.0, 1.0, -1.0);
   glTexCoord2f(this->scaleX, 0.0);
   glVertex3f(-1.0, 1.0, -1.0);
   glTexCoord2f(this->scaleX/2.0, (0.5 * this->scaleY)/2.0);
   glVertex3f(0.0, 1.5, -1.0);
   glEnd();

   glNormal3f(-0.5, 1.25, 0.0);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(-1.0, 1.0, -1.0);
   glTexCoord2f(this->scaleZ, 0.0);
   glVertex3f(-1.0, 1.0, 1.0);
   glTexCoord2f(this->scaleZ, this->scaleY);
   glVertex3f(0.0, 1.5, 1.0);
   glTexCoord2f(0.0, this->scaleY);
   glVertex3f(0.0, 1.5, -1.0);
   glEnd();

   glNormal3f(0.5, 1.25, 0.0);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(1.0, 1.0, 1.0);
   glTexCoord2f(this->scaleZ, 0.0);
   glVertex3f(1.0, 1.0, -1.0);
   glTexCoord2f(this->scaleZ, this->scaleY);
   glVertex3f(0.0, 1.5, -1.0);
   glTexCoord2f(0.0, this->scaleY);
   glVertex3f(0.0, 1.5, 1.0);
   glEnd();

   // Draw Tent flaps.
   glBegin(GL_QUAD_STRIP);
   for (int i = 0; i <= 12; i++)
   {
      int theta = i * 30;
      float x = Cos(theta);
      float z = Sin(theta);

      glNormal3f(x, -1.0, z);
      glTexCoord2f(0.0, i * textureRatio);
      glVertex3f(x * 0.1 + 0.4, -1.0, z * 0.1 + 1.0);
      glTexCoord2f(12.0, i * textureRatio);
      glVertex3f(x * 0.1 + 0.4, 0.2, z * 0.1 + 1.0);
   }
   glEnd();

   glNormal3f(0.4, 0.2, 1.0);
   glBegin(GL_TRIANGLE_FAN);
   glTexCoord2f(0.5, 0.5);
   glVertex3f(0.4, 0.2, 1.0);
   for (int i = 0; i <= 360; i += 30)
   {
      glNormal3f(Cos(i) + 0.4, 0.2, Sin(i) + 1.0);
      glTexCoord2f(0.5 * Cos(i) + 0.5, 0.5 * Sin(i) + 0.5);
      glVertex3f(0.1 * Cos(i) + 0.4, 0.2, 0.1 * Sin(i) + 1.0);
   }
   glEnd();

   glNormal3f(0.4, -1.0, 1.0);
   glBegin(GL_TRIANGLE_FAN);
   glTexCoord2f(0.5, 0.5);
   glVertex3f(0.4, -1.0, 1.0);
   for (int i = 0; i <= 360; i += 30)
   {
      glNormal3f(Cos(i) + 0.4, -1.0, Sin(i) + 1.0);
      glTexCoord2f(0.5 * Cos(i) + 0.5, 0.5 * Sin(i) + 0.5);
      glVertex3f(0.1 * Cos(i) + 0.4, -1.0, 0.1 * Sin(i) + 1.0);
   }
   glEnd();
   
   glBegin(GL_QUAD_STRIP);
   for (int i = 0; i <= 12; i++)
   {
      int theta = i * 30;
      float x = Cos(theta);
      float z = Sin(theta);

      glNormal3f(x, -1.0, z);
      glTexCoord2f(0.0, i * textureRatio);
      glVertex3f(x * 0.1 - 0.4, -1.0, z * 0.1 + 1.0);
      glTexCoord2f(12.0, i * textureRatio);
      glVertex3f(x * 0.1 - 0.4, 0.2, z * 0.1 + 1.0);
   }
   glEnd();

   glNormal3f(-0.4, 0.2, 1.0);
   glBegin(GL_TRIANGLE_FAN);
   glTexCoord2f(0.5, 0.5);
   glVertex3f(-0.4, 0.2, 1.0);
   for (int i = 0; i <= 360; i += 30)
   {
      glNormal3f(Cos(i) - 0.4, 0.2, Sin(i) + 1.0);
      glTexCoord2f(0.5 * Cos(i) + 0.5, 0.5 * Sin(i) + 0.5);
      glVertex3f(0.1 * Cos(i) - 0.4, 0.2, 0.1 * Sin(i) + 1.0);
   }
   glEnd();

   glNormal3f(-0.4, -1.0, 1.0);
   glBegin(GL_TRIANGLE_FAN);
   glTexCoord2f(0.5, 0.5);
   glVertex3f(-0.4, -1.0, 1.0);
   for (int i = 0; i <= 360; i += 30)
   {
      glNormal3f(Cos(i) - 0.4, -1.0, Sin(i) + 1.0);
      glTexCoord2f(0.5 * Cos(i) + 0.5, 0.5 * Sin(i) + 0.5);
      glVertex3f(0.1 * Cos(i) - 0.4, -1.0, 0.1 * Sin(i) + 1.0);
   }
   glEnd();

   // Draw Tent spikes.
   

   // Draw Tent ties.

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