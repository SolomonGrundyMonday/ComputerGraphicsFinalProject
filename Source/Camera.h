/*
 *   Camera class declaration.
 *
 *   Created by Jeff Colgan, October 25, 2021,
 *   CSCI-4229 Computer Graphics : Final Project.
 *
 *   This class controls all of the parameters for the player
 *   camera.  Only one such object should ever be instantiated
 *   in one application, otherwise undefined behavior will result. 
 */

#pragma once

#include "CSCIx229.h"

#ifndef VECTOR_SIZE
#define VECTOR_SIZE 3

class Camera
{
   // Member variables for eye position, center position, up vector, focal length and field of view.
   private:
      int theta;
      double EyePos[VECTOR_SIZE];
      double CenterPos[VECTOR_SIZE];
      double UpPos[VECTOR_SIZE];
      double dim;
      double asp;

   public:
      /*
       *   Function prototype for Camera class default constructor.
       *   Precondition:  None.
       *   Postcondition: A Camera object has been instantiated in the default position,
       *                  looking at the default point and with the default up direction.  
       */
      Camera();
      void MoveForward();
      void MoveBackward();
      void Turn();
      void setEyePos(double x, double y, double z);
      void setCenterPos(double x, double y, double z);
      void setUpPos(double x, double y, double z);
      void setDim(double dim);
      void setAsp(double asp);
      void setTheta(int theta);
      double getEyeX();
      double getEyeY();
      double getEyeZ();
      double getCenterX();
      double getCenterY();
      double getCenterZ();
      double getUpX();
      double getUpY();
      double getUpZ();
      double getDim();
      double getAsp();
      double getTheta();
};

#endif