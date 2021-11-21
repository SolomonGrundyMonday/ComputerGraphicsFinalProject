/*
 *   Class definition for Axe class.
 *   Created by Jeff Colgan, October 27, 2021,
 *   CSCI-4229 Computer Graphics : Final Project. 
 */

#include "Axe.h"

// Function definition for Axe class default constructor.
Axe::Axe()
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

// Function definition for Axe class constructor.
Axe::Axe(float x, float y, float z, float dx, float dy, float dz, float rx, float ry, float rz)
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

// Function definition for Axe class Initialize function implementation.
int Axe::Initialize(const char* filename)
{
   this->texture = LoadTexBMP(filename);
   this->metal = LoadTexBMP("Assets/RustyMetal.bmp");

   return 0;
}

// Function definition for Axe class Render function implementation.
void Axe::Render()
{
   float headTop = LENGTH + 0.001;
   float headBottom = headTop - HEAD_HEIGHT;
   float axeBlade = -RAD - HEAD_LENGTH;
   float bladeNormY = headTop - (HEAD_HEIGHT/2.0);
   float bladeNormX = -RAD - (HEAD_LENGTH/2.0);
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
      int theta = i * 30;
      glNormal3f(RAD * Cos(theta), 0.0, RAD * Sin(theta));
      glTexCoord2f(0.0, i * textureRatio);
      glVertex3f(RAD * Cos(theta), 0.0, RAD * Sin(theta));
      glTexCoord2f(12.0, i * textureRatio);
      glVertex3f(RAD * Cos(theta), LENGTH, RAD * Sin(theta));
   }
   glEnd();

   glNormal3f(0.0, LENGTH, 0.0);
   glBegin(GL_TRIANGLE_FAN);
   glTexCoord2f(0.5, 0.5);
   glVertex3f(0.0, LENGTH, 0.0);

   for (int i = 0; i <= 360; i += 30)
   {
      float cosine = Cos(i);
      float sine = Sin(i);

      glNormal3f(cosine, LENGTH, sine);
      glTexCoord2f(0.5 * cosine + 0.5, 0.5 * sine + 0.5);
      glVertex3f(RAD * cosine, LENGTH, RAD * sine);
   }
   glEnd();

   glNormal3f(0.0, 0.0, 0.0);
   glBegin(GL_TRIANGLE_FAN);
   glTexCoord2f(0.5, 0.5);
   glVertex3f(0.0, 0.0, 0.0);

   for (int i = 0; i <= 360; i += 30)
   {
      float cosine = Cos(i);
      float sine = Sin(i);

      glNormal3f(cosine, 0.0, sine);
      glTexCoord2f(0.5 * cosine + 0.5, 0.5 * sine + 0.5);
      glVertex3f(RAD * cosine, 0.0, RAD * sine);
   }
   glEnd();

   // Draw the head.
   glBindTexture(GL_TEXTURE_2D, metal);

   // Top.
   glNormal3f(0.0, headTop, 0.0);
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

   // Bottom.
   glNormal3f(0.0, -headBottom, 0.0);
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

   // Front side.
   glNormal3f(0.0, headTop - (HEAD_HEIGHT/2), RAD);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(RAD, headBottom, RAD);
   glTexCoord2f(0.0, 1.0);
   glVertex3f(-RAD, headBottom, RAD);
   glTexCoord2f(1.0, 0.0);
   glVertex3f(-RAD, headTop, RAD);
   glTexCoord2f(1.0, 1.0);
   glVertex3f(RAD, headTop, RAD);
   glEnd();

   // Left side.
   glNormal3f(RAD, headTop - (HEAD_HEIGHT/2), 0.0);
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

   // Back side.
   glNormal3f(0.0, bladeNormY, -RAD);
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

   // Front axe flat side.
   glNormal3f(-bladeNormX, bladeNormY, -RAD/2);
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

   // Back axe flat side.
   glNormal3f(bladeNormX, bladeNormY, RAD/2);
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

   // Axe head top.
   glNormal3f(bladeNormX, headTop, 0.0);
   glBegin(GL_TRIANGLES);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(-RAD, headTop, RAD);
   glTexCoord2f(1.0, 0.0);
   glVertex3f(-RAD, headTop, -RAD);
   glTexCoord2f(1.0, 1.0);
   glVertex3f(axeBlade, headTop, 0.0);
   glEnd();

   // Axe head bottom.
   glNormal3f(bladeNormX, -headBottom, 0.0);
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
   float camX = camera->getEyeX() - this->posX;
   float camZ = camera->getEyeZ() - this->posZ;
   camX = camX * Cos(this->rotY) - camZ * Sin(this->rotY);
   camZ = camZ * Cos(this->rotY) + camX * Sin(this->rotY);

   float minX = -RAD * Cos(this->rotZ) * this->scaleX - (Cos(this->rotZ) * Cos(this->rotX) * this->scaleY);
   float maxX = RAD * Cos(this->rotZ) * this->scaleX + (LENGTH * Cos(this->rotZ) * Cos(this->rotX) * this->scaleY);
   float minZ = ((-RAD - HEAD_LENGTH) * Cos(this->rotX) * this->scaleZ) - (Cos(this->rotZ) * Cos(this->rotX) * this->scaleY);
   float maxZ = (RAD * Cos(this->rotX) * this->scaleZ) + (LENGTH * Cos(this->rotZ) * Cos(this->rotX) * this->scaleY);

   bool xCollide = camX > minX - 0.5 && camX < maxX + 0.5;
   bool zCollide = camZ > minZ - 0.5 && camZ < maxZ + 0.5;

   return xCollide && zCollide;
}

// Function definition for Axe class resolveCollision function implementation.
void Axe::resolveCollision(Camera* camera)
{
   // Compute Camera's relative position, then convert to object coordinates.
   float camX = camera->getEyeX() - this->posX;
   float camZ = camera->getEyeZ() - this->posZ;
   camX = camX * Cos(this->rotY) - camZ * Sin(this->rotY);
   camZ = camZ * Cos(this->rotY) + camX * Sin(this->rotY);

   // Compute the minimum and maximum x and z values for the hitbox based on the rotations about the x, y, z axes.
   float minX = -RAD * Cos(this->rotZ) * this->scaleX - (Cos(this->rotZ) * Cos(this->rotX) * this->scaleY);
   float maxX = RAD * Cos(this->rotZ) * this->scaleX + (LENGTH * Cos(this->rotZ) * Cos(this->rotX) * this->scaleY);
   float minZ = ((-RAD - HEAD_LENGTH) * Cos(this->rotX) * this->scaleZ) - (Cos(this->rotZ) * Cos(this->rotX) * this->scaleY);
   float maxZ = (RAD * Cos(this->rotX) * this->scaleZ) + (LENGTH * Cos(this->rotZ) * Cos(this->rotX) * this->scaleY);

   // Optimization - reduce function calls to sine, cosine function.
   float cosine = Cos(this->rotY);
   float sine = Sin(this->rotY);

   wall collision = getSide(camera);
   
   // If Camera collided with the front side.
   if (collision == FRONT)
   {
      float newX, newZ;

      newZ = minZ - 0.5;
      newX = camX;

      // Undo transformation and convert back to world coordinates (transformation matrix inverse courtesy of Symbolab).
      newX = -(newX * cosine / (-sine * sine - cosine * cosine)) - (newZ * sine / (-sine * sine - cosine * cosine));
      newZ = (newX * sine / (-sine * sine - cosine * cosine)) - (newZ * cosine / (-sine * sine - cosine * cosine));
      newX += this->posX;
      newZ += this->posZ;

      // Update Camera position.
      camera->setEyePos(newX, camera->getEyeY(), newZ);
   }
   // If Camera collided with the back side.
   else if  (collision == BACK)
   {
      float newX, newZ;

      newZ = maxZ + 0.5;
      newX = camX;

      // Undo transformation and convert back to world coordinates (transformation matrix inverse courtesy of Symbolab).
      newX = -(newX * cosine / (-sine * sine - cosine * cosine)) - (newZ * sine / (-sine * sine - cosine * cosine));
      newZ = (newX * sine / (-sine * sine - cosine * cosine)) - (newZ * cosine / (-sine * sine - cosine * cosine));
      newX += this->posX;
      newZ += this->posZ;

      // Update Camera position.
      camera->setEyePos(newX, camera->getEyeY(), newZ);
   }
   // If Camera collided with the left side.
   else if (collision == LEFT)
   {
      float newX, newZ;

      newZ = camZ;
      newX = minX - 0.5;

      // Undo transformation and convert back to world coordinates (transformation matrix inverse courtesy of Symbolab).
      newX = -(newX * cosine / (-sine * sine - cosine * cosine)) - (newZ * sine / (-sine * sine - cosine * cosine));
      newZ = (newX * sine / (-sine * sine - cosine * cosine)) - (newZ * cosine / (-sine * sine - cosine * cosine));
      newX += this->posX;
      newZ += this->posZ;

      // Update Camera position.
      camera->setEyePos(newX, camera->getEyeY(), newZ);
   }
   // If Camera collided with the right side.
   else if (collision == RIGHT)
   {
      float newX, newZ;

      newZ = camZ;
      newX = maxX + 0.5;

      // Undo transformation and convert back to world coordinates (transformation matrix inverse courtesy of Symbolab).
      newX = -(newX * cosine / (-sine * sine - cosine * cosine)) - (newZ * sine / (-sine * sine - cosine * cosine));
      newZ = (newX * sine / (-sine * sine - cosine * cosine)) - (newZ * cosine / (-sine * sine - cosine * cosine));
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
   float camX = camera->getEyeX() - this->posX;
   float camZ = camera->getEyeZ() - this->posZ;
   camX = camX * Cos(this->rotY) - camZ * Sin(this->rotY);
   camZ = camZ * Cos(this->rotY) + camX * Sin(this->rotY);

   // Compute minimum and maximum x, z values based on the rotations and scaling ont the x, y, z axes.
   float minX = -RAD * Cos(this->rotZ) * this->scaleX - (Cos(this->rotZ) * Cos(this->rotX) * this->scaleY);
   float maxX = RAD * Cos(this->rotZ) * this->scaleX + (LENGTH * Cos(this->rotZ) * Cos(this->rotX) * this->scaleY);
   float minZ = ((-RAD - HEAD_LENGTH) * Cos(this->rotX) * this->scaleZ) - (Cos(this->rotZ) * Cos(this->rotX) * this->scaleY);
   float maxZ = (RAD * Cos(this->rotX) * this->scaleZ) + (LENGTH * Cos(this->rotZ) * Cos(this->rotX) * this->scaleY);

   // Determine if the Camera has collided with the front, back, left, or right side of the Axe hitbox.
   bool front = camX > minX && camX < maxX && camZ < 0.0;
   bool back = camX > minX && camX < maxX && camZ > 0.0;
   bool left = camZ > minZ && camZ < maxZ && camX < 0.0;
   bool right = camZ > minZ && camZ < maxZ && camX > 0.0;

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
   this->posX = x;
   this->posY = y;
   this->posZ = z;
}

// Function definition for Axe class setScale function.
void Axe::setScale(float x, float y, float z)
{
   this->scaleX = x;
   this->scaleY = y;
   this->scaleZ = z;
}

// Function definition for Axe class setRotation function.
void Axe::setRotation(float x, float y, float z)
{
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