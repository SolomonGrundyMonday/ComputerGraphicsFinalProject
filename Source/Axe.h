/*
 *   Class declaration for Axe class.
 *   Created by Jeff Colgan, October 27, 2021,
 *   CSCI-4229 Computer Graphics : Final Project. 
 */

#pragma once

#include "GameObject.h"

#define LENGTH 1.0
#define HEAD_WID 0.05
#define HEAD_HEIGHT 0.2
#define HEAD_LENGTH 0.3
#define RAD 0.05

class Axe : public GameObject
{
   // Private member variables for translation, scaling, rotation and textures.
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

   public:

      /*
       *   Function prototype for Axe object default constructor.  DO NOT USE.
       *   Precondition:  None.
       *   Postcondition: A Tree object has been instantiated at the origint (0, 0, 0) with 1.0 scaling
       *                  on all axes and 0.0 rotation about each axis.  
       */
      Axe();

      /*
       *    Function prototype for Axe object constructor.
       *    Precondition:  None.
       *    Postcondition: An axe object has been instantiated with the specified translation, scaling and
       *                   rotation.
       *    Parameters:    (x, y, z) coordinates for the object's translation, (x, y, z) values for the object's
       *                   scaling, and (x, y, z) values for the object's rotation about the corresponding axis. 
       */
      Axe(float x, float y, float z, float dx, float dy, float dz, float rx, float ry, float rz);

      /*
       *    Function prototype for Axe object implementation of Initialize function.
       *    Precondition:  An instance of an Axe object has been instantiated, and a valid bmp filename has been
       *                   passed to the function.
       *    Postcondition: A texture has been loaded from the .bmp file and applied to the texture field.
       *    Parameters:    The filename for a valid bitmap file in 3 X 8 bit format with maximum dimensions of
       *                   512 X 512 pixels. 
       */
      int Initialize(const char* filename);

      /*
       *    Function prototype for Axe object implementation of Render function.
       *    Precondition:  An Axe object has been instantiated, and initialized through the Initialize function.
       *                   This function must be called from within a display function of an OpenGL application,
       *                   otherwise undefined behavior will result.
       *    Postcondition: The object has been rendered in the OpenGL window. 
       */
      void Render();

      /*
       *    Function prototype for Axe object implementation of resolveCollision function.
       *    Precondition:  An Axe object has been instantiated, and the object has been rendered to the scene.
       *    Postcondition: If a Camera object has collided with the Axe object, the collision has been resolved, and
       *                   the Camera's position has been updated such that the Camera is prevented from "clipping" through
       *                   the object.
       *    Parameter:     The active Camera object.  
       */
      void resolveCollision(Camera* camera);
      
      /*
       *    Function prototype for Axe object setPosition setter function.
       *    Precondition:  None.
       *    Postcondition: The translation of the object has been set to the specified x, y, z values.
       *    Parameters:    The desired x, y, z values for the object's new translation. 
       */
      void setPosition(float x, float y, float z);

      /*
       *    Function prototype for Axe object setScale setter function.
       *    Precondition:  None.
       *    Postcondition: The scaling of the Axe object has been changed to the specified values.
       *    Parameters:    The desired x, y, z values for the object's new scaling.  
       */
      void setScale(float x, float y, float z);

      /*
       *    Function prototype for Axe object setRotation setter function.
       *    Precondition:  None.
       *    Postcondition: The rotation of the Axe object about each axis has been changed to the specified values.
       *    Parameters:    The desired rotation about the x, y, and z axes respectively. 
       */
      void setRotation(float x, float y, float z);

      /*
       *    Function prototype for Axe object getPosX getter function.
       *    Precondition:  None.
       *    Postcondition: The x-value of the object's translation has been returned to the caller.
       *    Return value:  The x-value of the object's translation. 
       */
      float getPosX();

      /*
       *     Function prototype for Axe object getPosY getter function.
       *     Precondition:  None.
       *     Postcondition: The y-value of the object's translation has been returned to the caller.
       *     Return value:  The y-value of the object's translation.  
       */
      float getPosY();

      /*
       *     Function prototype for Axe object getPosZ getter function.
       *     Precondition:  None.
       *     Postcondition: The z-value of the object's translation has been returned to the caller.
       *     Return value:  The z-value of the object's translation. 
       */
      float getPosZ();

      /*
       *     Function prototype for Axe object getScaleX getter function.
       *     Precondition:  None.
       *     Postcondition: The x-value of the object's scaling has been returned to the caller.
       *     Return value:  The x-scaling of the object. 
       */
      float getScaleX();

      /*
       *     Function prototype for Axe object getScaleY getter function.
       *     Precondition:  None.
       *     Postcondition: The y-value of the object's scaling has been returned to the caller.
       *     Return value:  The y-scaling of the object. 
       */
      float getScaleY();

      /*
       *     Function prototype for Axe object getScaleZ getter function.
       *     Precondition:  None.
       *     Postcondition: The z-value of the object's scaling has been returned to the caller.
       *     Return value:  The z-scaling of the object. 
       */
      float getScaleZ();

      /*
       *     Function prototype for Axe object getRotX getter function.
       *     Precondition:  None.
       *     Postcondition: The x-value of the object's scaling has been returned to the caller.
       *     Return value:  The object's rotation about the x-axis (in degrees). 
       */
      float getRotX();

      /*
       *     Function prototype for Axe object getRotY getter function.
       *     Precondition:  None.
       *     Postcondition: The y-value of the object's rotation has been returned to the caller.
       *     Return value:  The object's rotation about the y-axis (in degrees). 
       */
      float getRotY();

      /*
       *     Function prototype for Axe object getRotZ getter function.
       *     Precondition:  None.
       *     Postcondition: The z-value for the object's rotation has been returned to the caller.
       *     Return value:  The object's rotation about the z-axis (in degrees).  
       */
      float getRotZ();
};