#pragma once
#include "GameObject.h"
#include "CSCIx229.h"

class Cuboid : public GameObject
{
   private:
      unsigned char texture;
	  float xPos;
	  float yPos;
	  float zPos;
	  float xScale;
	  float yScale;
	  float zScale;
	  float xRot;
	  float yRot;
	  float zRot;

   public:
      Cuboid();
      Cuboid(float x, float y, float z, float scaleX, float scaleY, float scaleZ, float rotX, float rotY, float rotZ);
      ~Cuboid();
      int Initialize(const char* filename);
      void Render();
      float getPosX();
      float getPosY();
      float getPosZ();
      float getScaleX();
      float getScaleY();
      float getScaleZ();
      float getRotX();
      float getRotY();
      float getRotZ();
      void setPosition(float x, float y, float z);
      void setScale(float x, float y, float z);
      void setRotation(float x, float y, float z);
};