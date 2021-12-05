/*
 *   HedgeWall class definition.
 *   Created by Jeff Colgan, November 25, 2021.
 *   Computer Graphics Final Project. 
 */

#include "HedgeWall.h"

// Function definition for CaveWall class default constructor.
HedgeWall::HedgeWall()
{
   // Specify object's translation at the origin.
   this->posX = 0.0;
   this->posY = 0.0;
   this->posZ = 0.0;

   // Specify object's scaling as 1.0  on all axes.
   this->scaleX = 1.0;
   this->scaleY = 1.0;
   this->scaleZ = 1.0;

   // Specify object's rotation as 0.0 about each axis.
   this->rotX = 0.0;
   this->rotY = 0.0;
   this->rotZ = 0.0;
}

// Function definition for CaveWall class constructor.
HedgeWall::HedgeWall(float x, float y, float z, float dx, float dy, float dz, float rx, float ry, float rz)
{
   // Specify object's translation at the desired coordinates.
   this->posX = x;
   this->posY = y;
   this->posZ = z;

   // Specify object's scaling at the desired values.
   this->scaleX = dx;
   this->scaleY = dy;
   this->scaleZ = dz;

   // Specify object's rotation about each axis at the desired values.
   this->rotX = rx;
   this->rotY = ry;
   this->rotZ = rz;
}

// Function definition for CaveWall Initialize function implementation.
int HedgeWall::Initialize(const char* filename)
{
   texture = LoadTexBMP(filename);

   return 0;
}

// Function definition for CaveWall Render function implementation.
void HedgeWall::Render()
{
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

   // Wall long side.  (Tesselated to improve lighing effects on large polygons)
   // Idea borrowed from contents of https://www.glprogramming.com/red/chapter05.html.
   // Using a while loop/floating-point counter is intentional here.  This allows me to still
   // tesselate the surface of the polygon even if the scaling is by a non-integer factor.
   float i = -this->scaleX;
   while (i < this->scaleX)
   {
      float j = -this->scaleY;
      while (j < this->scaleY)
      {
         float minX = i / this->scaleX;
         float maxX = (i + 1 > this->scaleX) ? 1.0 : (i + 1) / this->scaleX;
         float minY = j / this->scaleY;
         float maxY = (j + 1 > this->scaleY) ? 1.0 : (j + 1) / this->scaleY;

         // Interior wall.
         glNormal3f(0.0, 0.0, 1.0);
         glBegin(GL_QUADS);
         glTexCoord2f(0.0, 0.0);
         glVertex3f(maxX, minY, -1.0);
         glTexCoord2f(1.0, 0.0);
         glVertex3f(minX, minY, -1.0);
         glTexCoord2f(1.0, 1.0);
         glVertex3f(minX, maxY, -1.0);
         glTexCoord2f(0.0, 1.0);
         glVertex3f(maxX, maxY, -1.0);
         glEnd();

         // Exterior wall.
         glNormal3f(0.0, 0.0, -1.0);
         glBegin(GL_QUADS);
         glTexCoord2f(0.0, 0.0);
         glVertex3f(maxX, minY, -1.2);
         glTexCoord2f(1.0, 0.0);
         glVertex3f(minX, minY, -1.2);
         glTexCoord2f(1.0, 1.0);
         glVertex3f(minX, maxY, -1.2);
         glTexCoord2f(0.0, 1.0);
         glVertex3f(maxX, maxY, -1.2);
         glEnd();

         j += 1.0;
      }
      i += 1.0;
   }

   // Wall end caps. (Tesselated to improve lighing effects on large polygons)
   // Idea borrowed from contents of https://www.glprogramming.com/red/chapter05.html.
   // Using a while loop with a floating-point counter is intentional here, this allows me to still
   // tesselate the surface of the polygon even if the scaling is not a whole number.
   i = -this->scaleY;
   while (i < this->scaleY)
   {
      float minY = i / this->scaleY;
      float maxY = (i + 1 > this->scaleY) ? 1.0 : (i + 1) / this->scaleY;

      // Back side.
      glNormal3f(-1.0, 0.0, 0.0);
      glBegin(GL_QUADS);
      glTexCoord2f(0.0, 0.0);
      glVertex3f(-1.0, maxY, -1.0);
      glTexCoord2f(1.0, 0.0);
      glVertex3f(-1.0, minY, -1.0);
      glTexCoord2f(0.0, 1.0);
      glVertex3f(-1.0, minY, -1.2);
      glTexCoord2f(1.0, 1.0);
      glVertex3f(-1.0, maxY, -1.2);
      glEnd();

      // Front side.
      glNormal3f(1.0, 0.0, 0.0);
      glBegin(GL_QUADS);
      glTexCoord2f(0.0, 0.0);
      glVertex3f(1.0, minY, -1.0);
      glTexCoord2f(1.0, 0.0);
      glVertex3f(1.0, maxY, -1.0);
      glTexCoord2f(0.0, 1.0);
      glVertex3f(1.0, maxY, -1.2);
      glTexCoord2f(1.0, 1.0);
      glVertex3f(1.0, minY, -1.2);
      glEnd();
      i += 1.0;
   }

   // Wall top caps.  (Tesselated to improve lighing effects on large polygons)
   // Idea borrowed from contents of https://www.glprogramming.com/red/chapter05.html. 
   // Using a while loop with a floating-point counter is intentional here, this allows me to still
   // tesselate the surface of the polygon even if the scaling is not a whole number.
   i = -this->scaleX;
   while (i < this->scaleX)
   {
      float minX = i / this->scaleX;
      float maxX = (i + 1 > this->scaleX) ? 1.0 : (i + 1) / this->scaleX;

      // Top side.
      glNormal3f(0.0, 1.0, 0.0);
      glBegin(GL_QUADS);
      glTexCoord2f(0.0, 0.0);
      glVertex3f(minX, 1.0, -1.0);
      glTexCoord2f(1.0, 0.0);
      glVertex3f(maxX, 1.0, -1.0);
      glTexCoord2f(0.0, 1.0);
      glVertex3f(maxX, 1.0, -1.2);
      glTexCoord2f(1.0, 1.0);
      glVertex3f(minX, 1.0, -1.2);
      glEnd();

      // Bottom side.
      glNormal3f(0.0, -1.0, 0.0);
      glBegin(GL_QUADS);
      glTexCoord2f(0.0, 0.0);
      glVertex3f(maxX, -1.0, -1.0);
      glTexCoord2f(1.0, 0.0);
      glVertex3f(minX, -1.0, -1.0);
      glTexCoord2f(0.0, 1.0);
      glVertex3f(minX, -1.0, -1.2);
      glTexCoord2f(1.0, 1.0);
      glVertex3f(maxX, -1.0, -1.2);
      glEnd();

      i += 1.0;
   }

   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}

// Function definition for CaveWall getSide helper function.
wall HedgeWall::getSide(Camera* camera)
{
   // Compute the relative x, z coodinates and convert to object coordinates.
   float cosine = Cos(this->rotY);
   float sine = Sin(this->rotY);
   float camX = camera->getEyeX() - this->posX;
   float camZ = camera->getEyeZ() - this->posZ;
   float objX = (camX * cosine) - (camZ * sine);
   float objZ = (camZ * cosine) + (camX * sine);

   float diffXMin = objX - (-this->scaleX - 0.6);
   float diffXMax = (this->scaleX + 0.6) - objX;
   float diffZMin = objZ - (-this->scaleZ - 0.8);
   float diffZMax = (-this->scaleZ + 0.6) - objZ;

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

// Function definition for CaveWall detectCollision function.
bool HedgeWall::detectCollision(Camera* camera)
{
   // Compute the relative x, z coordinates and convert to object coordinates.
   float cosine = Cos(this->rotY);
   float sine = Sin(this->rotY);
   float camX = camera->getEyeX() - this->posX;
   float camZ = camera->getEyeZ() - this->posZ;
   float objX = (camX * cosine) - (camZ * sine);
   float objZ = (camZ * cosine) + (camX * sine);

   // Compute x, z minimum and maximum values for object hitbox.
   float minX = -this->scaleX;
   float maxX = this->scaleX;
   float minZ = -this->scaleZ - 0.2;
   float maxZ = -this->scaleZ;

   // Determine if Camera is colliding with the object along the x, z axes.
   bool xCollide = objX > minX - 0.6 && objX < maxX + 0.6;
   bool zCollide = objZ > minZ - 0.6 && objZ < maxZ + 0.6;

   return xCollide && zCollide;
}

// Function definition for CaveWall resolveCollision function implementation.
void HedgeWall::resolveCollision(Camera* camera)
{
   // Compute the relative x, z coordinates and convert to object coordinates.
   float cosine = Cos(this->rotY);
   float sine = Sin(this->rotY);
   float camX = camera->getEyeX() - this->posX;
   float camZ = camera->getEyeZ() - this->posZ;
   float objX = (camX * cosine) - (camZ * sine);
   float objZ = (camZ * cosine) + (camX * sine);

   // Determine the wall to resolve collision with, and compute minimum and maximum x, z coordinates of the hitbox.
   wall collision = getSide(camera);
   float minX = -this->scaleX;
   float maxX = this->scaleX;
   float minZ = -this->scaleZ - 0.2;
   float maxZ = -this->scaleZ;

   if (collision == FRONT)
   {
      float newX, newZ;

      newX = objX;
      newZ = minZ - 0.6;

      // Undo transformation and convert back to world coordinates (transform matrix inverse courtesy of Symbolab.)
      newX = -(newX * cosine / (-sine * sine - cosine * cosine)) - (newZ * sine / (-sine * sine - cosine * cosine));
      newZ = (objX * sine / (-sine * sine - cosine * cosine)) - (newZ * cosine / (-sine * sine - cosine * cosine));
      newX += this->posX;
      newZ += this->posZ;

      // Update Camera position.
      camera->setEyePos(newX, camera->getEyeY(), newZ);
   }
   else if (collision == BACK)
   {
      float newX, newZ;

      newX = objX;
      newZ = maxZ + 0.6;

      // Undo transformation and convert back to world coordinates (transform matrix inverse courtesy of Symbolab).
      newX = -(newX * cosine / (-sine * sine - cosine * cosine)) - (newZ * sine / (-sine * sine - cosine * cosine));
      newZ = (objX * sine / (-sine * sine - cosine * cosine)) - (newZ * cosine /  (-sine * sine - cosine * cosine));
      newX += this->posX;
      newZ += this->posZ;

      // Update Camera position.
      camera->setEyePos(newX, camera->getEyeY(), newZ);
   }
   else if (collision == LEFT)
   {
      float newX, newZ;

      newX = minX - 0.6;
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

      newX = maxX + 0.6;
      newZ = objZ;

      // Undo transformation and convert back to world coordinates (transform matrix inverse courtesy of Symbolab).
      newZ = (newX * sine / (-sine * sine - cosine * cosine)) - (newZ * cosine / (-sine * sine - cosine * cosine));
      newX = -(newX * cosine / (-sine * sine - cosine * cosine)) - (objZ * sine / (-sine * sine - cosine * cosine));
      newX += this->posX;
      newZ += this->posZ;

      // Update Camera position.
      camera->setEyePos(newX, camera->getEyeY(), newZ);
   }
}

// Function definition for CaveWall setPosition function.
void HedgeWall::setPosition(float x, float y, float z)
{
   // Set translation coordinates.
   this->posX = x;
   this->posY = y;
   this->posZ = z;
}

// Function definition for CaveWall setScale function.
void HedgeWall::setScale(float x, float y, float z)
{
   // Set object scaling.
   this->scaleX = x;
   this->scaleY = y;
   this->scaleZ = z;
}

// Function definition for CaveWall setRotation function.
void HedgeWall::setRotation(float x, float y, float z)
{
   // Set object rotation about each axis.
   this->rotX = x;
   this->rotY = y;
   this->rotZ = z;
}

// Function definition for CaveWall getPosX function.
float HedgeWall::getPosX()
{
   return this->posX;
}

// Function definition for CaveWall getPosY function.
float HedgeWall::getPosY()
{
   return this->posY;
}

// Function definition for CaveWall getPosZ function.
float HedgeWall::getPosZ()
{
   return this->posZ;
}

// Function definition for CaveWall getScaleX function.
float HedgeWall::getScaleX()
{
   return this->scaleX;
}

// Function definition for CaveWall getScaleY function.
float HedgeWall::getScaleY()
{
   return this->scaleY;
}

// Function definition for CaveWall getScaleZ function.
float HedgeWall::getScaleZ()
{
   return this->scaleZ;
}

// Function definition for CaveWall getRotX function.
float HedgeWall::getRotX()
{
   return this->rotX;
}

// Function definition for CaveWall getRotY function.
float HedgeWall::getRotY()
{
   return this->rotY;
}

// Function definition for CaveWall getRotZ function.
float HedgeWall::getRotZ()
{
   return this->rotZ;
}