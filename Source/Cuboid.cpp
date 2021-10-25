#include "Cuboid.h"

Cuboid::Cuboid()
{
   this->xPos = 0.0;
   this->yPos = 0.0;
   this->zPos = 0.0;
   this->xScale = 1.0;
   this->yScale = 1.0;
   this->zScale = 1.0;
   this->xRot = 0.0;
   this->yRot = 0.0;
   this->zRot = 0.0;
}

Cuboid::Cuboid(float x, float y, float z, float scaleX, float scaleY, float scaleZ, float rotX, float rotY, float rotZ)
{
   this->xPos = x;
   this->yPos = y;
   this->zPos = z;
   this->xScale = scaleX;
   this->yScale = scaleY;
   this->zScale = scaleZ;
   this->xRot = rotX;
   this->yRot = rotY;
   this->zRot = rotZ;
}

Cuboid::~Cuboid()
{
   
}

int Cuboid::Initialize(const char* filename)
{
   texture = LoadTexBMP(filename);
   return 0;
}

void Cuboid::Render()
{
   float black[] = {0.0, 0.0, 0.0, 1.0};
   float white[] = {1.0, 1.0, 1.0, 1.0};
   int shiny = 0;
   float X = this->xScale;
   float Z = this->zScale;

   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D, texture);

   glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);
   glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, white);
   glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);

   glPushMatrix();

   glTranslated(this->xPos, this->yPos, this->zPos);
   glRotated(this->xRot, 1, 0, 0);
   glRotated(this->yRot, 0, 1, 0);
   glRotated(this->zRot, 0, 0, 1);
   glScaled(this->xScale, this->yScale, this->zScale);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);

   glNormal3f(0.0, 0.0, 1.0);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0); glVertex3f(1.0, 1.0, 1.0);
   glTexCoord2f(0.0, X); glVertex3f(-1.0, 1.0, -1.0);
   glTexCoord2f(X, X); glVertex3f(-1.0, -1.0, -1.0);
   glTexCoord2f(X, 0.0); glVertex3f(1.0, -1.0, -1.0);
   glEnd();

   glNormal3f(0.0, 0.0, -0.5);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0); glVertex3f(1.0, 1.0, -1.0);
   glTexCoord2f(0.0, X); glVertex3f(-1.0, 1.0, -1.0);
   glTexCoord2f(X, X); glVertex3f(-1.0, -1.0, -1.0);
   glTexCoord2f(X, 0.0); glVertex3f(1.0, -1.0, -1.0);
   glEnd();

   glNormal3f(-0.5, 0.0, 0.0);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, 1.0, 1.0);
   glTexCoord2f(0.0, Z); glVertex3f(-1.0, -1.0, 1.0);
   glTexCoord2f(Z, Z); glVertex3f(-1.0, -1.0, -1.0);
   glTexCoord2f(Z, 0.0); glVertex3f(-1.0, 1.0, -1.0);
   glEnd();

   glNormal3f(0.5, 0.0, 0.0);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0); glVertex3f(1.0, 1.0, 1.0);
   glTexCoord2f(0.0, Z); glVertex3f(1.0, -1.0, -1.0);
   glTexCoord2f(Z, Z); glVertex3f(1.0, -1.0, -1.0);
   glTexCoord2f(Z, 0.0); glVertex3f(1.0, 1.0, -1.0);
   glEnd();

   glNormal3f(0.0, 0.5, 0.0);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0); glVertex3f(1.0, 1.0, 1.0);
   glTexCoord2f(0.0, X); glVertex3f(1.0, 1.0, -1.0);
   glTexCoord2f(Z, X); glVertex3f(-1.0, 1.0, -1.0);
   glTexCoord2f(Z, 0.0); glVertex3f(-1.0, 1.0, 1.0);
   glEnd();

   glNormal3f(0.0, -0.5, 0.0);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0); glVertex3f(1.0, -1.0, 1.0);
   glTexCoord2f(0.0, X); glVertex3f(1.0, -1.0, -1.0);
   glTexCoord2f(Z, X); glVertex3f(-1.0, -1.0, -1.0);
   glTexCoord2f(Z, 0.0); glVertex3f(-1.0, -1.0, 1.0);
   glEnd();

   glDisable(GL_TEXTURE_2D);
   glPopMatrix();
}

float Cuboid::getPosX()
{
   return this->xPos;
}

float Cuboid::getPosY()
{
   return this->yPos;
}

float Cuboid::getPosZ()
{
   return this->zPos;
}

float Cuboid::getRotX()
{
   return this->xRot;
}

float Cuboid::getRotY()
{
   return this->yRot;   
}

float Cuboid::getRotZ()
{
   return this->zRot;
}

float Cuboid::getScaleX()
{
   return this->xScale;
}

float Cuboid::getScaleY()
{
   return this->yScale;
}

float Cuboid::getScaleZ()
{
   return this->zScale;
}

void Cuboid::setPosition(float x, float y, float z)
{
   this->xPos = x;
   this->yPos = y;
   this->zPos = z;
}

void Cuboid::setScale(float x, float y, float z)
{
   this->xScale = x;
   this->yScale = y;
   this->zScale = z;
}

void Cuboid::setRotation(float x, float y, float z)
{
   this->xRot = x;
   this->yRot = y;
   this->zRot = z;
}