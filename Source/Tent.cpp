#include "Tent.h"

// Function definition for Tent object default constructor.
Tent::Tent()
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

// Function definition for Tent object constructor.
Tent::Tent(float x, float y, float z, float dx, float dy, float dz, float rx, float ry, float rz)
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

// Function definition for Tent object Initialize function implementation.
int Tent::Initialize(const char* filename)
{
   this->texture = LoadTexBMP(filename);
   this->spike = LoadTexBMP("Assets/RustyMetal.bmp");
   this->canvasWrap = LoadTexBMP("Assets/CanvasRoll.bmp");
   return 0;
}

// Function definition for Tent object Render function implementation.
void Tent::Render()
{
   float textureRatio = 1.0/12.0;

   // Enable textures.
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
   glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);
   glBindTexture(GL_TEXTURE_2D, texture);

   glPushMatrix();

   // Apply translation, rotation and scaling.
   glTranslatef(this->posX, this->posY, this->posZ);
   glRotatef(this->rotX, 1, 0, 0);
   glRotatef(this->rotY, 0, 1, 0);
   glRotatef(this->rotZ, 0, 0, 1);
   glScalef(this->scaleX, this->scaleY, this->scaleZ);

   // Draw Tent front wall.
   glNormal3f(-0.8, 0.0, 1.0);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(-1.0, -1.0, 1.0);
   glTexCoord2f(this->scaleX, 0.0);
   glVertex3f(-0.6, -1.0, 1.0);
   glTexCoord2f(this->scaleX, this->scaleY);
   glVertex3f(-0.6, 1.0, 1.0);
   glTexCoord2f(0.0, this->scaleY);
   glVertex3f(-1.0, 1.0, 1.0);
   glEnd();

   glNormal3f(0.8, 0.0, 1.0);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(0.6, -1.0, 1.0);
   glTexCoord2f(this->scaleX, 0.0);
   glVertex3f(1.0, -1.0, 1.0);
   glTexCoord2f(this->scaleX, this->scaleY);
   glVertex3f(1.0, 1.0, 1.0);
   glTexCoord2f(0.0, this->scaleY);
   glVertex3f(0.6, 1.0, 1.0);
   glEnd();

   glNormal3f(0.0, 0.6, 1.0);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(-0.6, 0.2, 1.0);
   glTexCoord2f(this->scaleX, 0.0);
   glVertex3f(0.6, 0.2, 1.0);
   glTexCoord2f(this->scaleX, this->scaleY);
   glVertex3f(0.6, 1.0, 1.0);
   glTexCoord2f(0.0, this->scaleY);
   glVertex3f(-0.6, 1.0, 1.0);
   glEnd();

   // Draw Tent back wall.
   glNormal3f(0.0, 0.0, -1.0);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(1.0, -1.0, -1.0);
   glTexCoord2f(this->scaleX, 0.0);
   glVertex3f(-1.0, -1.0, -1.0);
   glTexCoord2f(this->scaleX, this->scaleY);
   glVertex3f(-1.0, 1.0, -1.0);
   glTexCoord2f(0.0, this->scaleY);
   glVertex3f(1.0, 1.0, -1.0);
   glEnd();

   // Draw Tent left wall.
   glNormal3f(-0.5, 0.0, 0.0);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(-1.0, -1.0, -1.0);
   glTexCoord2f(this->scaleZ, 0.0);
   glVertex3f(-1.0, -1.0, 1.0);
   glTexCoord2f(this->scaleZ, this->scaleY);
   glVertex3f(-1.0, 1.0, 1.0);
   glTexCoord2f(0.0, this->scaleY);
   glVertex3f(-1.0, 1.0, -1.0);
   glEnd();

   // Draw Tent Right wall.
   glNormal3f(0.5, 0.0, 0.0);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(1.0, -1.0, 1.0);
   glTexCoord2f(this->scaleZ, 0.0);
   glVertex3f(1.0, -1.0, -1.0);
   glTexCoord2f(this->scaleZ, this->scaleY);
   glVertex3f(1.0, 1.0, -1.0);
   glTexCoord2f(0.0, this->scaleY);
   glVertex3f(1.0, 1.0, 1.0);
   glEnd();

   // Draw Tent floor.
   glNormal3f(0.0, -1.0, 0.0);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(1.0, -0.999, 1.0);
   glTexCoord2f(this->scaleZ, 0.0);
   glVertex3f(-1.0, -0.999, 1.0);
   glTexCoord2f(this->scaleZ, this->scaleX);
   glVertex3f(-1.0, -0.999, -1.0);
   glTexCoord2f(0.0, this->scaleX);
   glVertex3f(1.0, -0.999, -1.0);
   glEnd();

   // Draw Tent roof.
   glNormal3f(0.0, (1.5/2.0), 1.0);
   glBegin(GL_TRIANGLES);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(-1.0, 1.0, 1.0);
   glTexCoord2f(this->scaleX, 0.0);
   glVertex3f(1.0, 1.0, 1.0);
   glTexCoord2f(this->scaleX/2.0, (0.5 * this->scaleY)/2.0);
   glVertex3f(0.0, 1.5, 1.0);
   glEnd();

   glNormal3f(0.0, 1.5/2.0, -1.0);
   glBegin(GL_TRIANGLES);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(1.0, 1.0, -1.0);
   glTexCoord2f(this->scaleX, 0.0);
   glVertex3f(-1.0, 1.0, -1.0);
   glTexCoord2f(this->scaleX/2.0, (0.5 * this->scaleY)/2.0);
   glVertex3f(0.0, 1.5, -1.0);
   glEnd();

   glNormal3f(-0.5, 1.25, 0.0);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(-1.0, 1.0, -1.0);
   glTexCoord2f(this->scaleZ, 0.0);
   glVertex3f(-1.0, 1.0, 1.0);
   glTexCoord2f(this->scaleZ, this->scaleY);
   glVertex3f(0.0, 1.5, 1.0);
   glTexCoord2f(0.0, this->scaleY);
   glVertex3f(0.0, 1.5, -1.0);
   glEnd();

   glNormal3f(0.5, 1.25, 0.0);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(1.0, 1.0, 1.0);
   glTexCoord2f(this->scaleZ, 0.0);
   glVertex3f(1.0, 1.0, -1.0);
   glTexCoord2f(this->scaleZ, this->scaleY);
   glVertex3f(0.0, 1.5, -1.0);
   glTexCoord2f(0.0, this->scaleY);
   glVertex3f(0.0, 1.5, 1.0);
   glEnd();

   glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 0);

   // Draw Tent flaps.
   glBegin(GL_QUAD_STRIP);
   for (int i = 0; i <= 12; i++)
   {
      int theta = i * 30;
      float x = Cos(theta);
      float z = Sin(theta);

      glNormal3f(x, -1.0, z);
      glTexCoord2f(0.0, i * textureRatio);
      glVertex3f(x * 0.1 + 0.6, -1.0, z * 0.1 + 1.0);
      glTexCoord2f(12.0, i * textureRatio);
      glVertex3f(x * 0.1 + 0.6, 0.2, z * 0.1 + 1.0);
   }
   glEnd();

   glBegin(GL_QUAD_STRIP);
   for (int i = 0; i <= 12; i++)
   {
      int theta = i * 30;
      float x = Cos(theta);
      float z = Sin(theta);

      glNormal3f(x, -1.0, z);
      glTexCoord2f(0.0, i * textureRatio);
      glVertex3f(x * 0.1 - 0.6, -1.0, z * 0.1 + 1.0);
      glTexCoord2f(12.0, i * textureRatio);
      glVertex3f(x * 0.1 - 0.6, 0.2, z * 0.1 + 1.0);
   }
   glEnd();

   // Draw Tent ties.
   glNormal3f(1.1, 0.055, 1.1);
   glBegin(GL_LINES);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(1.2, -0.89, 1.2);
   glTexCoord2f(1.0, 1.0);
   glVertex3f(1.0, 1.0, 1.0);
   glEnd();

   glNormal3f(-1.1, 0.055, 1.1);
   glBegin(GL_LINES);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(-1.2, -0.89, 1.2);
   glTexCoord2f(1.0, 1.0);
   glVertex3f(-1.0, 1.0, 1.0);
   glEnd();

   glNormal3f(-1.1, -0.89, -1.1);
   glBegin(GL_LINES);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(-1.2, -0.89, -1.2);
   glTexCoord2f(1.0, 1.0);
   glVertex3f(-1.0, 1.0, -1.0);
   glEnd();

   glNormal3f(1.1, -0.89, -1.1);
   glBegin(GL_LINES);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(1.2, -0.89, -1.2);
   glTexCoord2f(1.0, 1.0);
   glVertex3f(1.0, 1.0, -1.0);
   glEnd();

   // Draw rolled tent flap tops and bottoms.
   glBindTexture(GL_TEXTURE_2D, canvasWrap);
   glNormal3f(0.6, 0.2, 1.0);
   glBegin(GL_TRIANGLE_FAN);
   glTexCoord2f(0.5, 0.5);
   glVertex3f(0.6, 0.2, 1.0);
   for (int i = 0; i <= 360; i += 30)
   {
      float cosine = Cos(i);
      float sine = Sin(i);

      glNormal3f(cosine + 0.6, 0.2, sine + 1.0);
      glTexCoord2f(0.5 * cosine + 0.5, 0.5 * sine + 0.5);
      glVertex3f(0.1 * cosine + 0.6, 0.2, 0.1 * sine + 1.0);
   }
   glEnd();

   glNormal3f(0.6, -1.0, 1.0);
   glBegin(GL_TRIANGLE_FAN);
   glTexCoord2f(0.5, 0.5);
   glVertex3f(0.6, -1.0, 1.0);
   for (int i = 0; i <= 360; i += 30)
   {
      float cosine = Cos(i);
      float sine = Sin(i);

      glNormal3f(cosine + 0.6, -1.0, sine + 1.0);
      glTexCoord2f(0.5 * cosine + 0.5, 0.5 * sine + 0.5);
      glVertex3f(0.1 * cosine + 0.6, -1.0, 0.1 * sine + 1.0);
   }
   glEnd();

   glNormal3f(-0.6, 0.2, 1.0);
   glBegin(GL_TRIANGLE_FAN);
   glTexCoord2f(0.5, 0.5);
   glVertex3f(-0.6, 0.2, 1.0);
   for (int i = 0; i <= 360; i += 30)
   {
      float cosine = Cos(i);
      float sine = Sin(i);

      glNormal3f(cosine - 0.6, 0.2, sine + 1.0);
      glTexCoord2f(0.5 * cosine + 0.5, 0.5 * sine + 0.5);
      glVertex3f(0.1 * cosine - 0.6, 0.2, 0.1 * sine + 1.0);
   }
   glEnd();

   glNormal3f(-0.6, -1.0, 1.0);
   glBegin(GL_TRIANGLE_FAN);
   glTexCoord2f(0.5, 0.5);
   glVertex3f(-0.6, -1.0, 1.0);
   for (int i = 0; i <= 360; i += 30)
   {
      float cosine = Cos(i);
      float sine = Sin(i);

      glNormal3f(cosine - 0.6, -1.0, sine + 1.0);
      glTexCoord2f(0.5 * cosine + 0.5, 0.5 * sine + 0.5);
      glVertex3f(0.1 * cosine - 0.6, -1.0, 0.1 * sine + 1.0);
   }
   glEnd();

   // Draw Tent spikes.
   glBindTexture(GL_TEXTURE_2D, spike);
   DrawSpike(1.2, 1.2);
   DrawSpike(-1.2, 1.2);
   DrawSpike(-1.2, -1.2);
   DrawSpike(1.2, -1.2);

   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}

// Function definition for Tent object DrawSpike helper function.
void Tent::DrawSpike(float px, float pz)
{
   float textureRatio = 1.0/12.0;

   // Draw tent spike shaft component.
   glBegin(GL_QUAD_STRIP);
   for (int i = 0; i <= 12; i++)
   {
      int theta = i * 30;
      float x = 0.01 * Cos(theta);
      float z = 0.01 * Sin(theta);

      glNormal3f(x, -1.0, z);
      glTexCoord2f(0.0, textureRatio);
      glVertex3f(x + px, -1.0, z + pz);
      glTexCoord2f(12.0, textureRatio);
      glVertex3f(x + px, -0.9, z + pz);
   }
   glEnd();

   // Draw tent spike head component.
   glBegin(GL_QUAD_STRIP);
   for (int i = 0; i <= 12; i++)
   {
      int theta = i * 30;
      float x = 0.02 * Cos(theta);
      float z = 0.02 * Sin(theta);

      glNormal3f(x, -0.9, z);
      glTexCoord2f(0.0, textureRatio);
      glVertex3f(x + px, -0.9, z + pz);
      glTexCoord2f(12.0, textureRatio);
      glVertex3f(x + px, -0.89, z + pz);
   }
   glEnd();

   glNormal3f(px, -0.9, pz);
   glBegin(GL_TRIANGLE_FAN);
   glTexCoord2f(0.5, 0.5);
   glVertex3f(px, -0.9, pz);
   for (int i = 0; i <= 360; i += 30)
   {
      float cosine = Cos(i);
      float sine = Sin(i);

      glNormal3f(cosine + px, -0.9, sine + pz);
      glTexCoord2f(0.5 * cosine + 0.5, 0.5 * sine + 0.5);
      glVertex3f(cosine * 0.02 + px, -0.9, sine * 0.02 + pz);
   }
   glEnd();

   glNormal3f(px, -0.89, pz);
   glBegin(GL_TRIANGLE_FAN);
   glTexCoord2f(0.5, 0.5);
   glVertex3f(px, -0.89, pz);
   for (int i = 0; i <= 360; i += 30)
   {
      float cosine = Cos(i);
      float sine = Sin(i);

      glNormal3f(cosine + px, -0.89, sine + pz);
      glTexCoord2f(0.5 * cosine + 0.5, 0.5 * sine + 0.5);
      glVertex3f(cosine * 0.02 + px, -0.89, sine * 0.02 + pz);
   }
   glEnd();

}

bool Tent::detectCollision(Camera* camera)
{
   bool xCollide = camera->getEyeX() >= -this->posX - this->scaleX && camera->getEyeX() <= this->posX + this->scaleX;
   bool zCollide = camera->getEyeZ() >= -this->posZ - this->scaleZ && camera->getEyeZ() <= this->posZ + this->scaleZ;

   return xCollide && zCollide;
}

// Function definition for Tent object resovleCollision function implementation.
void Tent::resolveCollision(Camera* camera)
{
   // Account for rotations.
   float relX = camera->getEyeX() - this->posX;
   float relZ = camera->getEyeZ() - this->posZ;
   float camX = relX * Cos(this->rotY) - relZ * Sin(this->rotY);
   float camZ = relZ * Cos(this->rotY) + relX * Sin(this->rotY);
   
   // Compute the minimum/maximum x and z values for each wall, with offsets for player lantern.
   float minXLeft = -this->scaleX - 0.5;
   float maxXLeft = -this->scaleX + 0.5;
   float minXRight = this->scaleX - 0.5;
   float maxXRight = this->scaleX + 0.5;
   float minZBack = -this->scaleZ - 0.5;
   float maxZBack = -this->scaleZ + 0.5;
   float minZFront = this->scaleZ - 0.5;
   float maxZFront = this->scaleZ + 0.5;

   // If camera collided with back wall.
   if (camZ < maxZBack && camZ > minZBack && camX > minXLeft && camX < maxXRight)
   {
      float newX, newZ;

      if (camZ < -1.0)
      {
         newZ = minZBack + this->posZ;
         if (camX > maxXRight)
            newX = maxXRight + this->posX;
         else if (camX < minXLeft)
            newX = minXLeft + this->posX;
         else
            newX = camera->getEyeX();
      }
      else
      {
         newZ = maxZBack + this->posZ;
         if (camX > maxXRight)
            newX = maxXRight + this->posX;
         else if (camX < minXLeft)
            newX = minXLeft + this->posX;
         else
            if (camX < maxXLeft && camX > -1.0)
               newX = maxXLeft + this->posX;
            else if (camX > minXLeft && camX < -1.0)
            {
               newZ = camera->getEyeZ();
               newX = minXLeft + this->posX;
            }
            else if (camX > minXRight && camX < 1.0)
               newX = minXRight + this->posX;
            else if (camX < maxXRight && camX > 1.0)
            {
               newZ = camera->getEyeZ();
               newX = maxXRight + this->posX;
            }
            else
               newX = camera->getEyeX();
      }

   // Modify camera coordinates.
   camera->setEyePos(newX, camera->getEyeY(), newZ);
   }
   // If camera collided with the front wall (right of door). 
   else if (camZ < maxZFront && camZ > minZFront && camX < minXRight && camX > minXRight - 0.6)
   {
      float newX, newZ;

      if (camZ > 1.0)
      {
         if (camX < minXRight - 0.6 && camX > maxXLeft + 0.6)
            newZ = camera->getEyeZ();
         else
            newZ = maxZFront + this->posZ;
         if (camX > minXRight)
            newX = minXRight + this->posX;
         else if (camX < minXRight - 0.6)
            newX = minXRight - 0.6 + this->posX;
         else
            newX = camera->getEyeX();
      }
      else
      {
         newZ = minZFront + this->posZ;
         if (camX > minXRight)
            newX = minXRight + this->posX;
         else if (camX < minXRight - 0.6)
            newX = minXRight - 0.6 + this->posX;
         else
            newX = camera->getEyeX();
      }

      // Modify camera coordinates.
      camera->setEyePos(newX, camera->getEyeY(), newZ);
   }
   // If camera collided with the front wall (left of door).
   else if (camZ < maxZFront && camZ > minZFront && camX < maxXLeft + 0.6 && camX > maxXLeft)
   {
      float newX, newZ;

      if (camZ > 1.0)
      {
         if (camX < minXRight - 0.6 && camX > maxXLeft)
            newZ = camera->getEyeZ();
         else
            newZ = maxZFront + this->posZ;
         if (camX > maxXLeft + 0.6)
            newX = maxXLeft + 0.6 + this->posX;
         else if (camX < maxXLeft)
            newX = maxXLeft + this->posX;
         else
            newX = camera->getEyeX();
      }
      else
      {
         newZ = minZFront + this->posZ;
         if (camX > maxXLeft + 0.6)
            newX = maxXLeft + 0.6 + this->posX;
         else if (camX < maxXLeft)
            newX = maxXLeft + this->posX;
         else
            newX = camera->getEyeX();
      }

      // Modify camera coordinates.
      camera->setEyePos(newX, camera->getEyeY(), newZ);
   }
   // If player collides with the left wall.
   else if (camX > minXLeft && camX < maxXLeft && camZ < maxZFront && camZ > minZBack)
   {
      float newX, newZ;
      
      if(camX < -1.0)
      {
         newX = minXLeft + this->posX;
         if (camZ > maxZFront)
            newZ = maxZFront + this->posZ;
         else if (camZ < minZBack)
            newZ = minZBack + this->posZ;
         else
            newZ = camera->getEyeZ();
      }
      else
      {
         newX = maxXLeft + this->posX;
         if (camZ > minZFront)
            newZ = minZFront + this->posZ;
         else if (camZ < maxZBack)
            newZ = maxZBack + this->posZ;
         else
            newZ = camera->getEyeZ();
      }

      // Modify camera coordinates such that camera is outside of left wall boundaries.
      camera->setEyePos(newX, camera->getEyeY(), newZ);
   }
   // If camera collided with right wall.
   else if (camX > minXRight && camX < maxXRight && camZ < maxZFront && camZ > minZBack)
   {
      float newX, newZ;

      if (camX > 1.0)
      {
         newX = maxXRight + this->posX;
         if (camZ > maxZFront)
            newZ = maxZFront + this->posZ;
         else if (camZ < minZBack)
            newZ = minZBack + this->posZ;
         else
            newZ = camera->getEyeZ();
      }
      else
      {
         newX = minXRight + this->posX;
         if (camZ > minZFront)
            newZ = minZFront + this->posZ;
         else if (camZ < maxZBack)
            newZ = maxZBack + this->posZ;
         else
            newZ = camera->getEyeZ();
      }

      // Modify camera coordinates.
      camera->setEyePos(newX, camera->getEyeY(), newZ);
   }
}

// Function definition for Tent object setPosition function.
void Tent::setPosition(float x, float y, float z)
{
   this->posX = x;
   this->posY = y;
   this->posZ = z;
}

// Function definition for Tent object setScale function.
void Tent::setScale(float x, float y, float z)
{
   this->scaleX = x;
   this->scaleY = y;
   this->scaleZ = z;
}

// Function definition for Tent object setRotation function.
void Tent::setRotation(float x, float y, float z)
{
   this->rotX = x;
   this->rotY = y;
   this->rotZ = z;
}

// Function definition for Tent object getPosX function.
float Tent::getPosX()
{
   return this->posX;
}

// Function definition for Tent object getPosY function.
float Tent::getPosY()
{
   return this->posY;
}

// Function definition for Tent object getPosZ function.
float Tent::getPosZ()
{
   return this->posZ;
}

// Function definition for Tent object getScaleX function.
float Tent::getScaleX()
{
   return this->scaleX;
}

// Function definition for Tent object getScaleY function.
float Tent::getScaleY()
{
   return this->scaleY;
}

// Function definition for Tent object getScaleZ function.
float Tent::getScaleZ()
{
   return this->scaleZ;
}

// Function definition for Tent object getRotX function.
float Tent::getRotX()
{
   return this->rotX;
}

// Function definition for Tent object getRotY function.
float Tent::getRotY()
{
   return this->rotY;
}

// Function definition for Tent object getRotZ function.
float Tent::getRotZ()
{
   return this->rotZ;
}