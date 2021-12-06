/*
 *   Class definition for Axe class.
 *   Created by Jeff Colgan, October 27, 2021,
 *   CSCI-4229 Computer Graphics : Final Project. 
 */

#include "Axe.h"

// Function definition for Axe class default constructor.
Axe::Axe()
{
   // Set object translation coordinates.
   this->posX = 0.0;
   this->posY = 0.0;
   this->posZ = 0.0;

   // Set object's scaling.
   this->scaleX = 1.0;
   this->scaleY = 1.0;
   this->scaleZ = 1.0;

   // Set object's rotation about each axis.
   this->rotX = 0.0;
   this->rotY = 0.0;
   this->rotZ = 0.0;
}

// Function definition for Axe class constructor.
Axe::Axe(float x, float y, float z, float dx, float dy, float dz, float rx, float ry, float rz)
{
   // Set object translation coordinates.
   this->posX = x;
   this->posY = y;
   this->posZ = z;

   // Set object's scaling.
   this->scaleX = dx;
   this->scaleY = dy;
   this->scaleZ = dz;

   // Set object's rotation about each axis.
   this->rotX = rx;
   this->rotY = ry;
   this->rotZ = rz;
}

// Function definition for Axe class Initialize function implementation.
int Axe::Initialize(const char* filename)
{
   // Load textures from Assets subdirectory.
   this->texture = LoadTexBMP(filename);
   this->metal = LoadTexBMP("Assets/ToolHead.bmp");

   return 0;
}

// Function definition for Axe class Render function implementation.
void Axe::Render()
{
   // Optimization - reduce the number of floating-point computations per call to Render.
   float textureRatio = 1.0/12.0;

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

   // Draw the handle.
   glBegin(GL_QUAD_STRIP);
   for (int i = 0; i <= 12; i++)
   {
      // Optimization - reduce number of floating-point computations per loop iteration.
      int theta = i * 30;
      float cosine = Cos(theta);
      float sine = Sin(theta);

      glNormal3f(cosine, 0.0, sine);
      glTexCoord2f(0.0, i * textureRatio);
      glVertex3f(RAD * cosine, 0.0, RAD * sine);
      glTexCoord2f(12.0, i * textureRatio);
      glVertex3f(RAD * cosine, LENGTH, RAD * sine);
   }
   glEnd();

   // Draw the handle bottom disc.
   glNormal3f(0.0, -1.0, 0.0);
   glBegin(GL_TRIANGLE_FAN);
   glTexCoord2f(0.5, 0.5);
   glVertex3f(0.0, 0.0, 0.0);

   for (int i = 0; i <= 360; i += 30)
   {
      // Optimization - reduce number of floating-point computations per loop iteration.
      float cosine = Cos(i);
      float sine = Sin(i);

      glTexCoord2f(0.5 * cosine + 0.5, 0.5 * sine + 0.5);
      glVertex3f(RAD * cosine, 0.0, RAD * sine);
   }
   glEnd();

   // Draw the head.
   glBindTexture(GL_TEXTURE_2D, metal);
   glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 128.0);

   // Optimization - reduce number of floating-point computations per call to Render.
   float headTop = LENGTH + 0.001;
   float headBottom = headTop - HEAD_HEIGHT;
   float axeBlade = -RAD - HEAD_LENGTH;

   // Axe head connector Top.
   glNormal3f(0.0, 1.0, 0.0);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(-RAD, headTop, -RAD);
   glTexCoord2f(0.0, 1.0);
   glVertex3f(-RAD, headTop, RAD);
   glTexCoord2f(1.0, 0.0);
   glVertex3f(RAD, headTop, RAD);
   glTexCoord2f(1.0, 1.0);
   glVertex3f(RAD, headTop, -RAD);
   glEnd();

   // Axe head connector Bottom.
   glNormal3f(0.0, -1.0, 0.0);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(-RAD, headBottom, -RAD);
   glTexCoord2f(0.0, 1.0);
   glVertex3f(-RAD, headBottom, RAD);
   glTexCoord2f(1.0, 0.0);
   glVertex3f(RAD, headBottom, RAD);
   glTexCoord2f(1.0, 1.0);
   glVertex3f(RAD, headBottom, -RAD);
   glEnd();

   // Axe head connector Front side.
   glNormal3f(0.0, 0.0, 1.0);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(RAD, headBottom, RAD);
   glTexCoord2f(0.0, 1.0);
   glVertex3f(-RAD, headBottom, RAD);;
   glTexCoord2f(1.0, 0.0);
   glVertex3f(-RAD, headTop, RAD);
   glTexCoord2f(1.0, 1.0);
   glVertex3f(RAD, headTop, RAD);
   glEnd();

   // Axe head connector Left side.
   glNormal3f(1.0, 0.0, 0.0);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(RAD, headBottom, RAD);
   glTexCoord2f(0.0, 1.0);
   glVertex3f(RAD, headBottom, -RAD);
   glTexCoord2f(1.0, 0.0);
   glVertex3f(RAD, headTop, -RAD);
   glTexCoord2f(1.0, 1.0);
   glVertex3f(RAD, headTop, RAD);
   glEnd();

   // Axe head connector Back side.
   glNormal3f(0.0, 0.0, -1.0);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(-RAD, headTop, -RAD);
   glTexCoord2f(0.0, 1.0);
   glVertex3f(RAD, headTop, -RAD);
   glTexCoord2f(1.0, 0.0);
   glVertex3f(RAD, headBottom, -RAD);
   glTexCoord2f(1.0, 1.0);
   glVertex3f(-RAD, headBottom, -RAD);
   glEnd();

   // Back axe flat side.
   glNormal3f(0.0, 0.0, -1.0);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(-RAD, headTop, -RAD);
   glTexCoord2f(0.0, 1.0);
   glVertex3f(-RAD, headBottom, -RAD);   
   glTexCoord2f(1.0, 0.0);
   glVertex3f(axeBlade, headBottom, 0.0);
   glTexCoord2f(1.0, 1.0);
   glVertex3f(axeBlade, headTop, 0.0);
   glEnd();

   // Front axe flat side.
   glNormal3f(0.0, 0.0, 1.0);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(-RAD, headTop, RAD);
   glTexCoord2f(0.0, 1.0);
   glVertex3f(-RAD, headBottom, RAD);
   glTexCoord2f(1.0, 0.0);
   glVertex3f(axeBlade, headBottom, 0.0);
   glTexCoord2f(1.0, 1.0);
   glVertex3f(axeBlade, headTop, 0.0);
   glEnd();

   // Axe blade top.
   glNormal3f(0.0, 1.0, 0.0);
   glBegin(GL_TRIANGLES);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(-RAD, headTop, RAD);
   glTexCoord2f(1.0, 0.0);
   glVertex3f(-RAD, headTop, -RAD);
   glTexCoord2f(1.0, 1.0);
   glVertex3f(axeBlade, headTop, 0.0);
   glEnd();

   // Axe blade bottom.
   glNormal3f(0.0, -1.0, 0.0);
   glBegin(GL_TRIANGLES);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(-RAD, headBottom, RAD);
   glTexCoord2f(1.0, 0.0);
   glVertex3f(-RAD, headBottom, -RAD);
   glTexCoord2f(1.0, 1.0);
   glVertex3f(axeBlade, headBottom, 0.0);
   glEnd();

   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}

// Function definition for Axe class detectCollision function.
bool Axe::detectCollision(Camera* camera)
{
   // Convert Camera x, y coordinates to object coordinates.
   float cosine = Cos(this->rotY);
   float sine = Sin(this->rotY);
   float camX = camera->getEyeX() - this->posX;
   float camZ = camera->getEyeZ() - this->posZ;
   float objX = (camX * cosine) - (camZ * sine);
   float objZ = (camZ * cosine) + (camX * sine);

   float minX = (-RAD * Cos(this->rotX) * this->scaleX) + (Cos(this->rotZ) * LENGTH * this->scaleY);
   float maxX = (RAD * Cos(this->rotX) * this->scaleX) + (LENGTH * Cos(this->rotZ) * this->scaleY);
   float minZ = ((-RAD - HEAD_LENGTH) * Cos(this->rotX) * this->scaleZ) + (LENGTH * Sin(this->rotX) * this->scaleY);
   float maxZ = (RAD * Cos(this->rotX) * this->scaleZ) + (LENGTH * Sin(this->rotX) * this->scaleY);

   bool xCollide = objX >= minX - 0.7 && objX <= maxX + 0.7;
   bool zCollide = objZ >= minZ - 0.7 && objZ <= maxZ + 0.7;

   return xCollide && zCollide;
}

// Function definition for Axe class resolveCollision function implementation.
void Axe::resolveCollision(Camera* camera)
{
   // Compute Camera's relative position, then convert to object coordinates.
   float cosine = Cos(this->rotY);
   float sine = Sin(this->rotY);
   float camX = camera->getEyeX() - this->posX;
   float camZ = camera->getEyeZ() - this->posZ;
   float objX = (camX * cosine) - (camZ * sine);
   float objZ = (camZ * cosine) + (camX * sine);

   // Compute the minimum and maximum x and z values for the hitbox based on the rotations about the x, y, z axes.
   float minX = (-RAD * Cos(this->rotX) * this->scaleX) + (Cos(this->rotZ) * LENGTH * this->scaleY);
   float maxX = (RAD * Cos(this->rotX) * this->scaleX) + (LENGTH * Cos(this->rotZ) * this->scaleY);
   float minZ = ((-RAD - HEAD_LENGTH) * Cos(this->rotX) * this->scaleZ) + (LENGTH * Sin(this->rotX) * this->scaleY);
   float maxZ = (RAD * Cos(this->rotX) * this->scaleZ) + (LENGTH * Sin(this->rotX) * this->scaleY);

   wall collision = getSide(camera);
   
   // If Camera collided with the front side.
   if (collision == RIGHT)
   {
      float newX, newZ;

      newZ = maxZ + 0.7;
      newX = objX;

      // Undo transformation and convert back to world coordinates (transformation matrix inverse courtesy of Symbolab).
      newX = -(newX * cosine / (-sine * sine - cosine * cosine)) - (newZ * sine / (-sine * sine - cosine * cosine));
      newZ = (objX * sine / (-sine * sine - cosine * cosine)) - (newZ * cosine / (-sine * sine - cosine * cosine));
      newX += this->posX;
      newZ += this->posZ;

      // Update Camera position.
      camera->setEyePos(newX, camera->getEyeY(), newZ);
   }
   // If Camera collided with the back side.
   else if  (collision == LEFT)
   {
      float newX, newZ;

      newZ = minZ - 0.7;
      newX = objX;

      // Undo transformation and convert back to world coordinates (transformation matrix inverse courtesy of Symbolab).
      newX = -(newX * cosine / (-sine * sine - cosine * cosine)) - (newZ * sine / (-sine * sine - cosine * cosine));
      newZ = (objX * sine / (-sine * sine - cosine * cosine)) - (newZ * cosine / (-sine * sine - cosine * cosine));
      newX += this->posX;
      newZ += this->posZ;

      // Update Camera position.
      camera->setEyePos(newX, camera->getEyeY(), newZ);
   }
   // If Camera collided with the left side.
   else if (collision == FRONT)
   {
      float newX, newZ;

      newZ = objZ;
      newX = minX - 0.7;

      // Undo transformation and convert back to world coordinates (transformation matrix inverse courtesy of Symbolab).
      newZ = (newX * sine / (-sine * sine - cosine * cosine)) - (newZ * cosine / (-sine * sine - cosine * cosine));
      newX = -(newX * cosine / (-sine * sine - cosine * cosine)) - (objZ * sine / (-sine * sine - cosine * cosine));
      newX += this->posX;
      newZ += this->posZ;

      // Update Camera position.
      camera->setEyePos(newX, camera->getEyeY(), newZ);
   }
   // If Camera collided with the right side.
   else if (collision == BACK)
   {
      float newX, newZ;

      newZ = objZ;
      newX = maxX + 0.7;

      // Undo transformation and convert back to world coordinates (transformation matrix inverse courtesy of Symbolab).
      newZ = (newX * sine / (-sine * sine - cosine * cosine)) - (newZ * cosine / (-sine * sine - cosine * cosine));
      newX = -(newX * cosine / (-sine * sine - cosine * cosine)) - (objZ * sine / (-sine * sine - cosine * cosine));
      newX += this->posX;
      newZ += this->posZ;

      // Update Camera position.
      camera->setEyePos(newX, camera->getEyeY(), newZ);
   }
}

// Function definition for Axe class getSide helper function.
wall Axe::getSide(Camera* camera)
{
   // Compute relative position and convert to object coordinates.
   float cosine = Cos(this->rotY);
   float sine = Sin(this->rotY);
   float camX = camera->getEyeX() - this->posX;
   float camZ = camera->getEyeZ() - this->posZ;
   float objX = (camX * cosine) - (camZ * sine);
   float objZ = (camZ * cosine) + (camX * sine);

   // Compute minimum and maximum x, z values based on the rotations and scaling ont the x, y, z axes.
   float minX = (-RAD * Cos(this->rotX) * this->scaleX) + (Cos(this->rotZ) * LENGTH * this->scaleY);
   float maxX = (RAD * Cos(this->rotX) * this->scaleX) + (LENGTH * Cos(this->rotZ) * this->scaleY);
   float minZ = ((-RAD - HEAD_LENGTH) * Cos(this->rotX) * this->scaleZ) + (LENGTH * Sin(this->rotX) * this->scaleY);
   float maxZ = (RAD * Cos(this->rotX) * this->scaleZ) + (LENGTH * Sin(this->rotX) * this->scaleY);
   float diffXMin = objX - (minX - 0.7);
   float diffXMax = (maxX + 0.7) - objX;
   float diffZMin = objZ - (minZ - 0.7);
   float diffZMax = (maxZ + 0.7) - objZ;

   // Determine if the Camera has collided with the front, back, left, or right side of the Axe hitbox.
   bool front = diffXMin < diffXMax && diffXMin < diffZMin && diffXMin < diffZMax;
   bool back = diffXMax < diffXMin && diffXMax < diffZMin && diffXMax < diffZMax;
   bool left = diffZMin < diffZMax && diffZMin < diffXMin && diffZMin < diffXMax;
   bool right = diffZMax < diffZMin && diffZMax < diffXMin && diffZMax < diffXMax;

   // Return the appropriate side.
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

// Function definition for Axe class setPosition function.
void Axe::setPosition(float x, float y, float z)
{
   // Set object translation coordinates.
   this->posX = x;
   this->posY = y;
   this->posZ = z;
}

// Function definition for Axe class setScale function.
void Axe::setScale(float x, float y, float z)
{
   // Set object's scaling.
   this->scaleX = x;
   this->scaleY = y;
   this->scaleZ = z;
}

// Function definition for Axe class setRotation function.
void Axe::setRotation(float x, float y, float z)
{
   // Set object's rotation about each axis.
   this->rotX = x;
   this->rotY = y;
   this->rotZ = z;
}

// Function definition for Axe class getPosX function.
float Axe::getPosX()
{
   return this->posX;
}

// Function definition for Axe class getPosY function.
float Axe::getPosY()
{
   return this->posY;
}

// Function definition for Axe class getPosZ function.
float Axe::getPosZ()
{
   return this->posZ;
}

// Function definition for Axe class getScaleX function.
float Axe::getScaleX()
{
   return this->scaleX;
}

// Function definition for Axe class getScaleY function.
float Axe::getScaleY()
{
   return this->scaleY;
}

// Function definition for Axe class getScaleZ function.
float Axe::getScaleZ()
{
   return this->scaleZ;
}

// Function definition for Axe class getRotX function.
float Axe::getRotX()
{
   return this->rotX;
}

// Function definition for Axe class getRotY function.
float Axe::getRotY()
{
   return this->rotY;
}

// Function definition for Axe class getRotZ function.
float Axe::getRotZ()
{
   return this->rotZ;
}