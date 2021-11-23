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
   // Specify Tree translation at the origin.
   this->posX = 0.0;
   this->posY = 0.0;
   this->posZ = 0.0;

   // Specify default scaling of 1.0 to each axis.
   this->scaleX = 1.0;
   this->scaleY = 1.0;
   this->scaleZ = 1.0;

   // Specify default 0.0 rotation about each axis.
   this->rotX = 0.0;
   this->rotY = 0.0;
   this->rotZ = 0.0;
}

// Function definition for Tree class Constructor.
Tree::Tree(float x, float y, float z, float dx, float dy, float dz, float rx, float ry, float rz)
{
   // Specify Tree translation at desired x, y, z coordinates.
   this->posX = x;
   this->posY = y;
   this->posZ = z;

   // Specify desired x, y, z scaling.
   this->scaleX = dx;
   this->scaleY = dy;
   this->scaleZ = dz;

   // Specify desired rotation about x, y, z axes, respectively.
   this->rotX = rx;
   this->rotY = ry;
   this->rotZ = rz;
}

// Function definition for recursive branchFractal function (algorithm borrowed from in-class notes).
int Tree::branchFractal(float l0, float r0)
{
   // Compute random branching angle, branch length.
   int angle = rand()/RAND_MAX * (360 / BRANCH_NUM);
   float l = l0 * (rand() / RAND_MAX * (1.15 - 0.85) + 0.85);

   glPushMatrix();
   
   // Call branch based on random branch length.
   int ntri = this->branch(l, r0);
   glTranslatef(0, l, 0);

   // Base case: if branch length less than threshold, draw leaf.
   if (l < LEAF_SIZE)
   {
      glRotatef(angle, 0, 1, 0);

	  
      glRotatef(360/BRANCH_NUM, 0, 1, 0);
      ntri += this->leaf();
   }
   // Recursive case.
   else
   {
      // Shrink radius by branching factor, and length by branching factor.
      float r = SHRINK_FACTOR * r0;
      float left = BRANCH_RATIO * l0;

      // Make recursive calls to branchFractal for number of branches iterations.
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

// Function definition for branch method (algorithm borrowed from in-class notes).
int Tree::branch(float l, float r)
{
   // Apply transformations.
   glPushMatrix();
   glScaled(r, l, r);

   // Set Material/color properties.
   glColor4fv(brown);
   glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.0);
   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, brown);
   glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, Emission);

   // Enable textures, and apply bark texture to branches.
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D, texture);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

   // Enable back face culling.
   glEnable(GL_CULL_FACE);
   glCullFace(GL_BACK);
   glBegin(GL_QUAD_STRIP);

   // Code for branch generation borrowed from lecture, made a slight change by unrolling loop for optimization purposes.
   for (int i = 0; i <= 360; i += 60)
   {
      // Reduce number of floating-point calculations per loop iteration.
      float x = Cos(i);
      float z = Sin(i);
      float texX = i / 120.0;
      float x1 = Cos(i + 30);
      float z1 = Sin(i + 30);
      float texY = l/r;
      float texX1 = (i + 30) / 120.0;

      // Draw four vertices per iteration (loop unrolling).
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

   // Dicable textures, face culling.
   glEnd();
   glDisable(GL_CULL_FACE);
   glDisable(GL_TEXTURE_2D);
   glPopMatrix();

   return 24;
}

// Function definition for leaf method (algorithm borrowed from in-class notes).
int Tree::leaf()
{
   // Set texture, color for leaves, enable two-sided light model.
   glColor4fv(orange);
   glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
   glBindTexture(GL_TEXTURE_2D, leafTex);

   // Draw leaf.
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

   // Disable textures, two-sided light model.
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

   // Place recursive call to branchFractal with length 2.0 and radius 0.2.
   this->branchFractal(2.0, 0.2);
   glPopMatrix();
}

void Tree::resolveCollision(Camera* camera)
{
   // Reduce number of function calls, floating point computations per call to resolveCollision (optimization).
   float camX = camera->getEyeX();
   float camZ = camera->getEyeZ();
   float xOffset = (0.7 * Sin(camera->getTheta()));
   float zOffset = (0.7 * Cos(camera->getTheta()));
   float minX = (this->posX - this->scaleX * 0.2) - (xOffset + 0.5);
   float maxX = (this->posX + this->scaleX * 0.2) - (xOffset - 0.5);
   float minZ = (this->posZ - this->scaleZ * 0.2) + (zOffset - 0.5);
   float maxZ = (this->posZ + this->scaleZ * 0.2) + (zOffset + 0.5);

   // If Camera collides along x-axis and z-axis, collision needs to be resolved.
   if (camX < maxX && camX > minX && camZ < maxZ && camZ > minZ)
   {
      // Compute difference between Camera coordinates and minimum/maximum x, z values of the hitbox.
      float diffXMin = camX - minX;
      float diffXMax = maxX - camX;
      float diffZMin = camZ - minZ;
      float diffZMax = maxZ - camZ;

      // If collision is on the maximum x-coordinate, or maximum z-coordinate.
	  if (diffXMax < diffXMin && diffZMax < diffZMin)
	  {
         if(diffXMax < diffZMax)
            camera->setEyePos(maxX, camera->getEyeY(), camZ);
         else
            camera->setEyePos(camX, camera->getEyeY(), maxZ);
	  }
      // If collision is on the maximum x-coordinate, or minimum z-coordinate.
	  else if (diffXMax < diffXMin && diffZMin < diffZMax)
	  {
         if (diffXMax < diffZMin)
            camera->setEyePos(maxX, camera->getEyeY(), camZ);
         else
            camera->setEyePos(camX, camera->getEyeY(), minZ);
	  }
      // If collision is on the minimum x-coordinate, or maximum z-coordinate.
	  else if (diffXMin < diffXMax && diffZMax < diffZMin)
	  {
         if (diffXMin < diffZMax)
            camera->setEyePos(minX, camera->getEyeY(), camZ);
         else
            camera->setEyePos(camX, camera->getEyeY(), maxZ);
	  }
      // If collision is on the minimum x-coordinate or minimum z-coordinate.
	  else if (diffXMin < diffXMax && diffZMin < diffZMax)
	  {
         if (diffXMin < diffZMin)
            camera->setEyePos(minX, camera->getEyeY(), camZ);
         else
            camera->setEyePos(camX, camera->getEyeY(), minZ);
	  }
   }
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