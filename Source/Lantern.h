/*
 *   Class declaration for Lantern class.
 *
 *   Created by Jeff Colgan, November 5, 2021.
 *   Computer Graphics: Final Project. 
 */

#include "GameObject.h"

#pragma once

#define LANTERN_RAD 0.5
#define HANDLE_RAD 0.05

class Lantern : public GameObject
{
   private:
      unsigned char texture;
      unsigned char glass;
      float posX;
      float posY;
      float posZ;
      float scaleX;
      float scaleY;
      float scaleZ;
      float rotX;
      float rotY;
      float rotZ;
      float Ambient[4] = {0.0, 0.0, 0.0, 1.0};
      float Diffuse[4] = {1.0, 1.0, 1.0, 1.0};
      float Specular[4] = {0.0, 0.0, 0.0, 1.0};
      float white[4] = {1.0, 1.0, 1.0, 0.2};

   public:

      /*
       *   Function prototype for Lantern class default constructor.  DO NOT USE.
       *   Precondition:    None.
       *   Postcondition:   A Lantern object has been instantiated at the origin (0, 0, 0) with 1.0
       *                    scaling on all axes and 0.0 rotation about each axis.   
       */
      Lantern();

      /*
       *   Function prototype for Lantern class constructor.
       *   Precondition:    None.
       *   Postcondition:   A Lantern object has been instantiated with the specified translation, scaling
       *                    and rotation.
       *   Parameters:      (x, y, z) coordinates for the object's translation, (x, y, z) values for the object's
       *                    scaling and (x, y, z) values for the object's rotatino about the corresponding axis. 
       */
      Lantern(float x, float y, float z, float dx, float dy, float dz, float rx, float ry, float rz);

      /*
       *   Function prototype for Lantern class Initialize function implementation.
       *   Precondition:   An instance of a Lantern object has been instantiated and a valid bmp filename has been
       *                   passed to the function.
       *   Postcondition:  A texture has been loaded from a bmp file and applied to the texture field.
       *   Parameters:     The filename for a .bmp file in RGB 3 X 8 bit format with maximum dimensions of 512 X 512
       *                   pixels.  
       */
      int Initialize(const char* filename);

      /*
       *   Function prototype for Lantern class Render function implementation.
       *   Precondition:   An instance of a Lantern object has been instantiated and initialized.  This function must
       *                   be called from within the display function of an OpenGL application, or undefined behavior
       *                   will result.
       *   Postcondition:  The object has been rendered in the OpenGL window.  
       */
      void Render();

      /*
       *   Function prototype for Lantern class setPosition setter function.
       *   Precondition:   None.
       *   Postcondition:  The translation of the object has been set to the specified values.
       *   Parameters:     The desired (x, y, z) coordinates of the object's translation.   
       */
      void setPosition(float x, float y, float z);

      /*
       *   Function prototype for Lantern class setScale setter function.
       *   Precondition:   None.
       *   Postcondition:  The scaling of the object has been set to the specified values.
       *   Parameters:     The desired (x, y, z) scaling of the object. 
       */
      void setScale(float x, float y, float z);

      /*
       *   Function prototype for Lantern class setRotation setter function.
       *   Precondition:   None.
       *   Postcondition:  The rotation of the object has been set to the specified values.
       *   Parameters:     The desired rotation about the x, y, z axes respectively (in degrees).  
       */
      void setRotation(float x, float y, float z);

      /*
       *   Function prototype for Lantern class getPosX getter function.
       *   Precondition:   None.
       *   Postcondition:  The x-value of the object's translation has been returned to the caller.
       *   Return value:   The x-value of the object's translation. 
       */
      float getPosX();

      /*
       *   Function prototype for Lantern class getPosY getter function.
       *   Precondition:    None.  
       *   Postcondition:   The y-value of the object's translation has been returned to the caller.
       *   Return value:    The y-value of the object's translation.
       */
      float getPosY();

      /*
       *   Function prototype for Lantern class getPosZ getter function.
       *   Precondition:   None.
       *   Postcondition:  The z-value of the object's translation has been returned to the caller.
       *   Return value:   The z-value of the object's translation. 
       */
      float getPosZ();

      /*
       *   Function prototype for Lantern class getScaleX getter function.
       *   Precondition:   None.
       *   Postcondition:  The x-scaling of the object has been returned to the caller.
       *   Return value:   The object's x-scaling. 
       */
      float getScaleX();

      /*
       *   Function prototype for Lantern class getScaleY getter function.
       *   Precondition:   None.
       *   Postcondition:  The y-scaling of the object has been returned to the caller.
       *   Return value:   The object's y-scaling.  
       */
      float getScaleY();

      /*
       *   Function prototype for Lantern class getScaleZ getter function.
       *   Precondition:   None.
       *   Postcondition:  The z-scaling of the object has been returned to the caller.
       *   Return value:   The object's z-scaling. 
       */
      float getScaleZ();

      /*
       *   Function prototype for Lantern class getRotX getter function.
       *   Precondition:   None.
       *   Postcondition:  The object's rotation about the x-axis has been returned to the caller.
       *   Return value:   The object's rotation about the x-axis. 
       */
      float getRotX();

      /*
       *   Function prototype for Lantern class getRotY getter function.
       *   Precondition:   None.
       *   Postcondition:  The object's rotation about the y-axis has been returned to the caller.
       *   Return value:   The object's rotation about the y-axis. 
       */
      float getRotY();

      /*
       *   Function prototype for Lantern class getRotZ getter function.
       *   Precondition:    None. 
       *   Postcondition:   The object's rotation about the z-axis has been returned to the caller.
       *   Return value:    The object's rotation about the z-axis. 
       */
      float getRotZ();
};