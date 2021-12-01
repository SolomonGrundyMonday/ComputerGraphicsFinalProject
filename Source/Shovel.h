/*
 *   Shovel class declaration.
 *
 *   Created by Jeff Colgan, October 26, 2021,
 *   CSCI-4229 Computer Graphics: Final Project. 
 */

#pragma once

#include "GameObject.h"

#define HANDLE_LEN 0.15
#define HANDLE_HEIGHT 0.2
#define SHAFT_LEN 1.2
#define HEAD_LEN 0.4
#define HEAD_WIDTH 0.3
#define RADIUS 0.05

class Shovel : public GameObject
{
   // Private member variables for translation, rotation, scaling and textures.
   private:
      unsigned char texture;
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

      /*
       *   Function prototype for Shovel object getWall helper function.
       *   Precondition:  A Shovel object has been instantiated and rendered to the scene.
       *   Postcondition: The function returns the wall with which the Camera object has collided.
       *   Parameter:     The active Camera object.
       *   Return value:  The wall with which the camera has collided.  
       */
      wall getSide(Camera* camera);

   public:

      /*
       *   Function prototype for Shovel object default constructor.  DO NOT USE.
       *   Precondition:  None.
       *   Postcondition: A Shovel object has been instantiated at the origin (0, 0, 0) with 1.0
       *                  scaling on all axes, and 0.0 rotation about each axis.
       */
      Shovel();

      /*
       *   Function prototype for Shovel object constructor.
       *   Precondition:  None.
       *   Postcondition: A Shovel object has been instantiated with the specified translation,
       *   scaling and rotation.
       *   Parameters:    (x, y, z) coordinates for the object's translation, (x, y, z) values for the object's
       *                  scaling, and (x, y, z) values for the object's rotation about the corresponding axes.
       */
      Shovel(float x, float y, float z, float dx, float dy, float dz, float rx, float ry, float rz);

      /*
       *    Function prototype for the Shovel objects Initialize function implementation.
       *    Precondition:  A Shovel object has been instantiated and a valid RGB bitmap filename has been provided.
       *    Postcondition: A texture has been loaded from a .bmp file and applied to the texture field of the object.
       *    Parameters:    The filename for a .bmp in RGB 3 X 8 bit format with maximum dimensions of 512 X 512 pixels.
       */
      int Initialize(const char* filename);

      /*
       *    Function prototype for the Shovel object Render function implementation.
       *    Precondition:  An instance of a Shovel object has been instantiated and initialized.  This function
       *                   must be called from within the display function of an OpenGL application, or undefined behavior
       *                   will result.
       *    Postcondition: The object has been rendered in the OpenGL window. 
       */
      void Render();

      /*
       *    Function prototype for Shovel object detectCollision function.
       *    Precondition:  A Shovel object has been instantiated and rendered to the scene.
       *    Postcondition: The function returns the side with which the Camera object has collided.  
       *    Parameter:     The active Camera object.
       *    Return value:  The side with which the Camera object has collided.  
       */
      bool detectCollision(Camera* camera);

      /*
       *    Function prototype for the Shovel object resolveCollision function implementation.
       *    Precondition:  An instance of a Shovel object has been instantated and rendered to the scene.
       *    Postcondition: If a Camera has collided with the object, the collision has been resolved, and the Camera's
       *                   position has been updated such that the Camera is prevented from "clipping" through the object.
       *    Parameter:     The active Camera object.  
       */
      void resolveCollision(Camera* camera);

      /*
       *    Function prototype for Shovel object setPosition setter function.
       *    Precondition:  None.
       *    Postcondition: The translation of the Shovel object has been changed to the specified value.
       *    Parameters:    The desired x, y, z coordinates for the Shovel object's translation. 
       */
      void setPosition(float x, float y, float z);

      /*
       *    Function prototype for Shovel object setScaling setter function.
       *    Precondition:  None.
       *    Postcondition: The scaling of the Shovel object has been changed to the specified values.
       *    Parameters:    The desired x, y, z values for the Shovel object's translation.  
       */
      void  setScale(float x, float y, float z);

      /*
       *    Function prototype for Shovel objecct setRotation setter function.
       *    Precondition:  None.
       *    Postcondition: The rotation of the Shovel object has been changed to the specified values.
       *    Parameters:    The desired rotation about the x, y, z axes respectively in degrees.  
       */
      void setRotation(float x, float y, float z);

      /*
       *    Function prototype for Shovel object getPosX getter function.
       *    Precondition:  None.
       *    Postcondition: The x-value of the object's translation has been returned to the caller.
       *    Return value:  The x-value of the object's position.   
       */
      float getPosX();

      /*
       *    Function prototype for Shovel object getPosY getter function.
       *    Precondition:  None.
       *    Postcondition: The y-value of the object's translation has been returned to the caller.
       *    Return value:  The y-value of the object's position. 
       */
      float getPosY();

      /*
       *    Function prototype for Shovel object getPosZ getter function.
       *    Precondition:  None.
       *    Postcondition: The z-value of the object's translation has been returned to the caller.
       *    Return value:  The z-value of the object's position. 
       */
      float getPosZ();

      /*
       *    Function prototype for Shovel object getScaleX getter function.
       *    Precondition:  None.
       *    Postcondition: The x-scaling of the object has been returned to the caller.
       *    Return value:  The x-scaling of the object. 
       */
      float getScaleX();

      /*
       *     Function prototype for Shovel object getScaleY getter function.
       *     Precondition:  None.
       *     Postcondition: The y-scaling of the object has been returned to the caller.
       *     Return value:  The y-scaling of the object. 
       */
      float getScaleY();

      /*
       *     Function prototype for Shovel object getScaleZ getter function.
       *     Precondition:  None.
       *     Postcondition: The z-scaling of the object has been returned to the caller.
       *     Return value:  The z-scaling of the object. 
       */
      float getScaleZ();

      /*
       *     Function prototype for Shovel object getRotX getter function.
       *     Precondition:  None.
       *     Postcondition: The object's rotation about the x-axis has been returned to the caller.
       *     Return value:  The object's rotation about the x-axis (in degrees). 
       */
      float getRotX();

      /*
       *     Function prototype for Shovel object getRotY getter function.
       *     Precondition:  None.
       *     Postcondition: The object's rotation about the y-axis has been returned to the caller.
       *     Return value:  The object's rotation about the y-axis (in degrees).  
       */
      float getRotY();

      /*
       *     Function prototype for Shovel object getRotZ getter function.
       *     Precondition:  None.
       *     Postcondition: The object's rotation about the z-axis has been returned to the caller.
       *     Return value:  The object's rotation about the z-axis.  
       */
      float getRotZ();
};