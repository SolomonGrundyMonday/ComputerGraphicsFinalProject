/*
 *   Lantern class definition.
 *
 *   Created by Jeff Colgan, November 5, 2021.
 *   Computer Graphics: Final Project. 
 */
#include "Lantern.h"

// Function definition for Lantern class default constructor.
Lantern::Lantern()
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

   this->lightDir[0] = 0.0;
   this->lightDir[1] = 1.1;
   this->lightDir[2] = 0.0;
}

// Function definition for Lantern class constructor.
Lantern::Lantern(float x, float y, float z, float dx, float dy, float dz, float rx, float ry, float rz)
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

   this->lightDir[0] = 0.0;
   this->lightDir[1] = 0.5;
   this->lightDir[2] = 0.0;
}

// Function definition for Lantern class Initialize function implementation.
int Lantern::Initialize(const char* filename)
{
   // Load textures from Assets subdirectory.
   this->texture = LoadTexBMP(filename);
   this->glass = LoadTexBMP("Assets/Metal.bmp");

   return 0;
}

// Function definition for Lantern class Render function implementation.
void Lantern::Render()
{
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

   // Optimization - this ratio is used in all texture coordinates for all cyllinders.  No need to repeat the floating-point
   // division dozens of times.
   float textureRatio = 1.0 / 12.0;

   // Draw lantern base cyllinder.
   glBegin(GL_QUAD_STRIP);
   for (int i = 0; i <= 12; i++)
   {
      // Optimization - reduce number of floating-point computations per loop iteration.
      int theta = i * 30;
      float cosine = Cos(theta);
      float sine = Sin(theta);

      glNormal3f(cosine, 0.0, sine);
      glTexCoord2f(0.0, i * textureRatio);
      glVertex3f(LANTERN_RAD * cosine, -1.0, LANTERN_RAD * sine);
      glTexCoord2f(12.0, i * textureRatio);
      glVertex3f(LANTERN_RAD * cosine, -0.6, LANTERN_RAD * sine);
   }
   glEnd();

   // Draw Lantern Base bottom disc.
   glNormal3f(0.0, -1.0, 0.0);
   glBegin(GL_TRIANGLE_FAN);
   glTexCoord2f(0.5, 0.5);
   glVertex3f(0.0, -1.0, 0.0);
   for (int i = 0; i <= 360; i += 30)
   {
      // Optimization - reduce number of floating-point computations per loop iteration.
      float cosine = Cos(i);
      float sine = Sin(i);

      glTexCoord2f(0.5 * cosine + 0.5, 0.5 * sine + 0.5);
      glVertex3f(LANTERN_RAD * cosine, -1.0, LANTERN_RAD * sine);
   }
   glEnd();

   // Draw Lanter base top disc.
   glNormal3f(0.0, 1.0, 0.0);
   glBegin(GL_TRIANGLE_FAN);
   glTexCoord2f(0.5, 0.5);
   glVertex3f(0.0, -0.6, 0.0);
   for (int i = 0; i <= 360; i += 30)
   {
      // Optimization - reduce number of floating-point computations per loop iteration.
      float cosine = Cos(i);
      float sine = Sin(i);

      glTexCoord2f(0.5 * cosine + 0.5, 0.5 * sine + 0.5);
      glVertex3f(LANTERN_RAD * cosine, -0.6, LANTERN_RAD * sine);
   }
   glEnd();

   // Draw lantern top cyllinder.
   glBegin(GL_QUAD_STRIP);
   for (int i = 0; i <= 12; i++)
   {
      // Optimization - reduce number of floating-point comuptations per loop iteration.
      int theta = i * 30;
      float cosine = Cos(theta);
      float sine = Sin(theta);

      glNormal3f(cosine, 0.6, sine);
      glTexCoord2f(0.0, i * textureRatio);
      glVertex3f(LANTERN_RAD * cosine, 0.6, LANTERN_RAD * sine);
      glTexCoord2f(12.0, i * textureRatio);
      glVertex3f(LANTERN_RAD * cosine, 1.0, LANTERN_RAD * sine);
   }
   glEnd();

   // Draw Lantern top upper disc.
   glNormal3f(0.0, 1.0, 0.0);
   glBegin(GL_TRIANGLE_FAN);
   glTexCoord2f(0.5, 0.5);
   glVertex3f(0.0, 1.0, 0.0);
   for (int i = 0; i <= 360; i += 30)
   {
      // Optimization - reduce number of floating-point computations per loop iteration.
      float cosine = Cos(i);
      float sine = Sin(i);

      glTexCoord2f(0.5 * cosine + 0.5, 0.5 * sine + 0.5);
      glVertex3f(LANTERN_RAD * cosine, 1.0, LANTERN_RAD * sine);
   }
   glEnd();

   // Draw Lantern top lower disc.
   glNormal3f(0.0, -1.0, 0.0);
   glBegin(GL_TRIANGLE_FAN);
   glTexCoord2f(0.5, 0.5);
   glVertex3f(0.0, 0.6, 0.0);
   for (int i = 0; i <= 360; i += 30)
   {
      // Optimization - reduce number of floating-point computations per loop iteration.
      float cosine = Cos(i);
      float sine = Sin(i);

      glTexCoord2f(0.5 * cosine + 0.5, 0.5 * sine + 0.5);
      glVertex3f(LANTERN_RAD * cosine, 0.6, LANTERN_RAD * sine);
   }
   glEnd();

   // Draw lantern handle cyllinder.
   glBegin(GL_QUAD_STRIP);
   for (int i = 0; i <= 12; i++)
   {
      // Optimization - reduce number of floating-point computations per loop iteration.
      int theta = i * 30;
      float cosine = Cos(theta);
      float sine = Sin(theta);

      glNormal3f(0.0, sine, cosine);
      glTexCoord2f(0.0, i * textureRatio);
      glVertex3f(-0.4, HANDLE_RAD * sine + 1.6, HANDLE_RAD * cosine);
      glTexCoord2f(12.0, i * textureRatio);
      glVertex3f(0.4, HANDLE_RAD * sine + 1.6, HANDLE_RAD * cosine);
   }
   glEnd();

   // Draw Lantern handle left disc.
   glNormal3f(-1.0, 0.0, 0.0);
   glBegin(GL_TRIANGLE_FAN);
   glTexCoord2f(0.5, 0.5);
   glVertex3f(-0.4, 1.6, 0.0);
   for (int i = 0; i <= 360; i += 30)
   {
      // Optimization - reduce number of floating-point computations per loop iteration.
     float cosine = Cos(i);
     float sine = Sin(i);

      glTexCoord2f(0.5 * cosine + 0.5, 0.5 * sine + 0.5);
      glVertex3f(-0.4, HANDLE_RAD * sine + 1.6, HANDLE_RAD * cosine);
   }
   glEnd();

   // Draw Lantern handle right disc.
   glNormal3f(1.0, 0.0, 0.0);
   glBegin(GL_TRIANGLE_FAN);
   glTexCoord2f(0.5, 0.5);
   glVertex3f(0.4, 1.6, 0.0);
   for (int i = 0; i <= 360; i += 30)
   {
      // Optimization - reduce number of floating-point computations per loop iteration.
      float cosine = Cos(i);
      float sine = Sin(i);

      glTexCoord2f(0.5 * cosine + 0.5, 0.5 * sine + 0.5);
      glVertex3f(0.4, HANDLE_RAD * sine + 1.6, HANDLE_RAD * cosine);
   }
   glEnd();

   // Draw Lantern handle right connecting cyllinder.
   glBegin(GL_QUAD_STRIP);
   for (int i = 0; i <= 12; i++)
   {
      // Optimization - reduce number of floating-point computations per loop iteration.
      int theta = i * 30;
      float cosine = Cos(theta);
      float sine = Sin(theta);

      glNormal3f(cosine, 0.0, sine);
      glTexCoord2f(0.0, i * textureRatio);
      glVertex3f(0.01 * cosine + 0.4, 1.6, 0.01 * sine);
      glTexCoord2f(12.0, i * textureRatio);
      glVertex3f(0.01 * cosine + 0.4, 1.0, 0.01 * sine);
   }
   glEnd();

   // Draw Lantern handle left connecting cyllinder.
   glBegin(GL_QUAD_STRIP);
   for (int i = 0; i <= 12; i++)
   {
      // Optimization - reduce number of floating-point computations per loop iteration.
      int theta = i * 30;
      float cosine = Cos(theta);
      float sine = Sin(theta);

      glNormal3f(-cosine, 0.0, sine);
      glTexCoord2f(0.0, i * textureRatio);
      glVertex3f(-0.01 * cosine - 0.4, 1.6, 0.01 * sine);
      glTexCoord2f(12.0, i * textureRatio);
      glVertex3f(-0.01 * cosine - 0.4, 1.0, 0.01 * sine);
   }
   glEnd();

   // Draw Lantern glass casing.
   // GL_BLEND info citation from this stack overflow thread:
   // https://stackoverflow.com/questions/24399431/opengl-texture-with-transparency-alpha
   glBindTexture(GL_TEXTURE_2D, glass);
   glColor4fv(white);
   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Specular);

   glBegin(GL_QUAD_STRIP);
   for (int i = 0; i <= 12; i++)
   {
      // Optimization - reduce number of floating-point computations per loop iteration.
      int theta = i * 30;
      float cosine = Cos(theta);
      float sine = Sin(theta);

      glNormal3f(cosine, 0.0, sine);
      glTexCoord2f(0.0, i * textureRatio);
      glVertex3f(LANTERN_RAD * cosine, -0.6, LANTERN_RAD * sine);
      glTexCoord2f(12.0, i * textureRatio);
      glVertex3f(LANTERN_RAD * cosine, 0.6, LANTERN_RAD * sine);
   }
   glEnd();

   glDisable(GL_CULL_FACE);

   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
   glDisable(GL_BLEND);
}

// Function definition for Lantern class detectCollision function.
bool Lantern::detectCollision(Camera* camera)
{
   // Compute relative Camera x, z coordinates and convert to object coordinates.
   float camX = camera->getEyeX() - this->posX;
   float camZ = camera->getEyeZ() - this->posZ;
   float objX = camX * Cos(this->rotY) - camZ * Sin(this->rotY);
   float objZ = camZ * Cos(this->rotY) + camX * Sin(this->rotY);

   // Compute x, z minimum and maximum values for object hitbox.
   float minX = -LANTERN_RAD * this->scaleX;
   float maxX = LANTERN_RAD * this->scaleX;
   float minZ = -LANTERN_RAD * this->scaleZ;
   float maxZ = LANTERN_RAD * this->scaleZ;

   // Determine if Camera is colliding with the object along both x and z axes, respectively.
   bool xCollide = objX > minX - 0.7 && objX < maxX + 0.7;
   bool zCollide = objZ > minZ - 0.7 && objZ < maxZ + 0.7;

   return xCollide && zCollide;
}

// Function definition for Lantern class resolveCollision function implementation.
void Lantern::resolveCollision(Camera* camera)
{
   // Compute relative Camera x, z coordinates and convert to object coordinates.
   float camX = camera->getEyeX() - this->posX;
   float camZ = camera->getEyeZ() - this->posZ;
   float objX = camX * Cos(this->rotY) - camZ * Sin(this->rotY);
   float objZ = camZ * Cos(this->rotY) + camX * Sin(this->rotY);

   // Compute x, z minimmum and maximum values for object hitbox.
   float minX = -LANTERN_RAD * this->scaleX;
   float maxX = LANTERN_RAD * this->scaleX;
   float minZ = -LANTERN_RAD * this->scaleZ;
   float maxZ = LANTERN_RAD * this->scaleZ;

   // Optimization - reduce number of function calls to sine/cosine.
   float sine = Sin(this->rotY);
   float cosine = Cos(this->rotY);

   wall collision = getSide(camera);

   // Update Camera position based on which wall of the hitbox is experiencing the collision.
   if (collision == FRONT)
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
   else if (collision == BACK)
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
   else if (collision == LEFT)
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
   else if (collision == RIGHT)
   {
      float newX, newZ;

      newZ = objZ;
      newX = maxX + 0.7;

      // Undo transformation and convert back to world coordinates (transformatino matrix inverse courtesy of Symbolab).
      newZ = (newX * sine / (-sine * sine - cosine * cosine)) - (newZ * cosine / (-sine * sine - cosine * cosine));
      newX = -(newX * cosine / (-sine * sine - cosine * cosine)) - (objZ * sine / (-sine * sine - cosine * cosine));
      newX += this->posX;
      newZ += this->posZ;

      // Update Camera position.
      camera->setEyePos(newX, camera->getEyeY(), newZ);
   }
}

// Funciton definition for Lantern class getSide helper function.
wall Lantern::getSide(Camera* camera)
{
   // Compute relative position and convert to object coordinates.
   float camX = camera->getEyeX() - this->posX;
   float camZ = camera->getEyeZ() - this->posZ;
   float objX = camX * Cos(this->rotY) - camZ * Sin(this->rotY);
   float objZ = camZ * Cos(this->rotY) + camX * Sin(this->rotY);

   // Compute x, z maximum and minimum values for object hitbox.
   float minX = (-LANTERN_RAD * this->scaleX) - 0.7;
   float maxX = (LANTERN_RAD * this->scaleX) + 0.7;
   float minZ = (-LANTERN_RAD * this->scaleZ) - 0.7;
   float maxZ = (LANTERN_RAD * this->scaleZ) + 0.7;
   float diffXMin = objX - minX;
   float diffXMax = maxX - objX;
   float diffZMin = objZ - minZ;
   float diffZMax = maxZ - objZ;

   // Determine which wall the Camera has collided with.
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

// Function definition for Lantern class lightSource function.
void Lantern::lightSource()
{
   // Declare parameters for Lantern light source.
   float spotE[] = { 0.0 };
   float spotC[] = { 180.0 };
   float spotPosition[] = { this->posX, this->posY, this->posZ, 1.0 };

   // Values for constant, linear and quadratic attenuation retrieved from chart found at: https://learnopengl.com/Lighting/Light-casters
   float cAttenuation[] = { 1.0 };
   float lAttenuation[] = { 0.09 };
   float qAttenuation[] = { 0.032 };

   // Enable light source.
   glEnable(GL_LIGHT0);
   glLightfv(GL_LIGHT0, GL_AMBIENT, Ambient);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, Diffuse);
   glLightfv(GL_LIGHT0, GL_SPECULAR, Specular);
   glLightfv(GL_LIGHT0, GL_POSITION, spotPosition);
   glLightfv(GL_LIGHT0, GL_SPOT_EXPONENT, spotE);
   glLightfv(GL_LIGHT0, GL_CONSTANT_ATTENUATION, cAttenuation);
   glLightfv(GL_LIGHT0, GL_LINEAR_ATTENUATION, lAttenuation);
   glLightfv(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, qAttenuation);
   glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF, spotC);
}

// Function definition for Lantern class setPosition function.
void Lantern::setPosition(float x, float y, float z)
{
   // Set object translation coordinates.
   this->posX = x;
   this->posY = y;
   this->posZ = z;
}

// Function definition for Lantern class setScale function.
void Lantern::setScale(float x, float y, float z)
{
   // Set object's scaling.
   this->scaleX = x;
   this->scaleY = y;
   this->scaleZ = z;
}

// Function definition for Lantern class setRotation function.
void Lantern::setRotation(float x, float y, float z)
{
   // Set object's rotation about each axis.
   this->rotX = x;
   this->rotY = y;
   this->rotZ = z;
}

// Function definition for Lantern class getPosX function.
float Lantern::getPosX()
{
   return this->posX;
}

// Function definition for Lantern class getPosY function.
float Lantern::getPosY()
{
   return this->posY;
}

// Function definition for Lantern class getPosZ function.
float Lantern::getPosZ()
{
   return this->posZ;
}

// Function definition for Lantern class getScaleX function.
float Lantern::getScaleX()
{
   return this->scaleX;
}

// Function definition for Lantern class getScaleY function.
float Lantern::getScaleY()
{
   return this->scaleY;
}

// Function definition for Lantern class getScaleZ function.
float Lantern::getScaleZ()
{
   return this->scaleZ;
}

// Function definition for Lantern class getRotX function.
float Lantern::getRotX()
{
   return this->rotX;
}

// Function definition for Lantern class getRotY function.
float Lantern::getRotY()
{
   return this->rotY;
}

// Function definition for Lantern class getRotZ function.
float Lantern::getRotZ()
{
   return this->rotZ;
}
