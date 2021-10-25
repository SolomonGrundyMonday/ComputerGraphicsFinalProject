/*
 *   Class definition for Cuboid subclass of GameObject.
 * 
 *   Created by Jeff Colgan, October 25, 2021,
 *   CSCI-4229 Final Project : Haunted Forest project.
 * 
 *   This class creates and renders a basic cuboid object in OpenGL,
 *   applying lighting and texture to the object.  
 */
#include "Cuboid.h"

// Function definition for default constructor of Cuboid : GameObject class. DO NOT USE.
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

// Function definition for constructor of Cuboid : GameObject class.
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

// Function definition Initialize function for Cuboid : GameObject class.
int Cuboid::Initialize(const char* filename)
{
   texture = LoadTexBMP(filename);
   return 0;
}

// Function definition for Render function of Cuboid : GameObject class.
void Cuboid::Render()
{
   // Vectors and scalars for lighting, texture coordinates and materials.
   float black[] = {0.0, 0.0, 0.0, 1.0};
   float white[] = {1.0, 1.0, 1.0, 1.0};
   int shiny = 0;
   float X = this->xScale;
   float Z = this->zScale;

   // Bind to texture loaded in initialize function.
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D, texture);

   // Set object material parameters.
   glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);
   glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, white);
   glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);

   glPushMatrix();

   // Apply any applicable translations, rotations and scaling.
   glTranslated(this->xPos, this->yPos, this->zPos);
   glRotated(this->xRot, 1, 0, 0);
   glRotated(this->yRot, 0, 1, 0);
   glRotated(this->zRot, 0, 0, 1);
   glScaled(this->xScale, this->yScale, this->zScale);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);

   // Right face texture coordinates/vertices.
   glNormal3f(0.0, 0.0, 1.0);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, 1.0, 1.0);
   glTexCoord2f(0.0, X); glVertex3f(1.0, 1.0, 1.0);
   glTexCoord2f(X, X); glVertex3f(1.0, -1.0, 1.0);
   glTexCoord2f(X, 0.0); glVertex3f(-1.0, -1.0, 1.0);
   glEnd();

   // Left face texturecoordinates/vertices.
   glNormal3f(0.0, 0.0, -0.5);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0); glVertex3f(1.0, 1.0, -1.0);
   glTexCoord2f(0.0, X); glVertex3f(-1.0, 1.0, -1.0);
   glTexCoord2f(X, X); glVertex3f(-1.0, -1.0, -1.0);
   glTexCoord2f(X, 0.0); glVertex3f(1.0, -1.0, -1.0);
   glEnd();

   // Front face texture coordinates/vertices.
   glNormal3f(-0.5, 0.0, 0.0);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, 1.0, 1.0);
   glTexCoord2f(0.0, Z); glVertex3f(-1.0, -1.0, 1.0);
   glTexCoord2f(Z, Z); glVertex3f(-1.0, -1.0, -1.0);
   glTexCoord2f(Z, 0.0); glVertex3f(-1.0, 1.0, -1.0);
   glEnd();

   // Back face texture coordinates/vertices.
   glNormal3f(0.5, 0.0, 0.0);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0); glVertex3f(1.0, 1.0, 1.0);
   glTexCoord2f(0.0, Z); glVertex3f(1.0, -1.0, 1.0);
   glTexCoord2f(Z, Z); glVertex3f(1.0, -1.0, -1.0);
   glTexCoord2f(Z, 0.0); glVertex3f(1.0, 1.0, -1.0);
   glEnd();

   // Top face texture coordinates/vertices.
   glNormal3f(0.0, 0.5, 0.0);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0); glVertex3f(1.0, 1.0, 1.0);
   glTexCoord2f(0.0, X); glVertex3f(1.0, 1.0, -1.0);
   glTexCoord2f(Z, X); glVertex3f(-1.0, 1.0, -1.0);
   glTexCoord2f(Z, 0.0); glVertex3f(-1.0, 1.0, 1.0);
   glEnd();

   // Bottom face texture coordintates/vertices.
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

// Function definition for getPosX getter function of Cuboid : GameObject class.
float Cuboid::getPosX()
{
   return this->xPos;
}

// Function definition for getPosY getter function of Cuboid : GameObject class.
float Cuboid::getPosY()
{
   return this->yPos;
}

// Function definition for getPosZ getter function of Cuboid : GameObject class.
float Cuboid::getPosZ()
{
   return this->zPos;
}

// Function definition for getRotX getter function of Cuboid : GameObject class.
float Cuboid::getRotX()
{
   return this->xRot;
}

// Function definition for getRotY getter function of Cuboid : GameObject class.
float Cuboid::getRotY()
{
   return this->yRot;   
}

// Function definition for getRotZ getter function of Cuboid : GameObject class.
float Cuboid::getRotZ()
{
   return this->zRot;
}

// Function definition for getScaleX getter function of Cuboid : GameObject class.
float Cuboid::getScaleX()
{
   return this->xScale;
}

// Function definition for getScaleY getter function of Cuboid : GameObject class.
float Cuboid::getScaleY()
{
   return this->yScale;
}

// Function definition for getScaleZ getter function of Cuboid : GameObject class.
float Cuboid::getScaleZ()
{
   return this->zScale;
}

// Function definition for setPosition setter function of Cuboid : GameObject class.
void Cuboid::setPosition(float x, float y, float z)
{
   this->xPos = x;
   this->yPos = y;
   this->zPos = z;
}

// Function definition for setScale setter function of Cuboid : GameObject class.
void Cuboid::setScale(float x, float y, float z)
{
   this->xScale = x;
   this->yScale = y;
   this->zScale = z;
}

// Function definition for setRotation function of Cuboid : GameObject class.
void Cuboid::setRotation(float x, float y, float z)
{
   this->xRot = x;
   this->yRot = y;
   this->zRot = z;
}