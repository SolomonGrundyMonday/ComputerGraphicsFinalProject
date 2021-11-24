/*
 *   Cabin class declaration.
 *   Created by Jeff Colgan, October 27, 2021,
 *   CSCI-4229 Computer Graphics : Final Project.
 */

#pragma once

#include "GameObject.h"

#define WALL_HEIGHT 1.0
#define STEEPLE_HEIGHT 1.0
#define CABIN_LENGTH 1.5
#define CABIN_WIDTH 1.0
#define HINGE_RADIUS 0.005
#define HINGE_HEIGHT 0.1
#define KNOB_RADIUS 0.001
#define KNOB_PROTRUSION 0.0025
#define OVERHANG 0.1
#define WINDOW_HEIGHT 0.4
#define WINDOW_WIDTH 0.05
#define WINDOW_DEPTH 0.005

class Cabin : public GameObject
{
   // private member variables for translation, rotation, scaling and texture.
   private:
      unsigned char texture;
      unsigned char shingles;
      unsigned char wood;
      unsigned char shutters;
      unsigned char metal;
      float posX;
      float posY;
      float posZ;
      float scaleX;
      float scaleY;
      float scaleZ;
      float rotX;
      float rotY;
      float rotZ;
      const float white[4] = { 1.0, 1.0, 1.0, 1.0 };
      const float gold[4] = { 0.831, 0.686, 0.216, 1.0 };

      /*
       *   Function prototype for Cabin object drawWindow helper function.
       *   Precondition:  A Cabin object has been instantiated, and this function is called from within
       *                  this object's Render function.
       *   Postcondition: A window has been drawn on the left or right side of the cabin (depending on the
       *                  x-value passed into the function) with the center point at the specified coordinates.
       *   Parameters:    The coordinates of the window's center point.     
       */
      void drawWindow(float x, float y, float z);

   public:
     
      /*
       *   Function prototype for Cabin object default constructor.  DO NOT USE.
       *   Precondition:  None.
       *   Postcondition: A Cabin object has been instantiated at the origin (0, 0, 0) with 1.0
       *                  scaling on all axes and 0.0 rotation about each axis.  
       */
      Cabin();

      /*
       *   Function prototype for Cabin object constructor.
       *   Precondition:  None.
       *   Postcondition: A Cabin object has been instantiated with the specified translation, scaling
       *                  and rotation.
       *   Parameters:    (x, y, z) coordinates for the object's translation, (x, y, z) values for the object's 
       *                  scaling, and (x, y, z) values for the object's rotation about the corresponding axis. 
       */
      Cabin(float x, float y, float z, float dx, float dy, float dz, float rx, float ry, float rz);

      /*
       *   Function prototype for Cabin object implementation of Initialize function.
       *   Precondition:  An instance of a Cabin object has been instantiated, and a valid bmp filename 
       *                  has been passed into the function.
       *   Postcondition: The texture(s) for the object have been loaded from a bmp file and applied to the texture field.
       *   Parameters:    The filename for a valid bmp file in 3 X 8 bit RGB format, with maximum size of 512 X 512 pixels. 
       */
      int Initialize(const char* filename);

      /*
       *    Function prototype for Cabin object implementation of resolveCollision function.
       *    Precondition:  An instance of a Cabin object has been instantiated, and the object has been rendered to the scene.
       *    Postcondition: If a Camera has collided with the object, the collision has been resolved, and the Camera's position
       *                   has been updated such that the Camera is prevented from "clipping" through the object.
       *    Parameter:     The active Camera object. 
       */
      void resolveCollision(Camera* camera);

      /*
       *    Function prototype for Cabin object implementation of Render function.
       *    Precondition:  An instance of a Cabin object has been instantiated, and the textures have been loaded through
       *                   a call to Initialize.  This function must be ccalled from the display function of an OpenGL
       *                   application, or undefined behavior will result.
       *    Postcondition: The object has been rendered in the OpenGL window. 
       */
      void Render();

      /*
       *    Function prototype for Cabin object setPosition setter function.
       *    Precondition:  None.
       *    Postcondition: The object's translation has been changed to the specified values.
       *    Parameters:    The desired (x, y, z) coordinates for the object's new translation.  
       */
      void setPosition(float x, float y, float z);

      /*
       *    Function prototype for Cabin object setScale setter function.
       *    Precondition:  None.
       *    Postcondition: The object's scaling has been changed to the specified values.
       *    Parameters:    The desired x, y, z scaling. 
       */
      void setScale(float x, float y, float z);

      /*
       *    Function prototype for Cabin object setRotation setter function.
       *    Precondition:  None.
       *    Postcondition: The object's rotation about each axis has been changed to the specified vlaues.
       *    Parameters:    The desired rotation about the x, y and z axes respectively. 
       */
      void setRotation(float x, float y, float z);

      /*
       *    Function prototype for Cabin object getPosX getter function.
       *    Precondition:  None.
       *    Postcondition: The x-value of the object's translation has been returned to the caller.
       *    Return value:  The x-value of the object's translation.   
       */
      float getPosX();

      /*
       *    Function prototype for Cabin object getPosY getter function.
       *    Precondition:  None.
       *    Postcondition: The y-value of the object's translation has been returned to the caller.
       *    Return value:  The y-value of the object's translation.  
       */
      float getPosY();

      /*
       *    Function prototype for Cabin object getPosZ getter function.
       *    Precondition:  None.
       *    Postcondition: The z-value of the object's translation has been returned to the caller.
       *    Return value:  The z-value of the object's translation.  
       */
      float getPosZ();

      /*
       *    Function prototype for Cabin object getScaleX getter function.
       *    Precondition:  None.
       *    Postcondition: The x-value of the object's scaling has been returned to the caller.
       *    Return value:  The x-scaling of the object. 
       */
      float getScaleX();

      /*
       *    Function prototype for Cabin object getScaleY getter function.
       *    Precondition:  None.
       *    Postcondition: The y-value of the object's scaling has been returned to the caller.
       *    Return value:  The y-scaling of the object. 
       */
      float getScaleY();

      /*
       *    Function prototype for Cabin object getScaleZ getter function.
       *    Precondition:  None.
       *    Postcondition: The z-value of the object's scaling has been returned to the caller.
       *    Return value:  The z-scaling of the object. 
       */
      float getScaleZ();

      /*
       *    Function prototype for Cabin object getRotX getter function.
       *    Precondition:  None.
       *    Postcondition: The x-value of the object's rotation has been returned to the caller.
       *    Return value:  The object's rotation about the x-axis (in degrees). 
       */
      float getRotX();

      /*
       *    Function prototype for Cabin object getRotY getter function.
       *    Precondition:  None.
       *    Postcondition: The y-value of the object's rotation has been returned to the caller.
       *    Return value:  The object's rotation about the y-axis (in degrees).  
       */
      float getRotY();

      /*
       *    Function prototype for Cabin object getRotZ getter function.
       *    Precondition:  None.
       *    Postcondition: The z-value for the object's rotation has been returned to the caller.
       *    Return value:  The object's rotation about the z-axis (in degrees). 
       */
      float getRotZ();
};