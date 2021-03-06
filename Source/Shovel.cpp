/*
 *   Shovel class definition.
 *
 *   Created by Jeff Colgan, October 26, 2021,
 *   CSCI-4229 Computer Graphics: Final Project. 
 */
#include "Shovel.h"

// Definition of Shovel class default constructor.
Shovel::Shovel()
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

// Definition of Shovel class constructor.
Shovel::Shovel(float x, float y, float z, float dx, float dy, float dz, float rx, float ry, float rz)
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

// Definition of Shovel class Initialize function implementation.
int Shovel::Initialize(const char* filename)
{
   // Load textures from Assets subdirectory.
   texture = LoadTexBMP(filename);
   metal = LoadTexBMP("Assets/ToolHead.bmp");
   plastic = LoadTexBMP("Assets/Plastic.bmp");

   return 0;
}

// Definition of Shovel class Render function implementation.
void Shovel::Render()
{
   // Enable textures.
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D, plastic);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

   glPushMatrix();

   // Apply translation, rotation and scaling.
   glTranslated(this->posX, this->posY, this->posZ);
   glRotated(this->rotX, 1, 0, 0);
   glRotated(this->rotY, 0, 1, 0);
   glRotated(this->rotZ, 0, 0, 1);
   glScaled(this->scaleX, this->scaleY, this->scaleZ);

   glBegin(GL_QUAD_STRIP);

   // Draw the handle cyllinder.
   for (int i = 0; i <= 12; i++)
   {
      // Optimization - reduce the number of floating-point computations per iteration.
      int theta = i * 30;
      float sine = Sin(theta);
      float cosine = Cos(theta);

      glNormal3f(HANDLE_LEN, sine, cosine);
      glTexCoord2f(0, i * 0.25);
      glVertex3f(HANDLE_LEN, RADIUS * sine + HANDLE_HEIGHT, RADIUS * cosine);
      glTexCoord2f(1, i * 0.25);
      glVertex3f(-HANDLE_LEN, RADIUS * sine + HANDLE_HEIGHT, RADIUS * cosine);
   }
   glEnd();

   // Draw handle right disc.
   glNormal3f(HANDLE_LEN, 0.0, 0.0);
   glBegin(GL_TRIANGLE_FAN);
   glTexCoord2f(0.5, 0.5);
   glVertex3f(HANDLE_LEN, HANDLE_HEIGHT, 0.0);

   for (int i = 0; i <= 360; i += 30)
   {
      // Optimization - reduce the number of floating-point computations per iteration.
      float sine = Sin(i);
      float cosine = Cos(i);

      glTexCoord2f(0.5 * cosine + 0.5, 0.5 * sine + 0.5);
      glVertex3f(HANDLE_LEN, RADIUS * sine + HANDLE_HEIGHT, RADIUS * cosine);
   }
   glEnd();

   // Draw handle left disc.
   glNormal3f(-HANDLE_LEN, 0.0, 0.0);
   glBegin(GL_TRIANGLE_FAN);
   glTexCoord2f(0.5, 0.5);
   glVertex3f(-HANDLE_LEN, HANDLE_HEIGHT, 0.0);

   for (int i = 0; i <= 360; i += 30)
   {
      // Optimization - reduce the number of floating-point computations per iteration.
      float sine = Sin(i);
      float cosine = Cos(i);

      glTexCoord2f(0.5 * cosine + 0.5, 0.5 * sine + 0.5);
      glVertex3f(-HANDLE_LEN, RADIUS * sine + HANDLE_HEIGHT, RADIUS * cosine);
   }
   glEnd();

   // Draw handle right shaft connector.
   float handleBaseY = -HANDLE_HEIGHT / 2.0 + RADIUS;
   glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);
   glNormal3f(1.0, 0.0, 0.0);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(HANDLE_LEN, handleBaseY, RADIUS);
   glTexCoord2f(0.0, 1.0);
   glVertex3f(HANDLE_LEN, handleBaseY, -RADIUS);
   glTexCoord2f(1.0, 0.0);
   glVertex3f(HANDLE_LEN, HANDLE_HEIGHT, -RADIUS);
   glTexCoord2f(1.0, 1.0);
   glVertex3f(HANDLE_LEN, HANDLE_HEIGHT, RADIUS);
   glEnd();

   // Draw handle left shaft connector.
   glNormal3f(1.0, 0.0, 0.0);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(-HANDLE_LEN, handleBaseY, RADIUS);
   glTexCoord2f(0.0, 1.0);
   glVertex3f(-HANDLE_LEN, handleBaseY, -RADIUS);
   glTexCoord2f(1.0, 0.0);
   glVertex3f(-HANDLE_LEN, HANDLE_HEIGHT, -RADIUS);
   glTexCoord2f(1.0, 1.0);
   glVertex3f(-HANDLE_LEN, HANDLE_HEIGHT, RADIUS);
   glEnd();

   // Draw handle bottom shaft connector.
   glNormal3f(0.0, -1.0, 0.0);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(-HANDLE_LEN, handleBaseY, RADIUS);
   glTexCoord2f(0.0, 1.0);
   glVertex3f(-HANDLE_LEN, handleBaseY, -RADIUS);
   glTexCoord2f(1.0, 0.0);
   glVertex3f(HANDLE_LEN, handleBaseY, -RADIUS);
   glTexCoord2f(1.0, 1.0);
   glVertex3f(HANDLE_LEN, handleBaseY, RADIUS);
   glEnd();

   glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 0);

   // Draw the shaft.
   glBindTexture(GL_TEXTURE_2D, texture);
   glBegin(GL_QUAD_STRIP);
   
   for (int i = 0; i <= 12; i++)
   {
      // Optimization - reduce the number of floating-point computations per loop iteration.
      int theta = i * 30;
      float cosine = Cos(theta);
      float sine = Sin(theta);

      glNormal3f(cosine, 0.0, sine);
      glTexCoord2f(0.0, i * 1.0/12.0);
      glVertex3f(RADIUS * cosine, -RADIUS - SHAFT_LEN, RADIUS * sine);
      glTexCoord2f(12.0, i * 1.0/12.0);
      glVertex3f(RADIUS * cosine, -RADIUS, RADIUS * sine);
   }
   glEnd();

   // Draw the Shovel head.
   glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);
   glBindTexture(GL_TEXTURE_2D, metal);

   glNormal3f(0.0, -1.0, 0.0);
   glBegin(GL_TRIANGLE_FAN);
   glTexCoord2f(0.5, 0.5);
   glVertex3f(0.0, -SHAFT_LEN - HEAD_LEN - RADIUS, -RADIUS);

   for (int i = 0; i <= 180; i += 30)
   {
      // Optimization reduce the number of floating-point computations per iteration.
      float cosine = Cos(i);
      float sine = Sin(i);

      glNormal3f(cosine, 0.0, sine);
      glTexCoord2f(0.5 * cosine + 0.5, 0.5 * sine + 0.5);
      glVertex3f(RADIUS * cosine + HEAD_WIDTH * cosine, -SHAFT_LEN - RADIUS, RADIUS * sine);
   }
   glEnd();
   glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 0);

   // Draw shovel head connector cyllender.
   glBegin(GL_QUAD_STRIP);
   float newRadius = RADIUS + 0.01;

   for (int i = 0; i <= 12; i++)
   {
      // Optimization - reduce the number of floating-point computations per iteration.
      int theta = i * 30;
      float cosine = Cos(theta);
      float sine = Sin(theta);

      glNormal3f(cosine, 0.0, sine);
      glTexCoord2f(0.0, i % 2);
      glVertex3f(newRadius * cosine, -SHAFT_LEN, newRadius * sine);
      glTexCoord2f(1.0, i % 2);
      glVertex3f(newRadius * cosine, -SHAFT_LEN - RADIUS, newRadius * sine);
   }
   glEnd();

   // Draw shovel head connector cone.
   glNormal3f(0.0, 0.0, -1.0);
   glBegin(GL_TRIANGLE_FAN);
   glTexCoord2f(0.5, 0.5);
   glVertex3f(0.0, -RADIUS - SHAFT_LEN - 0.2, -RADIUS/2);

   for (int i = 0; i <= 360; i += 30)
   {
      // Optimization - reduce the number of floating-point computations per iteration.
      float cosine = Cos(i);
      float sine = Sin(i);

      glTexCoord2f(0.5 * cosine + 0.5, 0.5 * sine + 0.5);
      glVertex3f(newRadius * cosine, -RADIUS - SHAFT_LEN, newRadius * sine);
   }
   glEnd();

   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}

// Function definition for Shovel class detectCollision function.
bool Shovel::detectCollision(Camera* camera)
{
   // Compute relative position and convert to object coordinates.
   float cosine = Cos(this->rotY);
   float sine = Sin(this->rotY);
   float camX = camera->getEyeX() - this->posX;
   float camZ = camera->getEyeZ() - this->posZ;
   float objX = (camX * cosine) - (camZ * sine);
   float objZ = (camZ * cosine) + (camX * sine);

   // Compute minimum and maximum x, z  values based ont the rotations, scaling and dimensions of the object.
   float minX = (-HEAD_WIDTH / 2.0) * Cos(this->rotX) * this->scaleX - ((SHAFT_LEN + HEAD_LEN + RADIUS) * Sin(this->rotZ) * this->scaleY);
   float maxX = (HEAD_WIDTH / 2.0) * Cos(this->rotX) * this->scaleX + (HANDLE_HEIGHT * Sin(this->rotZ) * this->scaleY);
   float minZ = -RADIUS * Cos(this->rotX) * this->scaleZ - ((SHAFT_LEN + HEAD_LEN + RADIUS) * Sin(this->rotX) * this->scaleY);
   float maxZ = RADIUS * Cos(this->rotX) * this->scaleZ + (HANDLE_HEIGHT * Sin(this->rotX) * this->scaleY);

   // Determine if the Camera is colliding with the object's hitbox along the x and z axes, respectively.
   bool xCollide = objX >= minX - 0.7 && objX <= maxX + 0.7;
   bool zCollide = objZ >= minZ - 0.7 && objZ <= maxZ + 0.7;

   return xCollide && zCollide;
}

// Function definition for Shovel class getSide helper funciton.
wall Shovel::getSide(Camera* camera)
{
   // Compute relative position and convert to object coordinates.
   float camX = camera->getEyeX() - this->posX;
   float camZ = camera->getEyeZ() - this->posZ;
   float objX = camX * Cos(this->rotY) - camZ * Sin(this->rotY);
   float objZ = camZ * Cos(this->rotY) + camX * Sin(this->rotY);

   // Compute the minimum and maximum x, z values based on the rotation, scaling and dimensions of the object.
   float minX = (-HEAD_WIDTH / 2.0) * Cos(this->rotX) * this->scaleX - ((SHAFT_LEN + HEAD_LEN + RADIUS) * Sin(this->rotZ) * this->scaleY);
   float maxX = (HEAD_WIDTH / 2.0) * Cos(this->rotX) * this->scaleX + (HANDLE_HEIGHT * Sin(this->rotZ) * this->scaleY);
   float minZ = -RADIUS * Cos(this->rotX) * this->scaleZ - (SHAFT_LEN + HEAD_LEN + RADIUS) * Sin(this->rotX) * this->scaleY;
   float maxZ = RADIUS * Cos(this->rotX) * this->scaleZ + (HANDLE_HEIGHT * Sin(this->rotX) * this->scaleY);
   float diffXMin = objX - (minX - 0.7);
   float diffXMax = (maxX + 0.7) - objX;
   float diffZMin = objZ - (minZ - 0.7);
   float diffZMax = (maxZ + 0.7) - objZ; 

   // Determine if the camera has collided with the front, back, left or right side of the Shovel hitbox.
   bool front = diffZMin < diffZMax && diffZMin < diffXMin && diffZMin < diffXMax;
   bool back = diffZMax < diffZMin && diffZMax < diffXMin && diffZMax < diffXMax;
   bool left = diffXMin < diffXMax && diffXMin < diffZMin && diffXMin < diffZMax;
   bool right = diffXMax < diffXMin && diffXMax < diffZMin && diffXMax < diffZMax;

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

// Definition of Shovel class resolveCollision function implementaiton.
void Shovel::resolveCollision(Camera* camera)
{
   // Compute Camera's relative position then convert to object coordinates.
   float camX = camera->getEyeX() - this->posX;
   float camZ = camera->getEyeZ() - this->posZ;
   float objX = camX * Cos(this->rotY) - camZ * Sin(this->rotY);
   float objZ = camZ * Cos(this->rotY) + camX * Sin(this->rotY);

   // Compute the minimmum and maximum x and z values for the hitbox based on the rotations, scaling and dimensions of the object.
   float minX = (-HEAD_WIDTH / 2.0) * Cos(this->rotX) * this->scaleX - ((SHAFT_LEN + HEAD_LEN + RADIUS) * Sin(this->rotZ) * this->scaleY);
   float maxX = (HEAD_WIDTH / 2.0) * Cos(this->rotX) * this->scaleX + (HANDLE_HEIGHT * Sin(this->rotZ) * this->scaleY);
   float minZ = -RADIUS * Cos(this->rotX) * this->scaleZ - (SHAFT_LEN + HEAD_LEN + RADIUS) * Sin(this->rotX) * this->scaleY;
   float maxZ = RADIUS * Cos(this->rotX) * this->scaleZ + (HANDLE_HEIGHT * Sin(this->rotX) * this->scaleY);

   // Optimization - reduce function calls to sine, cosine functions.
   float cosine = Cos(this->rotY);
   float sine = Sin(this->rotY);

   wall collision = getSide(camera);

   // If Camera collided with the front side.
   if (collision == FRONT)
   {
      float newX, newZ;

      newZ = minZ - 0.7;
      newX = objX;

      // Undo transformatino and convert back to world coordinates (transform matrix inverse courtesy of Symbolab).
      newX = -(newX * cosine / (-sine * sine - cosine * cosine)) - (newZ * sine / (-sine * sine - cosine * cosine));
      newZ = (objX * sine / (-sine * sine - cosine * cosine)) - (newZ * cosine / (-sine * sine - cosine * cosine));
      newX += this->posX;
      newZ += this->posZ;

      // Update Camera position.
      camera->setEyePos(newX, camera->getEyeY(), newZ);
   }
   // If Camera collided with the back side.
   else if (collision == BACK)
   {
      float newX, newZ;

      newZ = maxZ + 0.7;
      newX = objX;

      // Undo transformation and convert back to world coordinates (transform matrix inverse courtesy of Symbolab).
      newX = -(newX * cosine / (-sine * sine - cosine * cosine)) - (newZ * sine / (-sine * sine - cosine * cosine));
      newZ = (objX * sine / (-sine * sine - cosine * cosine)) - (newZ * cosine / (-sine * sine - cosine * cosine));
      newX += this->posX;
      newZ += this->posZ;

      // Update Camera position.
      camera->setEyePos(newX, camera->getEyeY(), newZ);
   }
   // If Camera collided with the left side.
   else if (collision == LEFT)
   {
      float newX, newZ;
      glWindowPos2i(5, 45);
      Print("Here");

      newZ = objZ;
      newX = minX - 0.7;

      // Undo transformation and convert back to world coordinates (transform matrix inverse courtesy of Symbolab).
      newZ = (newX * sine / (-sine * sine - cosine * cosine)) - (newZ * cosine / (-sine * sine - cosine * cosine));
      newX = -(newX * cosine / (-sine * sine - cosine * cosine)) - (objZ * sine / (-sine * sine - cosine * cosine));
      newX += this->posX;
      newZ += this->posZ;

      // Update Camera position.
      camera->setEyePos(newX, camera->getEyeY(), newZ);
   }
   // If Camera collided with the right side.
   else if (collision == RIGHT)
   {
      float newX, newZ;
      glWindowPos2i(5, 45);
      Print("Here");

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

// Definition of Shovel class setPosition function.
void Shovel::setPosition(float x, float y, float z)
{
   // Set object translation coordinates.
   this->posX = x;
   this->posY = y;
   this->posZ = z;
}

// Definition of Shovel class setScale function.
void Shovel::setScale(float x, float y, float z)
{
   // Set object's scaling.
   this->scaleX = x;
   this->scaleY = y;
   this->scaleZ = z;
}

// Definition of Shovel class setRotation function.
void Shovel::setRotation(float x, float y, float z)
{
   // Set object's rotation about each axis.
   this->rotX = x;
   this->rotY = y;
   this->rotZ = z;
}

// Definition of Shovel class getPosX function.
float Shovel::getPosX()
{
   return this->posX;
}

// Definition of Shovel class getPosY function.
float Shovel::getPosY()
{
   return this->posY;
}

// Definition of Shovel class getPosZ function.
float Shovel::getPosZ()
{
   return this->posZ;
}

// Definition of Shovel class getScaleX function.
float Shovel::getScaleX()
{
   return this->scaleX;
}

// Definition of Shovel class getScaleY function.
float Shovel::getScaleY()
{
   return this->scaleY;
}

// Definition of Shovel class getScaleZ function.
float Shovel::getScaleZ()
{
   return this->scaleZ;
}

// Definition of Shovel class getRotX function.
float Shovel::getRotX()
{
   return this->rotX;
}

// Definition of Shovel class getRotY function.
float Shovel::getRotY()
{
   return this->rotY;
}

// Definition of Shovel class getRotZ function.
float Shovel::getRotZ()
{
   return this->rotZ;
}