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
   this->posX = 0.0;
   this->posY = 0.0;
   this->posZ = 0.0;

   this->scaleX = 1.0;
   this->scaleY = 1.0;
   this->scaleZ = 1.0;

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
   this->posX = x;
   this->posY = y;
   this->posZ = z;

   this->scaleX = dx;
   this->scaleY = dy;
   this->scaleZ = dz;

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

   // Draw lantern base.
   glBegin(GL_QUAD_STRIP);
   for (int i = 0; i <= 12; i++)
   {
      int theta = i * 30;
      float x = Cos(theta);
      float z = Sin(theta);

      glNormal3f(x, 0.0, z);
      glTexCoord2f(0.0, i * 1.0/12.0);
      glVertex3f(LANTERN_RAD * x, -1.0, LANTERN_RAD * z);
      glTexCoord2f(12.0, i * 1.0/12.0);
      glVertex3f(LANTERN_RAD * x, -0.6, LANTERN_RAD * z);
   }
   glEnd();

   glNormal3f(0.0, -1.0, 0.0);
   glBegin(GL_TRIANGLE_FAN);
   glTexCoord2f(0.5, 0.5);
   glVertex3f(0.0, -1.0, 0.0);
   for (int i = 0; i <= 360; i += 30)
   {
      glNormal3f(Cos(i), -1.0, Sin(i));
      glTexCoord2f(0.5 * Cos(i) + 0.5, 0.5 * Sin(i) + 0.5);
      glVertex3f(LANTERN_RAD * Cos(i), -1.0, LANTERN_RAD * Sin(i));
   }
   glEnd();

   glNormal3f(0.0, -0.6, 0.0);
   glBegin(GL_TRIANGLE_FAN);
   glTexCoord2f(0.5, 0.5);
   glVertex3f(0.0, -0.6, 0.0);
   for (int i = 0; i <= 360; i += 30)
   {
      glNormal3f(Cos(i), -0.6, Sin(i));
      glTexCoord2f(0.5 * Cos(i) + 0.5, 0.5 * Sin(i) + 0.5);
      glVertex3f(LANTERN_RAD * Cos(i), -0.6, LANTERN_RAD * Sin(i));
   }
   glEnd();

   // Draw lantern top.
   glBegin(GL_QUAD_STRIP);
   for (int i = 0; i <= 12; i++)
   {
      int theta = i * 30;
      float x = Cos(theta);
      float z = Sin(theta);

      glNormal3f(x, 0.6, z);
      glTexCoord2f(0.0, i * 1.0/12.0);
      glVertex3f(LANTERN_RAD * x, 0.6, LANTERN_RAD * z);
      glTexCoord2f(12.0, i * 1.0/12.0);
      glVertex3f(LANTERN_RAD * x, 1.0, LANTERN_RAD * z);
   }
   glEnd();

   glNormal3f(0.0, 1.0, 0.0);
   glBegin(GL_TRIANGLE_FAN);
   glTexCoord2f(0.5, 0.5);
   glVertex3f(0.0, 1.0, 0.0);
   for (int i = 0; i <= 360; i += 30)
   {
      glNormal3f(Cos(i), 1.0, Sin(i));
      glTexCoord2f(0.5 * Cos(i) + 0.5, 0.5 * Sin(i) + 0.5);
      glVertex3f(LANTERN_RAD * Cos(i), 1.0, LANTERN_RAD * Sin(i));
   }
   glEnd();

   glNormal3f(0.0, 0.6, 0.0);
   glBegin(GL_TRIANGLE_FAN);
   glTexCoord2f(0.5, 0.5);
   glVertex3f(0.0, 0.6, 0.0);
   for (int i = 0; i <= 360; i += 30)
   {
      glNormal3f(Cos(i), 0.6, Sin(i));
      glTexCoord2f(0.5 * Cos(i) + 0.5, 0.5 * Sin(i) + 0.5);
      glVertex3f(LANTERN_RAD * Cos(i), 0.6, LANTERN_RAD * Sin(i));
   }
   glEnd();

   // Draw lantern handle.
   glBegin(GL_QUAD_STRIP);
   for (int i = 0; i <= 12; i++)
   {
      int theta = i * 30;
      float z = Cos(theta);
      float y = Sin(theta);

      glNormal3f(-0.4, HANDLE_RAD * y + 1.6, HANDLE_RAD * z);
      glTexCoord2f(0.0, i * 1.0/12.0);
      glVertex3f(-0.4, HANDLE_RAD * y + 1.6, HANDLE_RAD * z);
      glTexCoord2f(12.0, i * 1.0/12.0);
      glVertex3f(0.4, HANDLE_RAD * y + 1.6, HANDLE_RAD * z);
   }
   glEnd();

   glNormal3f(-0.4, 1.6, 0.0);
   glBegin(GL_TRIANGLE_FAN);
   glTexCoord2f(0.5, 0.5);
   glVertex3f(-0.4, 1.6, 0.0);
   for (int i = 0; i <= 360; i += 30)
   {
      glNormal3f(-0.4, Sin(i), Cos(i));
      glTexCoord2f(0.5 * Cos(i) + 0.5, 0.5 * Sin(i) + 0.5);
      glVertex3f(-0.4, HANDLE_RAD * Sin(i) + 1.6, HANDLE_RAD * Cos(i));
   }
   glEnd();

   glNormal3f(0.4, 1.6, 0.0);
   glBegin(GL_TRIANGLE_FAN);
   glTexCoord2f(0.5, 0.5);
   glVertex3f(0.4, 1.6, 0.0);
   for (int i = 0; i <= 360; i += 30)
   {
      glNormal3f(0.4, Sin(i), Cos(i));
      glTexCoord2f(0.5 * Cos(i) + 0.5, 0.5 * Sin(i) + 0.5);
      glVertex3f(0.4, HANDLE_RAD * Sin(i) + 1.6, HANDLE_RAD * Cos(i));
   }
   glEnd();

   // Draw lantern handle connectors.
   glBegin(GL_QUAD_STRIP);
   for (int i = 0; i <= 12; i++)
   {
      int theta = i * 30;
      float x = Cos(theta);
      float z = Sin(theta);

      glNormal3f(x, 1.3, z);
      glTexCoord2f(0.0, i * 1.0/12.0);
      glVertex3f(0.01 * x + 0.4, 1.6, 0.01 * z);
      glTexCoord2f(12.0, i * 1.0/12.0);
      glVertex3f(0.01 * x + 0.4, 1.0, 0.01 * z);
   }
   glEnd();

   glBegin(GL_QUAD_STRIP);
   for (int i = 0; i <= 12; i++)
   {
      int theta = i * 30;
      float x = Cos(theta);
      float z = Sin(theta);

      glNormal3f(-x, 1.3, z);
      glTexCoord2f(0.0, i * 1.0/12.0);
      glVertex3f(-0.01 * x - 0.4, 1.6, 0.01 * z);
      glTexCoord2f(12.0, i * 1.0/12.0);
      glVertex3f(-0.01 * x - 0.4, 1.0, 0.01 * z);
   }
   glEnd();

   // Draw lantern glass casing.
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
      int theta = i * 30;
      float x = Cos(theta);
      float z = Sin(theta);

      glNormal3f(x, 0.0, z);
      glTexCoord2f(0.0, i * 1.0/12.0);
      glVertex3f(LANTERN_RAD * x, -0.6, LANTERN_RAD * z);
      glTexCoord2f(12.0, i * 1.0/12.0);
      glVertex3f(LANTERN_RAD * x, 0.6, LANTERN_RAD * z);
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
   camX = camX * Cos(this->rotY) - camZ * Sin(this->rotY);
   camZ = camZ * Cos(this->rotY) + camX * Sin(this->rotY);

   // Compute x, z minimum and maximum values for object hitbox.
   float minX = -LANTERN_RAD * this->scaleX;
   float maxX = LANTERN_RAD * this->scaleX;
   float minZ = -LANTERN_RAD * this->scaleZ;
   float maxZ = LANTERN_RAD * this->scaleZ;

   // Determine if Camera is colliding with the object along both x and z axes, respectively.
   bool xCollide = camX > minX - 0.7 && camX < maxX + 0.7;
   bool zCollide = camZ > minZ - 0.7 && camZ < maxZ + 0.7;

   return xCollide && zCollide;
}

// Function definition for Lantern class resolveCollision function implementation.
void Lantern::resolveCollision(Camera* camera)
{
   // Compute relative Camera x, z coordinates and convert to object coordinates.
   float camX = camera->getEyeX() - this->posX;
   float camZ = camera->getEyeZ() - this->posZ;
   camX = camX * Cos(this->rotY) - camZ * Sin(this->rotY);
   camZ = camZ * Cos(this->rotY) + camX * Sin(this->rotY);

   // Compute x, z minimmum and maximum values for object hitbox.
   float minX = -LANTERN_RAD * this->scaleX;
   float maxX = LANTERN_RAD * this->scaleX;
   float minZ = -LANTERN_RAD * this->scaleZ;
   float maxZ = LANTERN_RAD * this->scaleZ;

   // Optimization - reduce number of function calls to sine/cosine.
   float sine = Sin(this->rotY);
   float cosine = Cos(this->rotY);

   wall collision = getSide(camera);
   glWindowPos2i(5, 25);

   if (collision == FRONT)
   {
      float newX, newZ;
      Print("Front");

      newZ = minZ - 0.7;
      newX = camX;

      // Undo transformation and convert back to world coordinates (transformation matrix inverse courtesy of Symbolab).
      newX = -(newX * cosine / (-sine * sine - cosine * cosine)) - (newZ * sine / (-sine * sine - cosine * cosine));
      newZ = (newX * sine / (-sine * sine - cosine * cosine)) - (newZ * cosine / (-sine * sine - cosine * cosine));
      newX += this->posX;
      newZ += this->posZ;

      // Update Camera position.
      camera->setEyePos(newX, camera->getEyeY(), newZ);
   }
   else if (collision == BACK)
   {
      float newX, newZ;
      Print("Back");

      newZ = maxZ + 0.7;
      newX = camX;

      // Undo transformation and convert back to world coordinates (transformation matrix inverse courtesy of Symbolab).
      newX = -(newX * cosine / (-sine * sine - cosine * cosine)) - (newZ * sine / (-sine * sine - cosine * cosine));
      newZ = (newX * sine / (-sine * sine - cosine * cosine)) - (newZ * cosine / (-sine * sine - cosine * cosine));
      newX += this->posX;
      newZ += this->posZ;

      // Update Camera position.
      camera->setEyePos(newX, camera->getEyeY(), newZ);
   }
   else if (collision == LEFT)
   {
      float newX, newZ;
      Print("Left");

      newZ = camZ;
      newX = minX - 0.7;

      // Undo transformation and convert back to world coordinates (transformation matrix inverse courtesy of Symbolab).
      newX = -(newX * cosine / (-sine * sine - cosine * cosine)) - (newZ * sine / (-sine * sine - cosine * cosine));
      newZ = (newX * sine / (-sine * sine - cosine * cosine)) - (newZ * cosine / (-sine * sine - cosine * cosine));
      newX += this->posX;
      newZ += this->posZ;

      // Update Camera position.
      camera->setEyePos(newX, camera->getEyeY(), newZ);
   }
   else if (collision == RIGHT)
   {
      float newX, newZ;
      Print("Right");

      newZ = camZ;
      newX = maxX + 0.7;

      // Undo transformation and convert back to world coordinates (transformatino matrix inverse courtesy of Symbolab).
      newX = -(newX * cosine / (-sine * sine - cosine * cosine)) - (newZ * sine / (-sine * sine - cosine * cosine));
      newZ = (newX * sine / (-sine * sine - cosine * cosine)) - (newZ * cosine / (-sine * sine - cosine * cosine));
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
   camX = camX * Cos(this->rotY) - camZ * Sin(this->rotY);
   camZ = camZ * Cos(this->rotY) + camX * Sin(this->rotY);

   // Compute x, z maximum and minimum values for object hitbox.
   float minX = (-LANTERN_RAD * this->scaleX) - 0.7;
   float maxX = (LANTERN_RAD * this->scaleX) + 0.7;
   float minZ = (-LANTERN_RAD * this->scaleZ) - 0.7;
   float maxZ = (LANTERN_RAD * this->scaleZ) + 0.7;
   float diffXMin = camX - minX;
   float diffXMax = maxX - camX;
   float diffZMin = camZ - minZ;
   float diffZMax = maxZ - camZ;

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
   float spotDirection[] = {0.0, 0.0, -1.0};
   float cAttenuation[] = { 1.0 };
   float lAttenuation[] = { 0.09 };
   float qAttenuation[] = { 0.032 };

   // Enable light source.
   glEnable(GL_LIGHT0);
   glLightfv(GL_LIGHT0, GL_AMBIENT, Ambient);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, Diffuse);
   glLightfv(GL_LIGHT0, GL_SPECULAR, Specular);
   glLightfv(GL_LIGHT0, GL_POSITION, spotPosition);
   glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDirection);
   glLightfv(GL_LIGHT0, GL_SPOT_EXPONENT, spotE);
   glLightfv(GL_LIGHT0, GL_CONSTANT_ATTENUATION, cAttenuation);
   glLightfv(GL_LIGHT0, GL_LINEAR_ATTENUATION, lAttenuation);
   glLightfv(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, qAttenuation);
   glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF, spotC);
}

// Function definition for Lantern class setPosition function.
void Lantern::setPosition(float x, float y, float z)
{
   this->posX = x;
   this->posY = y;
   this->posZ = z;
}

// Function definition for Lantern class setScale function.
void Lantern::setScale(float x, float y, float z)
{
   this->scaleX = x;
   this->scaleY = y;
   this->scaleZ = z;
}

// Function definition for Lantern class setRotation function.
void Lantern::setRotation(float x, float y, float z)
{
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
