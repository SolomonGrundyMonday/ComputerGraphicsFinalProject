/*
 *   Skybox class definition.
 *   Created by Jeff Colgan, November 2, 2021.
 *   Computer Graphics: Final Project. 
 */

#include "Skybox.h"

// Skybox class default constructor definition.
Skybox::Skybox()
{
   // Set object translation coordinates.
   this->posX = 0.0;
   this->posY = 0.0;
   this->posZ = 0.0;

   // Set object scaling.
   this->scaleX = 1.0;
   this->scaleY = 1.0;
   this->scaleZ = 1.0;

   // Set object's rotation about each axis.
   this->rotX = 0.0;
   this->rotY = 0.0;
   this->rotZ = 0.0;
}

// Skybox class constructor defintion.
Skybox::Skybox(float x, float y, float z, float dx, float dy, float dz, float rx, float ry, float rz)
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

// Skybox class Initialize function implementation definition.
int Skybox::Initialize(const char* filename)
{
   // Load object texture from Assets subdirectory.
   this->texture = LoadTexBMP(filename);

   return 0;
}

// Skybox class Render function implementation definition.
void Skybox::Render()
{
   // Optimization - compute texture coordinates once per Render call.
   float texX = this->scaleX / 10.0;
   float texY = this->scaleY / 10.0;
   float texZ = this->scaleZ / 10.0;

   // Enable textures, front face culling (since we are inside the skybox).
   glEnable(GL_TEXTURE_2D);
   glEnable(GL_CULL_FACE);
   glCullFace(GL_FRONT);

   // For the skybox, I specifically want GL_REPLACE, since it is the skybox, I don't want its color affected by either the color state machine or lighting.
   glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
   glBindTexture(GL_TEXTURE_2D, texture);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

   glPushMatrix();

   // Apply object's translation, rotation and scaling.
   glTranslatef(this->posX, this->posY, this->posZ);
   glRotatef(this->rotX, 1, 0, 0);
   glRotatef(this->rotY, 0, 1, 0);
   glRotatef(this->rotZ, 0, 0, 1);
   glScalef(this->scaleX, this->scaleY, this->scaleZ);

   // Set material properties, ambient white black specular.
   glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 128.0);
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, white);
   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, black);

   // No normals because the skybox should not be affected by the local lighting.
   for (int i = 0; i < 20; i += 4)
   {
      int vert2 = i + 1;
      int vert3 = i + 2;
      int vert4 = i + 3;

      glBegin(GL_QUADS);

      // Draw "roof" of the skybox.
      if (i == 0)
      {
         glTexCoord2f(0.0, 0.0);
         glVertex3f(vertices[i][0], vertices[i][1], vertices[i][2]);
         glTexCoord2f(texX, 0.0);
         glVertex3f(vertices[vert2][0], vertices[vert2][1], vertices[vert2][2]);
         glTexCoord2f(texX, texZ);
         glVertex3f(vertices[vert3][0], vertices[vert3][1], vertices[vert3][2]);
         glTexCoord2f(0.0, texZ);
         glVertex3f(vertices[vert4][0], vertices[vert4][1], vertices[vert4][2]);
      }
      // Draw the left and right "walls" of the skybox.
      else if (i == 4 || i == 8)
      {
         glTexCoord2f(0.0, 0.0);
         glVertex3f(vertices[i][0], vertices[i][1], vertices[i][2]);
         glTexCoord2f(texZ, 0.0);
         glVertex3f(vertices[vert2][0], vertices[vert2][1], vertices[vert2][2]);
         glTexCoord2f(texZ, texY);
         glVertex3f(vertices[vert3][0], vertices[vert3][1], vertices[vert3][2]);
         glTexCoord2f(0.0, texY);
         glVertex3f(vertices[vert4][0], vertices[vert4][1], vertices[vert4][2]);
      }
      // Draw the front and back "walls" of the skybox.
      else
      {
         glTexCoord2f(0.0, 0.0);
         glVertex3f(vertices[i][0], vertices[i][1], vertices[i][2]);
         glTexCoord2f(texX, 0.0);
         glVertex3f(vertices[vert2][0], vertices[vert2][1], vertices[vert2][2]);
         glTexCoord2f(texX, texY);
         glVertex3f(vertices[vert3][0], vertices[vert3][1], vertices[vert3][2]);
         glTexCoord2f(0.0, texY);
         glVertex3f(vertices[vert4][0], vertices[vert4][1], vertices[vert4][2]);
      }
      glEnd();
   }

   glPopMatrix();
   glDisable(GL_CULL_FACE);
   glDisable(GL_TEXTURE_2D);
}

// Skybox class resolveCollision function definition.
void Skybox::resolveCollision(Camera* camera)
{
   // This collision implementation is deprecated, now handled by Horizon object.
   // Reduce function calls within display function.
   float camX = camera->getEyeX();
   float camZ = camera->getEyeZ();
   float xOffset = (0.7 * Sin(camera->getTheta()));
   float zOffset = (0.7 * Cos(camera->getTheta()));

   // If the camera x-value is beyond the negative limit of the skybox.
   if (camX + (xOffset - 0.5) < -this->scaleX)
   {
      camera->setEyePos(-this->scaleX - (xOffset - 0.5), camera->getEyeY(), camZ);
   }
   // If the camera x-value is beyond the positive limit of the skybox.
   else if (camX + (xOffset + 0.5) > this->scaleX)
   {
      camera->setEyePos(this->scaleX - (xOffset + 0.5), camera->getEyeY(), camZ);
   }

   // If the camera z-value is beyond the negative limit of the skybox.
   if (camZ - (zOffset + 0.5) < -this->scaleZ)
   {
      // Nested decision structure prevents camera from clipping through "holes" in the coroners of the map.
      if (camX + (xOffset - 0.5) < -this->scaleX)
         camera->setEyePos(-this->scaleX - (xOffset - 0.5), camera->getEyeY(), -this->scaleZ + (zOffset + 0.5));
      else if (camX + (xOffset + 0.5) > this->scaleX)
         camera->setEyePos(this->scaleX - (xOffset + 0.5), camera->getEyeY(), -this->scaleZ + (zOffset + 0.5));
      else
         camera->setEyePos(camX, camera->getEyeY(), -this->scaleZ + (zOffset + 0.5));
   }
   // If the camera z-value is beyond the positive limit of the skybox.
   else if (camZ - (zOffset - 0.5) > this->scaleZ)
   {
      // Nested decision structure prevents camera from clipping through "holes" in the corners of the map.
      if (camX + (xOffset - 0.5) < -this->scaleX)
         camera->setEyePos(-this->scaleX - (xOffset - 0.5), camera->getEyeY(), this->scaleZ + (zOffset - 0.5));
      else if (camX + (xOffset + 0.5) > this->scaleX)
         camera->setEyePos(this->scaleX - (xOffset + 0.5), camera->getEyeY(), this->scaleZ + (zOffset - 0.5));
      else
         camera->setEyePos(camX, camera->getEyeY(), this->scaleZ + (zOffset - 0.5));
   }
}

// Skybox class setPosition function definition.
void Skybox::setPosition(float x, float y, float z)
{
   // Set object translation coordinates.
   this->posX = x;
   this->posY = y;
   this->posZ = z;
}

// Skybox class setScale function definition.
void Skybox::setScale(float x, float y, float z)
{
   // Set object's scaling.
   this->scaleX = x;
   this->scaleY = y;
   this->scaleZ = z;
}

// Skybox class setRotation function definition.
void Skybox::setRotation(float x, float y, float z)
{
   // Set object's rotation about each axis.
   this->rotX = x;
   this->rotY = y;
   this->rotZ = z;
}

// Skybox class getPosX function definition.
float Skybox::getPosX()
{
   return this->posX;
}

// Skybox class getPosY function definition.
float Skybox::getPosY()
{
   return this->posY;
}

// Skybox class getPosZ function definition.
float Skybox::getPosZ()
{
   return this->posZ;
}

// Skybox class getScaleX function definition.
float Skybox::getScaleX()
{
   return this->scaleX;
}

// Skybox class getScaleY function definition.
float Skybox::getScaleY()
{
   return this->scaleY;
}

// Skybox class getScaleZ function definition.
float Skybox::getScaleZ()
{
   return this->scaleZ;
}

// Skybox class getRotX function definition.
float Skybox::getRotX()
{
   return this->rotX;
}

// Skybox class getRotY function definition.
float Skybox::getRotY()
{
   return this->rotY;
}

// Skybox class getRotZ function definition.
float Skybox::getRotZ()
{
   return this->rotZ;
}