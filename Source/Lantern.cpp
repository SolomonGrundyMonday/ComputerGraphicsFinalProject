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

   this->lightDir[0] = 0.0;
   this->lightDir[1] = 1.1;
   this->lightDir[2] = 0.0;
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

   this->lightDir[0] = 0.0;
   this->lightDir[1] = 0.5;
   this->lightDir[2] = 0.0;
}

// Function definition for Lantern class Initialize function implementation.
int Lantern::Initialize(const char* filename)
{
   this->texture = LoadTexBMP(filename);
   this->glass = LoadTexBMP("Assets/Metal.bmp");
   return 0;
}

// Function definition for Lantern class Render function implementation.
void Lantern::Render()
{
   float spotE[] = {90.0};
   float spotC[] = {15.0};
   float spotPosition[] = {0.0, 0.5, 0.0, 1.0};

   // Enable textures.
   glEnable(GL_TEXTURE_2D);
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

   // Draw lantern base.
   glBegin(GL_QUAD_STRIP);
   for (int i = 0; i <= 12; i++)
   {
      int theta = i * 30;
      float x = Cos(theta);
      float z = Sin(theta);

      glNormal3f(x, 0.0, z);
      glTexCoord2f(0.0, i * 1.0/12.0);
      glVertex3f(LANTERN_RAD * x, -1.0, LANTERN_RAD * z);
      glTexCoord2f(12.0, i * 1.0/12.0);
      glVertex3f(LANTERN_RAD * x, -0.6, LANTERN_RAD * z);
   }
   glEnd();

   glNormal3f(0.0, -1.0, 0.0);
   glBegin(GL_TRIANGLE_FAN);
   glTexCoord2f(0.5, 0.5);
   glVertex3f(0.0, -1.0, 0.0);
   for (int i = 0; i <= 360; i += 30)
   {
      glNormal3f(Cos(i), -1.0, Sin(i));
      glTexCoord2f(0.5 * Cos(i) + 0.5, 0.5 * Sin(i) + 0.5);
      glVertex3f(LANTERN_RAD * Cos(i), -1.0, LANTERN_RAD * Sin(i));
   }
   glEnd();

   glNormal3f(0.0, -0.6, 0.0);
   glBegin(GL_TRIANGLE_FAN);
   glTexCoord2f(0.5, 0.5);
   glVertex3f(0.0, -0.6, 0.0);
   for (int i = 0; i <= 360; i += 30)
   {
      glNormal3f(Cos(i), -0.6, Sin(i));
      glTexCoord2f(0.5 * Cos(i) + 0.5, 0.5 * Sin(i) + 0.5);
      glVertex3f(LANTERN_RAD * Cos(i), -0.6, LANTERN_RAD * Sin(i));
   }
   glEnd();

   // Draw lantern top.
   glBegin(GL_QUAD_STRIP);
   for (int i = 0; i <= 12; i++)
   {
      int theta = i * 30;
      float x = Cos(theta);
      float z = Sin(theta);

      glNormal3f(x, 0.6, z);
      glTexCoord2f(0.0, i * 1.0/12.0);
      glVertex3f(LANTERN_RAD * x, 0.6, LANTERN_RAD * z);
      glTexCoord2f(12.0, i * 1.0/12.0);
      glVertex3f(LANTERN_RAD * x, 1.0, LANTERN_RAD * z);
   }
   glEnd();

   glNormal3f(0.0, 1.0, 0.0);
   glBegin(GL_TRIANGLE_FAN);
   glTexCoord2f(0.5, 0.5);
   glVertex3f(0.0, 1.0, 0.0);
   for (int i = 0; i <= 360; i += 30)
   {
      glNormal3f(Cos(i), 1.0, Sin(i));
      glTexCoord2f(0.5 * Cos(i) + 0.5, 0.5 * Sin(i) + 0.5);
      glVertex3f(LANTERN_RAD * Cos(i), 1.0, LANTERN_RAD * Sin(i));
   }
   glEnd();

   glNormal3f(0.0, 0.6, 0.0);
   glBegin(GL_TRIANGLE_FAN);
   glTexCoord2f(0.5, 0.5);
   glVertex3f(0.0, 0.6, 0.0);
   for (int i = 0; i <= 360; i += 30)
   {
      glNormal3f(Cos(i), 0.6, Sin(i));
      glTexCoord2f(0.5 * Cos(i) + 0.5, 0.5 * Sin(i) + 0.5);
      glVertex3f(LANTERN_RAD * Cos(i), 0.6, LANTERN_RAD * Sin(i));
   }
   glEnd();

   // Draw lantern handle.
   glBegin(GL_QUAD_STRIP);
   for (int i = 0; i <= 12; i++)
   {
      int theta = i * 30;
      float z = Cos(theta);
      float y = Sin(theta);

      glNormal3f(-0.4, HANDLE_RAD * y + 1.6, HANDLE_RAD * z);
      glTexCoord2f(0.0, i * 1.0/12.0);
      glVertex3f(-0.4, HANDLE_RAD * y + 1.6, HANDLE_RAD * z);
      glTexCoord2f(12.0, i * 1.0/12.0);
      glVertex3f(0.4, HANDLE_RAD * y + 1.6, HANDLE_RAD * z);
   }
   glEnd();

   glNormal3f(-0.4, 1.6, 0.0);
   glBegin(GL_TRIANGLE_FAN);
   glTexCoord2f(0.5, 0.5);
   glVertex3f(-0.4, 1.6, 0.0);
   for (int i = 0; i <= 360; i += 30)
   {
      glNormal3f(-0.4, Sin(i), Cos(i));
      glTexCoord2f(0.5 * Cos(i) + 0.5, 0.5 * Sin(i) + 0.5);
      glVertex3f(-0.4, HANDLE_RAD * Sin(i) + 1.6, HANDLE_RAD * Cos(i));
   }
   glEnd();

   glNormal3f(0.4, 1.6, 0.0);
   glBegin(GL_TRIANGLE_FAN);
   glTexCoord2f(0.5, 0.5);
   glVertex3f(0.4, 1.6, 0.0);
   for (int i = 0; i <= 360; i += 30)
   {
      glNormal3f(0.4, Sin(i), Cos(i));
      glTexCoord2f(0.5 * Cos(i) + 0.5, 0.5 * Sin(i) + 0.5);
      glVertex3f(0.4, HANDLE_RAD * Sin(i) + 1.6, HANDLE_RAD * Cos(i));
   }
   glEnd();

   // Draw lantern handle connectors.
   glBegin(GL_QUAD_STRIP);
   for (int i = 0; i <= 12; i++)
   {
      int theta = i * 30;
      float x = Cos(theta);
      float z = Sin(theta);

      glNormal3f(x, 1.3, z);
      glTexCoord2f(0.0, i * 1.0/12.0);
      glVertex3f(0.01 * x + 0.4, 1.6, 0.01 * z);
      glTexCoord2f(12.0, i * 1.0/12.0);
      glVertex3f(0.01 * x + 0.4, 1.0, 0.01 * z);
   }
   glEnd();

   glBegin(GL_QUAD_STRIP);
   for (int i = 0; i <= 12; i++)
   {
      int theta = i * 30;
      float x = Cos(theta);
      float z = Sin(theta);

      glNormal3f(-x, 1.3, z);
      glTexCoord2f(0.0, i * 1.0/12.0);
      glVertex3f(-0.01 * x - 0.4, 1.6, 0.01 * z);
      glTexCoord2f(12.0, i * 1.0/12.0);
      glVertex3f(-0.01 * x - 0.4, 1.0, 0.01 * z);
   }
   glEnd();

   // Draw lantern glass casing.
   // GL_BLEND info citation from this stack overflow thread:
   // https://stackoverflow.com/questions/24399431/opengl-texture-with-transparency-alpha
   glBindTexture(GL_TEXTURE_2D, glass);
   glColor4fv(white);
   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

   glBegin(GL_QUAD_STRIP);
   for (int i = 0; i <= 12; i++)
   {
      int theta = i * 30;
      float x = Cos(theta);
      float z = Sin(theta);

      glNormal3f(x, 0.0, z);
      glTexCoord2f(0.0, i * 1.0/12.0);
      glVertex3f(LANTERN_RAD * x, -0.6, LANTERN_RAD * z);
      glTexCoord2f(12.0, i * 1.0/12.0);
      glVertex3f(LANTERN_RAD * x, 0.6, LANTERN_RAD * z);
   }
   glEnd();

   glDisable(GL_CULL_FACE);
   // Draw lantern bulb.
   glBegin(GL_QUAD_STRIP);
   for (int i = 0; i <= 12; i++)
   {
      int theta = i * 30;
      float x = Cos(theta);
      float z = Sin(theta);

      glNormal3f(x, -0.4, z);
      glTexCoord2f(0.0, i * 1.0/12.0);
      glVertex3f(BULB_RAD * x, -0.6, BULB_RAD * z);
      glTexCoord2f(12.0, i * 1.0/12.0);
      glVertex3f(BULB_RAD * x, -0.2, BULB_RAD * z);
   }
   glEnd();

   glNormal3f(0.0, -0.1, 0.0);
   glBegin(GL_TRIANGLE_FAN);
   glTexCoord2f(0.5, 0.5);
   glVertex3f(0.0, -0.1, 0.0);
   for (int i = 0; i <= 360; i += 30)
   {
      glNormal3f(Cos(i), -0.15, Sin(i));
      glTexCoord2f(0.5 * Cos(i) + 0.5, 0.5 * Sin(i) + 0.5);
      glVertex3f(BULB_RAD * Cos(i), -0.2, BULB_RAD * Sin(i));
   }
   glEnd();

   // Set up light source.
   glLoadIdentity();
   glEnable(GL_LIGHT0);
   glLightfv(GL_LIGHT0, GL_AMBIENT, Ambient);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, Diffuse);
   glLightfv(GL_LIGHT0, GL_SPECULAR, Specular);
   glLightfv(GL_LIGHT0, GL_POSITION, spotPosition);
   glLightfv(GL_LIGHT0, GL_SPOT_EXPONENT, spotE);
   glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF, spotC);

   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
   glDisable(GL_BLEND);
   glEnable(GL_CULL_FACE);
}

// Function definition for Lantern class resolveCollision function implementation.
void Lantern::resolveCollision(Camera* camera)
{
   // Do stuff here.
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
