#include "Tent.h"

// Function definition for Tent object default constructor.
Tent::Tent()
{
   // Set the origin for the position.
   this->posX = 0.0;
   this->posY = 0.0;
   this->posZ = 0.0;

   // Give 1.0 scaling on all axes.
   this->scaleX = 1.0;
   this->scaleY = 1.0;
   this->scaleZ = 1.0;

   // Give 0.0 rotation about each axis.
   this->rotX = 0.0;
   this->rotY = 0.0;
   this->rotZ = 0.0;
}

// Function definition for Tent object constructor.
Tent::Tent(float x, float y, float z, float dx, float dy, float dz, float rx, float ry, float rz)
{
   // Apply the specified translation.
   this->posX = x;
   this->posY = y;
   this->posZ = z;

   // Apply the specified scaling.
   this->scaleX = dx;
   this->scaleY = dy;
   this->scaleZ = dz;

   // Apply the specified rotations.
   this->rotX = rx;
   this->rotY = ry;
   this->rotZ = rz;
}

// Function definition for Tent object Initialize function implementation.
int Tent::Initialize(const char* filename)
{
   // Load the object textures from Assets subdirectory.
   this->texture = LoadTexBMP(filename);
   this->spike = LoadTexBMP("Assets/RustyMetal.bmp");
   this->canvasWrap = LoadTexBMP("Assets/CanvasRoll.bmp");

   return 0;
}

// Function definition for Tent object Render function implementation.
void Tent::Render()
{
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

   // Draw Tent front left wall.
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

   // Draw Tent front right wall.
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

   // Draw Tent front door.
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
   glNormal3f(-1.0, 0.0, 0.0);
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
   glNormal3f(1.0, 0.0, 0.0);
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

   // Draw Tent roof front triangle.
   glNormal3f(0.0, 1.25, 1.0);
   glBegin(GL_TRIANGLES);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(-1.0, 1.0, 1.0);
   glTexCoord2f(this->scaleX, 0.0);
   glVertex3f(1.0, 1.0, 1.0);
   glTexCoord2f(this->scaleX/2.0, (0.5 * this->scaleY)/2.0);
   glVertex3f(0.0, 1.5, 1.0);
   glEnd();

   // Draw Tent roof back triangle.
   glNormal3f(0.0, 1.25, -1.0);
   glBegin(GL_TRIANGLES);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(1.0, 1.0, -1.0);
   glTexCoord2f(this->scaleX, 0.0);
   glVertex3f(-1.0, 1.0, -1.0);
   glTexCoord2f(this->scaleX/2.0, (0.5 * this->scaleY)/2.0);
   glVertex3f(0.0, 1.5, -1.0);
   glEnd();

   // Draw Tent roof left quad.
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

   // Draw Tent roof right quad.
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

   // Optimization - this value is used in several loops, no need to keep recomputing it every iteration of every loop.
   float textureRatio = 1.0 / 12.0;

   // Draw rolled right Tent flaps cyllender. 
   glBegin(GL_QUAD_STRIP);
   for (int i = 0; i <= 12; i++)
   {
      // Optimization - reduce number of floating-point computations per loop iteration.
      int theta = i * 30;
      float x = Cos(theta);
      float z = Sin(theta);
      int theta1 = (i + 1) * 30;
      float x1 = Cos(theta1);
      float z1 = Sin(theta1);

      // Optimization - draw four vertices per loop iteration and reduce the number of iterations (loop unrolling).
      glNormal3f(x, -1.0, z);
      glTexCoord2f(0.0, i * textureRatio);
      glVertex3f(x * 0.1 + 0.6, -1.0, z * 0.1 + 1.0);
      glTexCoord2f(12.0, i * textureRatio);
      glVertex3f(x * 0.1 + 0.6, 0.2, z * 0.1 + 1.0);

      glNormal3f(x1, -1.0, z1);
      glTexCoord2f(0.0, (i + 1) * textureRatio);
      glVertex3f(x1 * 0.1 + 0.6, -1.0, z1 * 0.1 + 1.0);
      glTexCoord2f(12.0, (i + 1) * textureRatio);
      glVertex3f(x1 * 0.1 + 0.6, 0.2, z1 * 0.1 + 1.0);
   }
   glEnd();

   // Draw rolled left Tent flaps cyllender.
   glBegin(GL_QUAD_STRIP);
   for (int i = 0; i <= 12; i += 2)
   {
      // Optimization - reduce number of floating-point computations per loop iteration.
      int theta = i * 30;
      float x = Cos(theta);
      float z = Sin(theta);
      int theta1 = (i + 1) * 30;
      float x1 = Cos(theta1);
      float z1 = Sin(theta1);

      // Optimization - draw four vertices per loop iteration and reduce the number of iterations (loop unrolling).
      glNormal3f(x, -1.0, z);
      glTexCoord2f(0.0, i * textureRatio);
      glVertex3f(x * 0.1 - 0.6, -1.0, z * 0.1 + 1.0);
      glTexCoord2f(12.0, i * textureRatio);
      glVertex3f(x * 0.1 - 0.6, 0.2, z * 0.1 + 1.0);

      glNormal3f(x1, -1.0, z1);
      glTexCoord2f(0.0, (i + 1) * textureRatio);
      glVertex3f(x1 * 0.1 - 0.6, -1.0, z1 * 0.1 + 1.0);
      glTexCoord2f(12.0, (i + 1) * textureRatio);
      glVertex3f(x1 * 0.1 - 0.6, 0.2, z1 * 0.1 + 1.0);
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

   // Bind rolled canvas texture.
   glBindTexture(GL_TEXTURE_2D, canvasWrap);

   // Draw right rolled tent flap top disc.
   glNormal3f(0.6, 0.2, 1.0);
   glBegin(GL_TRIANGLE_FAN);
   glTexCoord2f(0.5, 0.5);
   glVertex3f(0.6, 0.2, 1.0);
   for (int i = 0; i <= 360; i += 60)
   {
      // Optimization - reduce number of floating-point computations per loop iteration with local variables.
      float cosine = Cos(i);
      float sine = Sin(i);
      float cosine1 = Cos(i + 30);
      float sine1 = Sin(i + 30);

      // Optimization - draw two vertices per loop iteration and reduce number of iterations (loop unrolling).
      glNormal3f(cosine + 0.6, 0.2, sine + 1.0);
      glTexCoord2f(0.5 * cosine + 0.5, 0.5 * sine + 0.5);
      glVertex3f(0.1 * cosine + 0.6, 0.2, 0.1 * sine + 1.0);

      glNormal3f(cosine1 + 0.6, 0.2, sine1 + 1.0);
      glTexCoord2f(0.5 * cosine1 + 0.5, 0.5 * sine1 + 0.5);
      glVertex3f(0.1 * cosine1 + 0.6, 0.2, 0.1 * sine1 + 1.0);
   }
   glEnd();

   // Draw right rolled tent flap bottom disc.
   glNormal3f(0.6, -1.0, 1.0);
   glBegin(GL_TRIANGLE_FAN);
   glTexCoord2f(0.5, 0.5);
   glVertex3f(0.6, -1.0, 1.0);
   for (int i = 0; i <= 360; i += 60)
   {
      // Optimization - reduce floating-point computations per loop iteration with local variables.
      float cosine = Cos(i);
      float sine = Sin(i);
      float cosine1 = Cos(i + 30);
      float sine1 = Sin(i + 30);

      // Optimization - draw two vertices per loop iteration and reduce number of iterations (loop unrolling).
      glNormal3f(cosine + 0.6, -1.0, sine + 1.0);
      glTexCoord2f(0.5 * cosine + 0.5, 0.5 * sine + 0.5);
      glVertex3f(0.1 * cosine + 0.6, -1.0, 0.1 * sine + 1.0);

      glNormal3f(cosine1 + 0.6, -1.0, sine1 + 1.0);
      glTexCoord2f(0.5 * cosine1 + 0.5, 0.5 * sine1 + 0.5);
      glVertex3f(0.1 * cosine1 + 0.6, -1.0, 0.1 * sine1 + 1.0);
   }
   glEnd();

   // Draw left rolled tent flap top disc.
   glNormal3f(-0.6, 0.2, 1.0);
   glBegin(GL_TRIANGLE_FAN);
   glTexCoord2f(0.5, 0.5);
   glVertex3f(-0.6, 0.2, 1.0);
   for (int i = 0; i <= 360; i += 60)
   {
      // Optimization - reduce floating-point computations per loop iteration with local variables.
      float cosine = Cos(i);
      float sine = Sin(i);
      float cosine1 = Cos(i + 30);
      float sine1 = Sin(i + 30);

      // Optimization - draw two vertices per loop iteration and reduce number of iterations (loop unrolling).
      glNormal3f(cosine - 0.6, 0.2, sine + 1.0);
      glTexCoord2f(0.5 * cosine + 0.5, 0.5 * sine + 0.5);
      glVertex3f(0.1 * cosine - 0.6, 0.2, 0.1 * sine + 1.0);

      glNormal3f(cosine1 - 0.6, 0.2, sine1 + 1.0);
      glTexCoord2f(0.5 * cosine1 + 0.5, 0.5 * sine1 + 0.5);
      glVertex3f(0.1 * cosine1 - 0.6, 0.2, 0.1 * sine1 + 1.0);
   }
   glEnd();

   // Draw left rolled tent flap bottom disc.
   glNormal3f(-0.6, -1.0, 1.0);
   glBegin(GL_TRIANGLE_FAN);
   glTexCoord2f(0.5, 0.5);
   glVertex3f(-0.6, -1.0, 1.0);
   for (int i = 0; i <= 360; i += 60)
   {
      // Optimization - reduce floating-point computations per loop iteration with local variables.
      float cosine = Cos(i);
      float sine = Sin(i);
      float cosine1 = Cos(i + 30);
      float sine1 = Cos(i + 30);

      // Optimization - draw two vertices per loop iteration and reduce number of iterations (loop unrolling).
      glNormal3f(cosine - 0.6, -1.0, sine + 1.0);
      glTexCoord2f(0.5 * cosine + 0.5, 0.5 * sine + 0.5);
      glVertex3f(0.1 * cosine - 0.6, -1.0, 0.1 * sine + 1.0);

      glNormal3f(cosine1 - 0.6, -1.0, sine1 + 1.0);
      glTexCoord2f(0.5 * cosine1 + 0.5, 0.5 * sine1 + 0.5);
      glVertex3f(0.1 * cosine1 - 0.6, -1.0, 0.1 * sine1 + 1.0);
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

   // Draw tent spike shaft component cyllinder.
   glBegin(GL_QUAD_STRIP);
   for (int i = 0; i <= 12; i += 2)
   {
      // Optimization - reduce floating-point computations per loop iteration.
      int theta = i * 30;
      float x = 0.01 * Cos(theta);
      float z = 0.01 * Sin(theta);
      int theta1 = (i + 1) * 30;
      float x1 = 0.01 * Cos(theta1);
      float z1 = 0.01 * Sin(theta1);

      // Optimization - draw four vertices per loop iteration.
      glNormal3f(x, -1.0, z);
      glTexCoord2f(0.0, textureRatio);
      glVertex3f(x + px, -1.0, z + pz);
      glTexCoord2f(12.0, textureRatio);
      glVertex3f(x + px, -0.9, z + pz);

      glNormal3f(x1, -1.0, z1);
      glTexCoord2f(0.0, textureRatio);
      glVertex3f(x1 + px, -1.0, z1 + pz);
      glTexCoord2f(12.0, textureRatio);
      glVertex3f(x1 + px, -0.9, z1 + pz);
   }
   glEnd();

   // Draw tent spike head component cyllinder.
   glBegin(GL_QUAD_STRIP);
   for (int i = 0; i <= 12; i += 2)
   {
      // Optimization - reduce floating-point computations per loop iteration.
      int theta = i * 30;
      float x = 0.02 * Cos(theta);
      float z = 0.02 * Sin(theta);
      int theta1 = (i + 1) * 30;
      float x1 = 0.02 * Cos(theta1);
      float z1 = 0.02 * Sin(theta1);

      // Optimization - draw four vertices per loop iteration.
      glNormal3f(x, -0.9, z);
      glTexCoord2f(0.0, textureRatio);
      glVertex3f(x + px, -0.9, z + pz);
      glTexCoord2f(12.0, textureRatio);
      glVertex3f(x + px, -0.89, z + pz);

      glNormal3f(x1, -0.9, z1);
      glTexCoord2f(0.0, textureRatio);
      glVertex3f(x1 + px, -0.9, z1 + pz);
      glTexCoord2f(12.0, textureRatio);
      glVertex3f(x1 + px, -0.89, z1 + pz);
   }
   glEnd();

   // Draw tent spike head component bottom disc.
   glNormal3f(px, -0.9, pz);
   glBegin(GL_TRIANGLE_FAN);
   glTexCoord2f(0.5, 0.5);
   glVertex3f(px, -0.9, pz);
   for (int i = 0; i <= 360; i += 60)
   {
      // Optimization - reduce floating-point computations per loop iteration with local variables.
      float cosine = Cos(i);
      float sine = Sin(i);
      float cosine1 = Cos(i + 30);
      float sine1 = Sin(i + 30);

      // Optimization - draw two vertices per loop iteration.
      glNormal3f(cosine + px, -0.9, sine + pz);
      glTexCoord2f(0.5 * cosine + 0.5, 0.5 * sine + 0.5);
      glVertex3f(cosine * 0.02 + px, -0.9, sine * 0.02 + pz);

      glNormal3f(cosine1 + px, -0.9, sine1 + pz);
      glTexCoord2f(0.5 * cosine1 + 0.5, 0.5 * sine1 + 0.5);
      glVertex3f(cosine1 * 0.02 + px, -0.9, sine1 * 0.02 + pz);
   }
   glEnd();

   // Draw tent spike head component top disc.
   glNormal3f(px, -0.89, pz);
   glBegin(GL_TRIANGLE_FAN);
   glTexCoord2f(0.5, 0.5);
   glVertex3f(px, -0.89, pz);
   for (int i = 0; i <= 360; i += 60)
   {
      // Optimization - reduce floating-point computations per loop iteration with local variables.
      float cosine = Cos(i);
      float sine = Sin(i);
      float cosine1 = Cos(i + 30);
      float sine1 = Sin(i + 30);

      // Optimization - draw two vertices per loop iteration.
      glNormal3f(cosine + px, -0.89, sine + pz);
      glTexCoord2f(0.5 * cosine + 0.5, 0.5 * sine + 0.5);
      glVertex3f(cosine * 0.02 + px, -0.89, sine * 0.02 + pz);

      glNormal3f(cosine1 + px, -0.89, sine1 + pz);
      glTexCoord2f(0.5 * cosine1 + 0.5, 0.5 * sine1 + 0.5);
      glVertex3f(cosine1 * 0.02 + px, -0.89, sine1 * 0.02 + pz);
   }
   glEnd();
}

// Function definition for Tent object detectCollision function implementation.
bool Tent::detectCollision(Camera* camera)
{
   // Compute relative x, z coordinates and convert to object coordinates.
   float cosine = Cos(this->rotY);
   float sine = Sin(this->rotY);
   float camX = camera->getEyeX() - this->posX;
   float camZ = camera->getEyeZ() - this->posZ;
   float objX = (camX * cosine) - (camZ * sine);
   float objZ = (camZ * cosine) + (camX * sine);

   // Compute x, z minimum and maximum values for object hitbox.
   float minX = -this->scaleX - 0.6;
   float maxX = this->scaleX + 0.6;
   float minZ = -this->scaleZ - 0.6;
   float maxZ = this->scaleZ + 0.6;

   // Determine if camera is colliding with the object along the x or z axis, respectively.
   bool xCollide = (objX > minX && objX < -this->scaleX + 0.6) || (objX > this->scaleX - 0.6 && objX < maxX);
   bool zCollide = (objZ > minZ && objZ < -this->scaleZ + 0.6) || (objZ > this->scaleZ - 0.6 && objZ < maxZ);
   bool xInside = objX > minX && objX < maxX;
   bool zInside = objZ > minZ && objZ < maxZ;

   // Camera is colliding with the object iff it is colliding along both x and y axis.
   return (xCollide && zInside) || (zCollide && xInside);
}

// Definition of Tent class getWall function. 
wall Tent::getWall(Camera* camera)
{
   // Compute relative x, z coordinates and convert to object coordinates.
   float cosine = Cos(this->rotY);
   float sine = Sin(this->rotY);
   float camX = camera->getEyeX() - this->posX;
   float camZ = camera->getEyeZ() - this->posZ;
   float objX = (camX * cosine) - (camZ * sine);
   float objZ = (camZ * cosine) + (camX * sine);

   // Convert Camera world coordinates to object coordinate system. 
   float diffXMin = objX - (-this->scaleX - 0.6);
   float diffXMax = (this->scaleX + 0.6) - objX;
   float diffZMin = objZ - (-this->scaleZ - 0.6);
   float diffZMax = (this->scaleZ + 0.6) - objZ;

   // Determine if collision occured with the back wall, left wall, right wall, front right wall or front left wall.
   bool back = diffZMin < diffZMax && diffZMin <= diffXMin && diffZMin <= diffXMax;
   bool frontRight = diffZMax < diffZMin && diffZMax <= diffXMin && diffZMax <= diffXMax && objX > 0.3;
   bool frontLeft = diffZMax < diffZMin && diffZMax <= diffXMin && diffZMax <= diffZMin && objX < -0.3;
   bool left = diffXMin < diffXMax && diffXMin < diffZMin && diffXMin < diffZMax;
   bool right = diffXMax < diffXMin && diffXMax < diffZMin && diffXMax < diffZMax;

   // Return appropriate enum value.
   if (back)
      return BACK;
   else if (frontRight)
      return FRONT_RIGHT;
   else if (frontLeft)
      return FRONT_LEFT;
   else if (left)
      return LEFT;
   else if (right)
      return RIGHT;
   else
      return NONE;   
}

// Function definition for Tent object resovleCollision function implementation.
void Tent::resolveCollision(Camera* camera)
{
   // Compute relative x, z coordinates and convert to object coordinates.
   float cosine = Cos(this->rotY);
   float sine = Sin(this->rotY);
   float camX = camera->getEyeX() - this->posX;
   float camZ = camera->getEyeZ() - this->posZ;
   float objX = (camX * cosine) - (camZ * sine);
   float objZ = (camZ * cosine) + (camX * sine);

   // Compute x, z maximum and minimum values.
   float minX = -this->scaleX - 0.6;
   float maxX = this->scaleX + 0.6;
   float minZ = -this->scaleZ - 0.6;
   float maxZ = this->scaleZ + 0.6;

   // Get the wall that the Camera is colliding with.
   wall collision = getWall(camera);

   // If camera collided with back wall.
   if (collision == BACK)
   {
      float newX, newZ;

      // If player collides with wall exterior.
      if (objZ < -this->scaleZ)
      {
         newZ = minZ;
         newX = objX;
      }
      // If player collides with wall interior.
      else
      {
         if (objX < this->scaleX && objX > -this->scaleX)
         {
            newZ = -this->scaleZ + 0.6;
            if (objX > this->scaleX - 0.6)
               newX = this->scaleX - 0.6;
            else if (objX < -this->scaleX + 0.6)
               newX = -this->scaleX + 0.6;
            else
               newX = objX;
         }
         else if (objX > this->scaleX)
         {
            newZ = (objX > this->scaleX) ? objZ : -this->scaleZ + 0.6;
            newX = (objX > this->scaleX) ? maxX : this->scaleX - 0.6;
         }
         else 
         {
            newZ = (objX < -this->scaleX) ? objZ : -this->scaleZ + 0.6;
            newX = (objX < -this->scaleX) ? minX : -this->scaleX + 0.6;
         }
      }

   // Undo transformations to convert back to world coordinates (inverse transform matrix courtesy of Symbolab).
   newX = -(newX * cosine / (-sine * sine - cosine * cosine)) - (newZ * sine / (-sine * sine - cosine * cosine));
   newZ = (objX * sine / (-sine * sine - cosine * cosine)) - (newZ * cosine / (-sine * sine - cosine * cosine));
   newX += this->posX;
   newZ += this->posZ;

   // Update Camera eye position.
   camera->setEyePos(newX, camera->getEyeY(), newZ);
   }
   // If Camera collided with the front wall(right of door).
   else if (collision == FRONT_RIGHT)
   {
      float newX, newZ;

      // If player collides with wall exterior.
      if (objZ > this->scaleZ)
      {
         newX = objX;
         newZ = maxZ;
      }
      // If player collides with wall interior.
      else
      {
         if (objX > this->scaleX - 0.6)
            newX = this->scaleX - 0.6;
         else
            newX = objX;
         newZ = this->scaleZ - 0.6;
      }

      // Undo transformations to convert back to world coordinates (inverse transform matrix courtesy of Symbolab).
      newX = -(newX * cosine / (-sine * sine - cosine * cosine)) - (newZ * sine / (-sine * sine - cosine * cosine));
      newZ = (objX * sine / (-sine * sine - cosine * cosine)) - (newZ * cosine / (-sine * sine - cosine * cosine));
      newX += this->posX;
      newZ += this->posZ;

      // Update Camera eye position.
      camera->setEyePos(newX, camera->getEyeY(), newZ);
   }
   // If camera collided with the front wall(left of door).
   else if (collision == FRONT_LEFT)
   {
      float newX, newZ;

      // If player collides with wall exterior.
      if (objZ > this->scaleZ)
      {
         newX = objX;
         newZ = maxZ;
      }
      // If player collides with wall interior.
      else
      {
         if (objX < -this->scaleX + 0.6)
            newX = -this->scaleX + 0.6;
         else
            newX = objX;
         newZ = this->scaleZ - 0.6;
      }

      // Undo transformations to convert back to world coordinates (inverse transform matrix courtesy of Symbolab).
      newX = -(newX * cosine / (-sine * sine - cosine * cosine)) - (newZ * sine / (-sine * sine - cosine * cosine));
      newZ = (objX * sine / (-sine * sine - cosine * cosine)) - (newZ * cosine / (-sine * sine - cosine * cosine));
      newX += this->posX;
      newZ += this->posZ;

      // Update Camera eye position.
      camera->setEyePos(newX, camera->getEyeY(), newZ);
   }
   // If player collides with the left wall.
   else if (collision == LEFT)
   {
      float newX, newZ;
      
      // If player collides with wall exterior.
      if(objX < -this->scaleX)
      {
         newX = minX;
         newZ = objZ;
      }
      // If player collides with wall interior.
      else
      {

         if (objZ > this->scaleZ - 0.6)
         {
            newX = -this->scaleX + 0.6;
            newZ = this->scaleZ - 0.6;
         }
         else if (objZ < -this->scaleZ + 0.6)
         {
            newX = -this->scaleX + 0.6;
            newZ = -this->scaleZ + 0.6;
         }
         else
         {
            newX = -this->scaleX + 0.6;
            newZ = objZ;
         }
      }

      // Undo transformations to convert back to world coordinates (inverse transform matrix courtesy of Symbolab).
      newZ = (newX * sine / (-sine * sine - cosine * cosine)) - (newZ * cosine / (-sine * sine - cosine * cosine));
      newX = -(newX * cosine / (-sine * sine - cosine * cosine)) - (objZ * sine / (-sine * sine - cosine * cosine));
      newX += this->posX;
      newZ += this->posZ;

      // Update Camera eye position.
      camera->setEyePos(newX, camera->getEyeY(), newZ);
   }
   // If camera collided with right wall.
   else if (collision == RIGHT)
   {
      float newX = 0, newZ = 0;

      // If player collides with wall exterior.
      if (objX > this->scaleX)
      {
         newX = maxX;
         newZ = objZ;
      }
      // If player collides with wall interior.
      else
      {

         if (objZ > this->scaleZ - 0.6)
         {
            newX = this->scaleX - 0.6;
            newZ = this->scaleZ - 0.6;
         }
         else if (objZ < -this->scaleZ + 0.6)
         {
            newX = this->scaleX - 0.6;
            newZ = -this->scaleZ + 0.6;
         }
         else
         {
            newX = this->scaleX - 0.6;
            newZ = objZ;
         }
      }

      // Undo transformations to convert back to world coordinates (inverse transform matrix courtesy of Symbolab).
      newZ = (newX * sine / (-sine * sine - cosine * cosine)) - (newZ * cosine / (-sine * sine - cosine * cosine));
      newX = -(newX * cosine / (-sine * sine - cosine * cosine)) - (objZ * sine / (-sine * sine - cosine * cosine));
      newX += this->posX;
      newZ += this->posZ;

      // Update Camera eye position.
      camera->setEyePos(newX, camera->getEyeY(), newZ);
   }
}

// Function definition for Tent object setPosition function.
void Tent::setPosition(float x, float y, float z)
{
   // Set object translation coordinates.
   this->posX = x;
   this->posY = y;
   this->posZ = z;
}

// Function definition for Tent object setScale function.
void Tent::setScale(float x, float y, float z)
{
   // Set object scaling.
   this->scaleX = x;
   this->scaleY = y;
   this->scaleZ = z;
}

// Function definition for Tent object setRotation function.
void Tent::setRotation(float x, float y, float z)
{
   // Set object rotation about each axis.
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