/*
 *   Tree class definition.
 *   Created by Jeff Colgan, October 25, 2021,
 *   CSCI-4229 Computer Graphics : Final Project.
 *   
 *   Function definitions for the Tree class used in the Computer Graphics
 *   Final Project.
 */

#include "Tree.h"

// Function definition for Tree class default constructor.
Tree::Tree()
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

// Function definition for Tree class Constructor.
Tree::Tree(float x, float y, float z, float dx, float dy, float dz, float rx, float ry, float rz)
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

// Function definition for recursive branchFractal function (borrowed from in-class notes).
int Tree::branchFractal(float l0, float r0)
{
   int angle = rand()/RAND_MAX * (360 / BRANCH_NUM);
   float l = l0 * (rand()/RAND_MAX*(1.15-0.85)+0.85);

   glPushMatrix();
   
   int ntri = this->branch(l, r0);
   glTranslatef(0, l, 0);

   if (l < LEAF_SIZE)
   {
      glRotatef(angle, 0, 1, 0);

	  
      glRotatef(360/BRANCH_NUM, 0, 1, 0);
      ntri += this->leaf();
   }
   else
   {
      float r = SHRINK_FACTOR * r0;
      float left = BRANCH_RATIO * l0;

	  for (int i = 0; i < BRANCH_NUM; i++)
	  {
         glPushMatrix();
         glRotatef(angle + i * 360 / BRANCH_NUM, 0, 1, 0);
         glRotatef(30.0, 1, 0, 0);
         ntri += this->branchFractal(left, r);
         glPopMatrix();
	  }
   }

   glColor4fv(white);
   glPopMatrix();
   return ntri;
}

// Function definition for branch method (algorithm from in-class notes).
int Tree::branch(float l, float r)
{
   glPushMatrix();
   glScaled(r, l, r);

   glColor4fv(brown);
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D, texture);
   

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glEnable(GL_CULL_FACE);
   glCullFace(GL_BACK);
   glBegin(GL_QUAD_STRIP);

   for (int i = 0; i <= 360; i += 60)
   {
      float x = Cos(i);
      float z = Sin(i);
      float texX = i / 120.0;
      float x1 = Cos(i + 30);
      float z1 = Sin(i + 30);
      float texY = l/r;
      float texX1 = (i + 30) / 120.0;

      glNormal3f(x, 1 - SHRINK_FACTOR, z);
      glTexCoord2d(texX, 0.0);
      glVertex3f(x, 0, z);
      glTexCoord2d(texX, texY);
      glVertex3f(SHRINK_FACTOR * x, 1, SHRINK_FACTOR * z);

      glNormal3f(x1, 1 - SHRINK_FACTOR, z1);
      glTexCoord2d(texX1, 0.0);
      glVertex3f(x1, 0, z1);
      glTexCoord2d(texX1, texY);
      glVertex3f(SHRINK_FACTOR * x1, 1, SHRINK_FACTOR * z1);
   }

   glEnd();
   glDisable(GL_CULL_FACE);
   glDisable(GL_TEXTURE_2D);
   glPopMatrix();

   return 24;
}

// Function definition for leaf method (algorithm borrowed from in-class notes).
int Tree::leaf()
{

   glColor4fv(orange);
   glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
   glBindTexture(GL_TEXTURE_2D, leafTex);

   glNormal3f(0, 0, 1);
   glBegin(GL_QUADS);
   glTexCoord2d(0.0, 0.0);
   glVertex3f(0.0, 0.0, 0.0);
   glTexCoord2d(0.0, 1.0);
   glVertex3f(-0.03, 0.03, 0.0);
   glTexCoord2d(1.0, 0.0);
   glVertex3f(0.0, 0.1, 0.0);
   glTexCoord2d(1.0, 1.0);
   glVertex3f(0.03, 0.03, 0.0);
   glEnd();

   glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 0);
   glDisable(GL_TEXTURE_2D);
   return 2;
}

// Function definition for Tree class Initialize function implementation.
int Tree::Initialize(const char* filename)
{
   // Import texture here, need good bark picture to use.
   texture = LoadTexBMP(filename);
   leafTex = LoadTexBMP("Assets/Leaf.bmp");
   return 0;
}

// Function definition for Tree class Render function implementation.
void Tree::Render()
{
   glPushMatrix();

   // Apply translation, rotation and scaling.
   glTranslated(this->posX, this->posY, this->posZ);
   glRotated(this->rotX, 1, 0, 0);
   glRotated(this->rotY, 0, 1, 0);
   glRotated(this->rotZ, 0, 0, 1);
   glScaled(this->scaleX, this->scaleY, this->scaleZ);

   this->branchFractal(2.0, 0.2);
   glPopMatrix();
}

void Tree::resolveCollision(Camera* camera)
{
   // Do stuff here.
}

// Function definition for Tree class setPosition setter function.
void Tree::setPosition(float x, float y, float z)
{
   this->posX = x;
   this->posY = y;
   this->posZ = z;
}

// Function definition for Tree class setScale setter function.
void Tree::setScale(float x, float y, float z)
{
   this->scaleX = x;
   this->scaleY = y;
   this->scaleZ = z;
}

// Function definition for Tree class setRotation setter function.
void Tree::setRotation(float x, float y, float z)
{
   this->rotX = x;
   this->rotY = y;
   this->rotZ = z;
}

// Function definition for Tree class getPosX getter function.
float Tree::getPosX()
{
   return this->posX;
}

// Function definition for Tree class getPosY getter function.
float Tree::getPosY()
{
   return this->posY;
}

// Function definition for Tree class getPosZ getter function.
float Tree::getPosZ()
{
   return this->posZ;
}

// Function definition for Tree class getScaleX getter function.
float Tree::getScaleX()
{
   return this->scaleX;
}

// Function definition for Tree class getScaleY getter function.
float Tree::getScaleY()
{
   return this->scaleY;
}

// Function definition for Tree class getScaleZ getter funcction.
float Tree::getScaleZ()
{
   return this->scaleZ;
}

// Function definition for Tree class getRotX getter function.
float Tree::getRotX()
{
   return this->rotX;
}

// Function definition for Tree class getRotY getter funcction.
float Tree::getRotY()
{
   return this->rotY;
}

// Function definition for Tree class getRotZ getter function.
float Tree::getRotZ()
{
   return this->rotZ;
}