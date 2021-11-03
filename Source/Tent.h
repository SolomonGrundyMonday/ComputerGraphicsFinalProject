/*
 *    Tent Class declaration.
 *    Created by Jeff Colgan, November 1, 2021,
 *    CSCI-4229 Computer Graphics : Final Project.  
 */

#pragma once

#include "GameObject.h"

#define TENT_HEIGHT 1.0
#define TENT_WIDTH 1.0
#define TENT_LENGTH 1.0

class Tent : public GameObject
{
   // Private member variables for translation, rotation, scaling and texture.
   private:
      unsigned char texture;
      float posX;
      float posY;
      float posZ;
      float scaleX;
      float scaleY;
      float scaleZ;
      float rotX;
      float rotY;
      float rotZ;

   public:

      /*
       *    Function prototype for Tent object default constructor.  DO NOT USE.
       *    Precondition:   None.
       *    Postcondition:  A Tent object has been instantiated with the default translation, scaling and rotation.  
       */
      Tent();

      /*
       *    Function prototype for Tent object constructor.
       *    Precondition:   None.
       *    Postcondition:  A Tent object has been instantiated with the specified translation, scaling
       *                    and rotation. 
       *    Parameters:     (x, y, z) coordinates for the object's translation, (x, y, z) values for the object's
       *                    scaling, and (x, y, z) values for the object's rotation about the corresponding axis.  
       */
      Tent(float x, float y, float z, float dx, float dy, float dz, float rx, float ry, float rz);

      /*
       *    Function prototype for Tent object Initialize function implementation.
       *    Precondition:   An instance of a Tent object has been instantiated, and a valid bmp filename has been passed
       *                    into the function.
       *    Postcondition:  The texture for the object has been loaded from a bmp file and applied to the texture field.
       *    Parameters:     The filename for a valid bmp file in 3 X 8 bit RGB format, with maximum size of 512 X 512 pixels. 
       */
      int Initialize(const char* filename);

      /*
       *    Function prototype for Tent object Render function implementation.
       *    Precondition:   An instance of a Tent object has been instantiated and the textures have been loaded by a call to
       *                    Initialize.  This function must be called from the display function of an OpenGL application,
       *                    or undefined behavior will result.
       *    Postcondition:  The object has been rendered in the OpenGL window.  
       */
      void Render();

      /*
       *    Function prototype for Tent object setPosition setter function.
       *    Precondition:   None.
       *    Postcondition:  The object's translation has been changed to the specified values.
       *    Parameters:     The desired (x, y, z) coordinates for the object's new translation.  
       */
      void setPosition(float x, float y, float z);

      /*
       *    Function prototype for Tent object setScale setter function.
       *    Precondition:   None.
       *    Postcondition:  The object's scaling has been changed to the specified values.
       *    Parameters:     The desired (x, y, z) values of the object's scaling.   
       */
      void setScale(float x, float y, float z);

      /*
       *    Function prototype for Tent object setRotation setter function.
       *    Precondition:   None.
       *    Postcondition:  The object's rotation about each axis has been changed to the specified values.
       *    Parameters:     The desired rotation about the x, y, z axes respectively.  
       */
      void setRotation(float x, float y, float z);

      /*
       *    Function prototype for Tent object getPosX getter function.
       *    Precondition:   None.
       *    Postcondition:  The x-value of the object's translation has been returned to the caller.
       *    Return value:   The x-value of the object's translation. 
       */
      float getPosX();

      /*
       *    Function prototype for Tent object getPosY getter function.
       *    Precondition:   None.
       *    Postcondition:  The y-value of the object's translation has been returned to the caller.
       *    Return value:   The y-value of the object's translation. 
       */
      float getPosY();

      /*
       *    Function prototype for Tent object getPosZ getter function.
       *    Precondition:   None.
       *    Postcondition:  The z-value of the object's translation has been returned to the caller.
       *    Return value:   The z-value of the object's translation. 
       */
      float getPosZ();

      /*
       *    Function prototype for Tent object getScaleX getter function.
       *    Precondition:   None.
       *    Postcondition:  The x-value of the object's scaling has been returned to the caller.
       *    Return value:   The x-scaling of the object. 
       */
      float getScaleX();

      /*
       *    Function prototype for Tent object getScaleY getter function.
       *    Precondition:   None.
       *    Postcondition:  The y-value of the object's scaling has been returned to the caller.
       *    Return value:   The y-scaling of the object. 
       */
      float getScaleY();

      /*
       *    Function prototype for Tent object getScaleZ getter function.
       *    Precondition:   None.
       *    Postcondition:  The z-value of the object's scaling has been returned to the caller.
       *    Return value:   The z-scaling of the object.   
       */
      float getScaleZ();

      /*
       *    Function prototype for Tent object getRotX getter function.
       *    Precondition:   None.
       *    Postcondition:  The x-value of the object's rotation has been returned to the caller.
       *    Return value:   The object's rotation about the x-axis (in degrees).  
       */
      float getRotX();

      /*
       *    Function prototype for Tent object getRotY getter function.
       *    Precondition:   None.
       *    Postcondition:  The y-value of the object's rotation has been returned to the caller.
       *    Return value:   The object's rotation about the y-axis (in degrees). 
       */
      float getRotY();

      /*
       *    Function prototype for Tent object getRotZ getter function.
       *    Precondition:   None.
       *    Postcondition:  The z-value of the object's rotation has been returned to the caller.
       *    Return value:   The object's rotation about the z-axis (in degrees).  
       */
      float getRotZ();
};