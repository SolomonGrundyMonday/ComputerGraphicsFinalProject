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

// Function definition for constructor of Cuboid : GameObject class.
Cuboid::Cuboid(float x, float y, float z, float scaleX, float scaleY, float scaleZ, float rotX, float rotY, float rotZ)
{
   this->posX = x;
   this->posY = y;
   this->posZ = z;
   this->scaleX = scaleX;
   this->scaleY = scaleY;
   this->scaleZ = scaleZ;
   this->rotX = rotX;
   this->rotY = rotY;
   this->rotZ = rotZ;
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
   float white[] = {1.0, 1.0, 1.0, 1.0};
   float Emission[] = {0.0, 0.0, 0.0, 1.0};

   // Set object material parameters.
   glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.0);
   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
   glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, Emission);

   glPushMatrix();
   glColor3f(1.0, 1.0, 1.0);

   // Apply any applicable translations, rotations and scaling.
   glTranslated(this->posX, this->posY, this->posZ);
   glRotated(this->rotX, 1, 0, 0);
   glRotated(this->rotY, 0, 1, 0);
   glRotated(this->rotZ, 0, 0, 1);
   glScaled(this->scaleX, this->scaleY, this->scaleZ);

   // Bind to texture loaded in initialize function.
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D, texture);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);

   // Right face texture coordinates/vertices.
   glNormal3f(0.0, 0.0, 1.0);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, 1.0, 1.0);
   glTexCoord2f(0.0, this->scaleZ); glVertex3f(1.0, 1.0, 1.0);
   glTexCoord2f(this->scaleY, this->scaleZ); glVertex3f(1.0, -1.0, 1.0);
   glTexCoord2f(this->scaleY, 0.0); glVertex3f(-1.0, -1.0, 1.0);
   glEnd();

   // Left face texturecoordinates/vertices.
   glNormal3f(0.0, 0.0, -1.0);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0); glVertex3f(1.0, 1.0, -1.0);
   glTexCoord2f(0.0, this->scaleZ); glVertex3f(-1.0, 1.0, -1.0);
   glTexCoord2f(this->scaleY, this->scaleZ); glVertex3f(-1.0, -1.0, -1.0);
   glTexCoord2f(this->scaleY, 0.0); glVertex3f(1.0, -1.0, -1.0);
   glEnd();

   // Front face texture coordinates/vertices.
   glNormal3f(-1.0, 0.0, 0.0);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, 1.0, 1.0);
   glTexCoord2f(0.0, this->scaleY); glVertex3f(-1.0, -1.0, 1.0);
   glTexCoord2f(this->scaleX, this->scaleY); glVertex3f(-1.0, -1.0, -1.0);
   glTexCoord2f(this->scaleX, 0.0); glVertex3f(-1.0, 1.0, -1.0);
   glEnd();

   // Back face texture coordinates/vertices.
   glNormal3f(1.0, 0.0, 0.0);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0); glVertex3f(1.0, 1.0, 1.0);
   glTexCoord2f(0.0, this->scaleY); glVertex3f(1.0, -1.0, 1.0);
   glTexCoord2f(this->scaleX, this->scaleY); glVertex3f(1.0, -1.0, -1.0);
   glTexCoord2f(this->scaleX, 0.0); glVertex3f(1.0, 1.0, -1.0);
   glEnd();

   // Top face texture coordinates/vertices (tesselated to improve lighting effects for large polygons)
   // Idea borrowed from contents of https://www.glprogramming.com/red/chapter05.html.
   for (int i = -this->scaleX; i < this->scaleX; i++)
   {
      for (int j = -this->scaleZ; j < this->scaleZ; j++)
      {
         float minX = i / this->scaleX;
         float maxX = (i + 1) / this->scaleX;
         float minZ = j / this->scaleZ;
         float maxZ = (j + 1) / this->scaleZ;

         glNormal3f( (maxX - minX) / 2.0, 1.0, (maxZ - minZ) / 2.0);
         glBegin(GL_QUADS);
         glTexCoord2f(0.0, 0.0); glVertex3f(maxX, 1.0, maxZ);
         glTexCoord2f(0.0, 1.0); glVertex3f(maxX, 1.0, minZ);
         glTexCoord2f(1.0, 1.0); glVertex3f(minX, 1.0, minZ);
         glTexCoord2f(1.0, 0.0); glVertex3f(minX, 1.0, maxZ);
         glEnd();
      }
   }

   // Bottom face texture coordintates/vertices.
   glNormal3f(0.0, -1.0, 0.0);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0); glVertex3f(1.0, -1.0, 1.0);
   glTexCoord2f(0.0, this->scaleX); glVertex3f(1.0, -1.0, -1.0);
   glTexCoord2f(this->scaleZ, this->scaleX); glVertex3f(-1.0, -1.0, -1.0);
   glTexCoord2f(this->scaleZ, 0.0); glVertex3f(-1.0, -1.0, 1.0);
   glEnd();

   glDisable(GL_TEXTURE_2D);
   glPopMatrix();
}

// Function definition for Cuboid class resolveCollision function implementation.
void Cuboid::resolveCollision(Camera* camera)
{
   // For now, there is no need to implement collisions for Cuboid as it is currently only used as the floor.
}

// Function definition for getPosX getter function of Cuboid : GameObject class.
float Cuboid::getPosX()
{
   return this->posX;
}

// Function definition for getPosY getter function of Cuboid : GameObject class.
float Cuboid::getPosY()
{
   return this->posY;
}

// Function definition for getPosZ getter function of Cuboid : GameObject class.
float Cuboid::getPosZ()
{
   return this->posZ;
}

// Function definition for getRotX getter function of Cuboid : GameObject class.
float Cuboid::getRotX()
{
   return this->rotX;
}

// Function definition for getRotY getter function of Cuboid : GameObject class.
float Cuboid::getRotY()
{
   return this->rotY;   
}

// Function definition for getRotZ getter function of Cuboid : GameObject class.
float Cuboid::getRotZ()
{
   return this->rotZ;
}

// Function definition for getScaleX getter function of Cuboid : GameObject class.
float Cuboid::getScaleX()
{
   return this->scaleX;
}

// Function definition for getScaleY getter function of Cuboid : GameObject class.
float Cuboid::getScaleY()
{
   return this->scaleY;
}

// Function definition for getScaleZ getter function of Cuboid : GameObject class.
float Cuboid::getScaleZ()
{
   return this->scaleZ;
}

// Function definition for setPosition setter function of Cuboid : GameObject class.
void Cuboid::setPosition(float x, float y, float z)
{
   this->posX = x;
   this->posY = y;
   this->posZ = z;
}

// Function definition for setScale setter function of Cuboid : GameObject class.
void Cuboid::setScale(float x, float y, float z)
{
   this->scaleX = x;
   this->scaleY = y;
   this->scaleZ = z;
}

// Function definition for setRotation function of Cuboid : GameObject class.
void Cuboid::setRotation(float x, float y, float z)
{
   this->rotX = x;
   this->rotY = y;
   this->rotZ = z;
}