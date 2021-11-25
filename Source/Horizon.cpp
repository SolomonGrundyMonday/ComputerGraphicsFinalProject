#include "Horizon.h"

// Function definition for Horizon class default constructor.
Horizon::Horizon()
{
   // Specify default translation (at the origin).
   this->posX = 0.0;
   this->posY = 0.0;
   this->posZ = 0.0;

   // Specify default scaling (1.0 on all axes).
   this->scaleX = 1.0;
   this->scaleY = 1.0;
   this->scaleZ = 1.0;

   // Specify default rotation (0.0 about each axis).
   this->rotX = 0.0;
   this->rotY = 0.0;
   this->rotZ = 0.0;
}

// Function definition for Horizon class constructor.
Horizon::Horizon(float x, float y, float z, float dx, float dy, float dz, float rx, float ry, float rz)
{
   // Specify the desired translation.
   this->posX = x;
   this->posY = y;
   this->posZ = z;

   // Specify the desired scaling.
   this->scaleX = dx;
   this->scaleY = dy;
   this->scaleZ = dz;

   // Specify the desired rotation.
   this->rotX = rx;
   this->rotY = ry;
   this->rotZ = rz;
}

// Function definition for Horizon class Initialize function implementation.
int Horizon::Initialize(const char* filename)
{
   this->texture = LoadTexBMP(filename);

   return 0;
}

// Function definition for Horizon class Render function implementation.
void Horizon::Render()
{
   // Optimization - compute texture coordinates once per call to Render.
   float texX = this->scaleX / 10.0;
   float texZ = this->scaleZ / 10.0;

   // Enable textures.
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
   glBindTexture(GL_TEXTURE_2D, texture);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
   glPushMatrix();

   // Apply object's translation, rotation and scaling.
   glTranslatef(this->posX, this->posY, this->posZ);
   glRotatef(this->rotX, 1, 0, 0);
   glRotatef(this->rotY, 0, 1, 0);
   glRotatef(this->rotZ, 0, 0, 1);
   glScalef(this->scaleX, this->scaleY, this->scaleZ);

   // Set material properties.
   glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.0);
   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, black);

   // Draw left wall.
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(-1.0, -1.0, -1.0);
   glTexCoord2f(0.0, 1.0);
   glVertex3f(-1.0, 1.0, -1.0);
   glTexCoord2f(texZ, 1.0);
   glVertex3f(1.0, 1.0, -1.0);
   glTexCoord2f(texZ, 0.0);
   glVertex3f(1.0, -1.0, -1.0);
   glEnd();

   // Draw right wall.
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(-1.0, -1.0, 1.0);
   glTexCoord2f(0.0, 1.0);
   glVertex3f(-1.0, 1.0, 1.0); 
   glTexCoord2f(texZ, 1.0);
   glVertex3f(1.0, 1.0, 1.0);
   glTexCoord2f(texZ, 0.0);
   glVertex3f(1.0, -1.0, 1.0);
   glEnd();

   // Draw front wall.
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(-1.0, -1.0, 1.0);
   glTexCoord2f(0.0, 1.0);
   glVertex3f(-1.0, 1.0, 1.0);
   glTexCoord2f(texX, 1.0);
   glVertex3f(-1.0, 1.0, -1.0);
   glTexCoord2f(texX, 0.0);
   glVertex3f(-1.0, -1.0, -1.0);
   glEnd();

   // Draw back wall.
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(1.0, -1.0, -1.0);
   glTexCoord2f(0.0, 1.0);
   glVertex3f(1.0, 1.0, -1.0);
   glTexCoord2f(texX, 1.0);
   glVertex3f(1.0, 1.0, 1.0);
   glTexCoord2f(texX, 0.0);
   glVertex3f(1.0, -1.0, 1.0);
   glEnd();

   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}

// Function definition for Horizon class getSide helper function.
wall Horizon::getSide(Camera* camera)
{
   // Optimization - reduce function call overhead.
   float camX = camera->getEyeX();
   float camZ = camera->getEyeZ();

   // Determine if collision occured on the front, back, left or right wall.
   bool front = camZ > this->scaleZ - 0.5;
   bool back = camZ < -this->scaleZ + 0.5;
   bool left = camX < -this->scaleX + 0.5;
   bool right = camX > this->scaleX - 0.5;

   // Return the appropriate wall (if applicable).
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

// Function definition for Horizon class detectCollision function.
bool Horizon::detectCollision(Camera* camera)
{
   // Optimization - reduce function call overhead.
   float camX = camera->getEyeX();
   float camZ = camera->getEyeZ();

   // Determine if collision occured with the x or z axis (since the Camera should be "inside" the horizon line).
   bool xCollide = camX < -this->scaleX + 0.5 || camX > this->scaleX - 0.5;
   bool zCollide = camZ < -this->scaleZ + 0.5 || camZ > this->scaleZ - 0.5;

   // Return true if Camera collided with either axis.
   return xCollide || zCollide; 
}

// Function definition for Horizon class resolveCollision function.
void Horizon::resolveCollision(Camera* camera)
{
   // Optimization - reduce function call overhead.
   float camX = camera->getEyeX();
   float camZ = camera->getEyeZ();

   wall collision = getSide(camera);

   // If Camera collided with the front wall.
   if (collision == FRONT)
   {
      if (camX > this->scaleX - 0.5)
         camX = this->scaleX - 0.5;
      else if (camX < -this->scaleX + 0.5)
         camX = -this->scaleX + 0.5;

      camZ = this->scaleZ - 0.5;
   }
   // If Camera collided with the back wall.
   else if (collision == BACK)
   {
      if (camX > this->scaleX - 0.5)
         camX = this->scaleX - 0.5;
      else if (camX < -this->scaleX + 0.5)
         camX = -this->scaleX + 0.5;

      camZ = -this->scaleZ + 0.5;
   }
   // If Camera collided with the left wall.
   else if (collision == LEFT)
   {
      camX = -this->scaleX + 0.5;

      if (camZ > this->scaleZ - 0.5)
         camZ = this->scaleZ - 0.5;
      else if (camZ < -this->scaleZ + 0.5)
         camZ = -this->scaleZ + 0.5;
   }
   // If Camera collided with the right wall.
   else if (collision == RIGHT)
   {
      camX = this->scaleX - 0.5;

      if (camZ > this->scaleZ - 0.5)
         camZ = this->scaleZ - 0.5;
      else if (camZ < -this->scaleZ + 0.5)
         camZ = -this->scaleZ + 0.5;
   }

   // Update Camera position.
   camera->setEyePos(camX, camera->getEyeY(), camZ);
}

// Function definition for Horizon class setPosition function.
void Horizon::setPosition(float x, float y, float z)
{
   this->posX = x;
   this->posY = y;
   this->posZ = z;
}

// Function definition for Horizon class setScale function.
void Horizon::setScale(float x, float y, float z)
{
   this->scaleX = x;
   this->scaleY = y;
   this->scaleZ = z;
}

// Function definition for Horizon class setRotation function.
void Horizon::setRotation(float x, float y, float z)
{
   this->rotX = x;
   this->rotY = y;
   this->rotZ = z;
}

// Function definition for Horizon class getPosX function.
float Horizon::getPosX()
{
   return this->posX;
}

// Function definition for Horizon class getPosY function.
float Horizon::getPosY()
{
   return this->posY;
}

// Function definition for Horizon class getPosZ function.
float Horizon::getPosZ()
{
   return this->posZ;
}

// Function definition for Horizon class getScaleX function.
float Horizon::getScaleX()
{
   return this->scaleX;
}

// Function definition for Horizon class getScaleY function.
float Horizon::getScaleY()
{
   return this->scaleY;
}

// Function definition for Horizon class getScaleZ function.
float Horizon::getScaleZ()
{
   return this->scaleZ;
}

// Function definition for Horizon class getRotX function.
float Horizon::getRotX()
{
   return this->rotX;
}

// Function definition for Horizon class getRotY function.
float Horizon::getRotY()
{
   return this->rotY;
}

// Function definition for Horizon class getRotZ function.
float Horizon::getRotZ()
{
   return this->rotZ;
}