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
   // Recursive step.
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
   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, brown);

   // Enable textures, and apply bark texture to branches.
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D, texture);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

   // Enable back face culling.
   glEnable(GL_CULL_FACE);
   glCullFace(GL_BACK);
   glBegin(GL_QUAD_STRIP);

   // Optimization - since the texture coordinate y-value is the same for every iteration, no need to calculate it every iteration of the loop.
   float texY = l / r;

   // Code for branch generation borrowed from lecture, made a slight change by unrolling loop for optimization purposes.
   for (int i = 0; i <= 360; i += 60)
   {
      // Optimization - reduce number of floating-point calculations per loop iteration.
      float x = Cos(i);
      float z = Sin(i);
      float texX = i / 120.0;
      
      glNormal3f(x, 0.0, z);
      glTexCoord2d(texX, 0.0);
      glVertex3f(x, 0, z);
      glTexCoord2d(texX, texY);
      glVertex3f(SHRINK_FACTOR * x, 1, SHRINK_FACTOR * z);

      // Draw four vertices per iteration (loop unrolling).
      if (i != 360)
      {
         int next = i + 30;

         // Optimization - reduce number of floating-point compuatations per loop iteration.
         float x1 = Cos(next);
         float z1 = Sin(next);
         float texX1 = (next) / 120.0;

         glNormal3f(x1, 0.0, z1);
         glTexCoord2d(texX1, 0.0);
         glVertex3f(x1, 0, z1);
         glTexCoord2d(texX1, texY);
         glVertex3f(SHRINK_FACTOR * x1, 1, SHRINK_FACTOR * z1);
      }
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
   // Import object textures from the Assets subdirectory.
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
   this->branchFractal(1.7, 0.2);
   glPopMatrix();
}

// Function definition for Tree class getSide helper function.
wall Tree::getSide(Camera* camera)
{
   // Compute the relative x, z coordinates and convert to object coordinates.
   float cosine = Cos(this->rotY);
   float sine = Sin(this->rotY);
   float camX = camera->getEyeX() - this->posX;
   float camZ = camera->getEyeZ() - this->posZ;
   float objX = (camX * cosine) - (camZ * sine);
   float objZ = (camZ * cosine) + (camX * sine);

   float diffXMin = objX - ((-this->scaleX * 0.2) - 0.55);
   float diffXMax = ((this->scaleX * 0.2) + 0.55) - objX;
   float diffZMin = objZ - ((-this->scaleZ * 0.2) - 0.55);
   float diffZMax = ((this->scaleZ * 0.2 + 0.55)) - objZ;

   // Determine the wall of the hitbox that is experiencing the collision.
   bool left = diffXMin < diffXMax && diffXMin < diffZMin && diffXMin < diffZMax;
   bool right = diffXMax < diffXMin && diffXMax < diffZMin && diffXMax < diffZMax;
   bool front = diffZMin < diffZMax && diffZMin < diffXMin && diffZMin < diffXMax;
   bool back = diffZMax < diffZMin && diffZMax < diffXMin && diffZMax < diffXMax;

   // Return the appropriate wall.
   if (front)
      return FRONT;
   else if (back)
      return BACK;
   else if (left)
      return LEFT;
   else if (right)
      return RIGHT;
   else
      return NONE;
}

// Function definition for Tree class detectCollision function.
bool Tree::detectCollision(Camera* camera)
{
   // Compute the relative x, z coordinates and convert to object coordinates.
   float cosine = Cos(this->rotY);
   float sine = Sin(this->rotY);
   float camX = camera->getEyeX() - this->posX;
   float camZ = camera->getEyeZ() - this->posZ;
   float objX = (camX * cosine) - (camZ * sine);
   float objZ = (camZ * cosine) + (camX * sine);

   // Compute x, z minimum and maximum values for object hitbox.
   float minX = (-this->scaleX * 0.2) - 0.55;
   float maxX = (this->scaleX * 0.2) + 0.55;
   float minZ = (-this->scaleZ * 0.2) - 0.55;
   float maxZ = (this->scaleZ * 0.2) + 0.55;

   // Determine if Camera is colliding with the object along x, z axes.
   bool xCollide = objX > minX && objX < maxX;
   bool zCollide = objZ > minZ && objZ < maxZ;

   return xCollide && zCollide;
}

// Function definition for Tree class resolveCollision function.
void Tree::resolveCollision(Camera* camera)
{
   // Reduce number of function calls, floating point computations per call to resolveCollision (optimization).
   float cosine = Cos(this->posY);
   float sine = Sin(this->posY);
   float camX = camera->getEyeX() - this->posX;
   float camZ = camera->getEyeZ() - this->posZ;
   float objX = (camX * cosine) - (camZ * sine);
   float objZ = (camZ * cosine) - (camX * sine);

   // Compute minimum and maximum x, z values.
   float minX = (-this->scaleX * 0.2) - 0.55;
   float maxX = (this->scaleX * 0.2) + 0.55;
   float minZ = (-this->scaleZ * 0.2) - 0.55;
   float maxZ = (this->scaleZ * 0.2) + 0.55;

   wall collision = getSide(camera);
   glWindowPos2i(5, 25);

   // Update Camera eye position based on which wall of the hitbox is experiencing the collision.
   if (collision == FRONT)
   {
      float newX, newZ;

      newX = objX;
      newZ = minZ;

      // Undo trnasformation and convert back to world coordinates (transform matrix inverse courtesy of Symbolab).
      newX = -(newX * cosine / (-sine * sine - cosine * cosine)) - (newZ * sine / (-sine * sine - cosine * cosine));
      newZ = (objX * sine / (-sine * sine - cosine * cosine)) - (newZ * cosine / (-sine * sine - cosine * cosine));
      newX += this->posX;
      newZ += this->posZ;

      // Update camera position.
      camera->setEyePos(newX, camera->getEyeY(), newZ);
   }
   else if (collision == BACK)
   {
      float newX, newZ;

      newX = objX;
      newZ = maxZ;

      // Undo transformation and convert back to world coordinates (transform matrix inverse courtesy of Symbolab).
      newX = -(newX * cosine / (-sine * sine - cosine * cosine)) - (newZ * sine / (-sine * sine - cosine * cosine));
      newZ = (objX * sine / (-sine * sine - cosine * cosine)) - (newZ * cosine / (-sine * sine - cosine * cosine));
      newX += this->posX;
      newZ += this->posZ;

      // Update Camera position.
      camera->setEyePos(newX, camera->getEyeY(), newZ);
   }
   else if (collision == LEFT)
   {
      float newX, newZ;

      newX = minX;
      newZ = objZ;

      // Undo transformation and convert back to world coordinates (transform matrix inverse courtesy of Symbolab).
      newZ = (newX * sine / (-sine * sine - cosine * cosine)) - (newZ * cosine / (-sine * sine - cosine * cosine));
      newX = -(newX * cosine / (-sine * sine - cosine * cosine)) - (objZ * sine / (-sine * sine - cosine * cosine));
      newX += this->posX;
      newZ += this->posZ;

      // Update Camera position.
      camera->setEyePos(newX, camera->getEyeY(), newZ);
   }
   else if (collision == RIGHT)
   {
      float newX, newZ;

      newX = maxX;
      newZ = objZ;

      // Undo transformation and convert back to world coordinates (transform matrix inverse courtesy of Symbolab).
      newZ = (newX * sine / (-sine * sine - cosine * cosine)) - (newZ * cosine / (-sine * sine - cosine * cosine));
      newX = -(newX * cosine / (-sine * sine - cosine * cosine)) - (objX * sine / (-sine * sine - cosine * cosine));
      newX += this->posX;
      newZ += this->posZ;

      // Update Camera position.
      camera->setEyePos(newX, camera->getEyeY(), newZ);
   }
}

// Function definition for Tree class setPosition setter function.
void Tree::setPosition(float x, float y, float z)
{
   // Set object translation coordinates.
   this->posX = x;
   this->posY = y;
   this->posZ = z;
}

// Function definition for Tree class setScale setter function.
void Tree::setScale(float x, float y, float z)
{
   // Set object scaling.
   this->scaleX = x;
   this->scaleY = y;
   this->scaleZ = z;
}

// Function definition for Tree class setRotation setter function.
void Tree::setRotation(float x, float y, float z)
{
   // Set object rotation about each axis.
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