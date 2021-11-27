/*
 *   Class definition for TreeStump class.
 *   Created by Jeff Colgan, November 27, 2021.
 *   CSCI-4229 Computer Graphics : Final Project. 
 */

#include "TreeStump.h"

// Function definition for TreeStump default constructor.
TreeStump::TreeStump()
{
   // Specify the default translation at the origin.
   this->posX = 0.0;
   this->posY = 0.0;
   this->posZ = 0.0;

   // Specify the default scaling.
   this->scaleX = 1.0;
   this->scaleY = 1.0;
   this->scaleZ = 1.0;

   // Specify the default rotation.
   this->rotX = 0.0;
   this->rotY = 0.0;
   this->rotZ = 0.0;
}

// Function definition for TreeStump constructor.
TreeStump::TreeStump(float x, float y, float z, float dx, float dy, float dz, float rx, float ry, float rz)
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

// Function definition for TreeStump class Initialize function implementation.
int TreeStump::Initialize(const char* filename)
{
   texture = LoadTexBMP(filename);
   surface = LoadTexBMP("Assets/TreeRings.bmp");

   return 0;
}

// Function definition for TreeStump class Render function implementation.
void TreeStump::Render()
{
   // Enable textures.
   float brown[] = { 0.3, 0.165, 0.165, 0.2 };
   float white[] = { 1.0, 1.0, 1.0, 1.0 };
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D, texture);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glColor4fv(brown);
   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, brown);

   glPushMatrix();

   // Apply translation, rotation and scaling.
   glTranslatef(this->posX, this->posY, this->posZ);
   glRotatef(this->rotX, 1, 0, 0);
   glRotatef(this->rotY, 0, 1, 0);
   glRotatef(this->rotZ, 0, 0, 1);
   glScalef(this->scaleX, this->scaleY, this->scaleZ);

   // Draw the cyllinder.
   glBegin(GL_QUAD_STRIP);
   for(int i = 0; i <= 12; i += 2)
   {
      int theta = i * 30;
      int theta2 = (i + 1) * 30;
      float x1 = Cos(theta);
      float z1 = Sin(theta);
      float x2 = Cos(theta2);
      float z2 = Sin(theta2);
      float texRatio = i * 0.5;
      float texRatio2 = (i + 1) * 0.5; 

      glNormal3f(x1, 0.0, z1);
      glTexCoord2f(0.0, texRatio);
      glVertex3f(2.0 * x1, -1.0, 2.0 * z1);
      glTexCoord2f(2.0, texRatio);
      glVertex3f(2.0 * x1, 1.0, 2.0 * z1);

      glNormal3f(x2, 0.0, z2);
      glTexCoord2f(0.0, texRatio2);
      glVertex3f(2.0 * x2, -1.0, 2.0 * z2);
      glTexCoord2f(2.0, texRatio2);
      glVertex3f(2.0 * x2, 1.0, 2.0 * z2);
   }
   glEnd();

   // Draw the surfce (tree rings).
   glBindTexture(GL_TEXTURE_2D, surface);
   glBegin(GL_TRIANGLE_FAN);
   glNormal3f(0.0, 1.0, 0.0);
   glTexCoord2f(0.5, 0.5);
   glVertex3f(0.0, 1.0, 0.0);
   for (int i = 0; i <= 360; i += 60)
   {
      float x = Cos(i);
      float z = Sin(i);
      float x2 = Cos(i + 30);
      float z2 = Sin(i + 30);

      glNormal3f(x, 1.0, z);
      glTexCoord2f(0.5 * x + 0.5, 0.5 * z + 0.5);
      glVertex3f(2.0 * x, 1.0, 2.0 * z);

      glNormal3f(x2, 1.0, z2);
      glTexCoord2f(0.5 * x2 + 0.5, 0.5 * z2 + 0.5);
      glVertex3f(2.0 * x2, 1.0, 2.0 * z2);
   }
   glEnd();

   glColor4fv(white);
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}

// Function definition for TreeStump detectCollision function.
bool TreeStump::detectCollision(Camera* camera)
{
   // Compute relative Camera x, z coordinates and convert to object coordinate system.
   float camX = camera->getEyeX() - this->posX;
   float camZ = camera->getEyeZ() - this->posZ;
   camX = camX * Cos(this->rotY) - camZ * Sin(this->rotY);
   camZ = camZ * Cos(this->rotY) + camX * Sin(this->rotY);

   // Compute x, z minimum and maximum coordinates for object hitbox.
   float minX = -2.0 * this->scaleX;
   float maxX = 2.0 * this->scaleX;
   float minZ = -2.0 * this->scaleZ;
   float maxZ = 2.0 * this->scaleZ;

   // Determine if Camera is colliding with the object along the x and z axes, respectively.
   bool xCollide = camX > minX - 0.7 && camX < maxX + 0.7;
   bool zCollide = camZ > minZ - 0.7 && camZ < maxZ + 0.7;

   return xCollide && zCollide; 
}

// Function definition for TreeStump resolveCollision function implementation.
void TreeStump::resolveCollision(Camera* camera)
{
   // Compute relativve Camera x, z coordinates and convert to object coordinates.
   float camX = camera->getEyeX() - this->posX;
   float camZ = camera->getEyeZ() - this->posZ;
   camX = camX * Cos(this->rotY) - camZ * Sin(this->rotY);
   camZ = camZ * Cos(this->rotY) + camX * Sin(this->rotY);

   // Compute x, z minimum and maximum values for object hitbox.
   float minX = -2.0 * this->scaleX;
   float maxX = 2.0 * this->scaleX;
   float minZ = -2.0 * this->scaleZ;
   float maxZ = 2.0 * this->scaleZ;

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

      // Undo transformation and convert back to world coordinates (translation matrix invers courtesy of Symbolab).
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

      // Undo transformation and convert back to world coordinates (transformation matrix inverse courtesy to Symbolab).
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

      // Undo transformation and convert back to world coordinates (transformation matrix inverse courtesy of Symbolab).
      newX = -(newX * cosine / (-sine * sine - cosine * cosine)) - (newZ * sine / (-sine * sine - cosine * cosine));
      newZ = (newX * sine / (-sine * sine - cosine * cosine)) - (newZ * cosine / (-sine * sine - cosine * cosine));
      newX += this->posX;
      newZ += this->posZ;

      // Update Camera position.
      camera->setEyePos(newX, camera->getEyeY(), newZ);
   }

}

// Function definition for TreeStump getSide helper function.
wall TreeStump::getSide(Camera* camera)
{
   // Compute relative position and convert to object coordinates.
   float camX = camera->getEyeX() - this->posX;
   float camZ = camera->getEyeZ() - this->posZ;
   camX = camX * Cos(this->rotY) - camZ * Sin(this->rotY);
   camZ = camZ * Cos(this->rotY) + camX * Sin(this->rotY);

   // Compute x, z maximum and minimum values for object hitbox.
   float minX = -2.0 * this->scaleX - 0.7;
   float maxX = 2.0 * this->scaleX + 0.7;
   float minZ = -2.0 * this->scaleZ - 0.7;
   float maxZ = 2.0 * this->scaleZ + 0.7;
   float diffXMin = camX - minX;
   float diffXMax = maxX - camX;
   float diffZMin = camZ - minZ;
   float diffZMax = maxZ - camZ;

   // Determine which wall the Camera is colliding with.
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

// Function definition for TreeStump setPosition function.
void TreeStump::setPosition(float x, float y, float z)
{
   // Update translation coordinates.
   this->posX = x;
   this->posY = y;
   this->posZ = z;
}

// Function definition for TreeStump setScale function.
void TreeStump::setScale(float x, float y, float z)
{
   // Update object scaling.
   this->scaleX = x;
   this->scaleY = y;
   this->scaleZ = z;
}

// Function definition for TreeStump setRotation function.
void TreeStump::setRotation(float x, float y, float z)
{
   // Update object rotation.
   this->rotX = x;
   this->rotY = y;
   this->rotZ = z;
}

// Function definition for TreeStump getPosX function.
float TreeStump::getPosX()
{
   return this->posX;
}

// Function definition for TreeStump getPosY function.
float TreeStump::getPosY()
{
   return this->posY;
}

// Function definition for TreeStump getPosZ function.
float TreeStump::getPosZ()
{
   return this->posZ;
}

// Function definition for TreeStump getScaleX function.
float TreeStump::getScaleX()
{
   return this->scaleX;
}

// Function definition for TreeStump getScaleY function.
float TreeStump::getScaleY()
{
   return this->scaleY;
}

// Function definition for TreeStump getScaleZ function.
float TreeStump::getScaleZ()
{
   return this->scaleZ;
}

// Function definition for TreeStump getRotX function.
float TreeStump::getRotX()
{
   return this->rotX;
}

// Function definition for TreeStump getRotY function.
float TreeStump::getRotY()
{
   return this->rotY;
}

// Function definition for TreeStump getRotZ function
float TreeStump::getRotZ()
{
   return this->rotZ;
}