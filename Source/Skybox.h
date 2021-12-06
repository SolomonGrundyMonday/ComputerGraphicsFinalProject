/*
 *   Class declaration for Skybox class.
 *   Created by Jeff Colgan, November 2, 2021.
 *   CSCI-4229 Computer Graphics: Final Project. 
 */

#pragma once

#include "GameObject.h"

class Skybox : public GameObject
{
   // Private member variables for translation, scaling and texture.
   private:
      unsigned char texture;
      unsigned char moon;
      float posX;
      float posY;
      float posZ;
      float scaleX;
      float scaleY;
      float scaleZ;
      float rotX;
      float rotY;
      float rotZ;
      const float vertices[20][3] = { {-1.0, 1.0, 1.0}, {1.0, 1.0, 1.0}, {1.0, 1.0, -1.0}, {-1.0, 1.0, -1.0},
                                      {-1.0, -1.0, -1.0}, {-1.0, -1.0, 1.0}, {-1.0, 1.0, 1.0}, {-1.0, 1.0, -1.0},
                                      {1.0, -1.0, 1.0}, {1.0, -1.0, -1.0}, {1.0, 1.0, -1.0}, {1.0, 1.0, 1.0},
                                      {1.0, -1.0, -1.0}, {-1.0, -1.0, -1.0}, {-1.0, 1.0, -1.0}, {1.0, 1.0, -1.0},
                                      {-1.0, -1.0, 1.0}, {1.0, -1.0, 1.0}, {1.0, 1.0, 1.0}, {-1.0, 1.0, 1.0} };
      const float white[4] = { 1.0, 1.0, 1.0, 1.0 };
      const float black[4] = { 1.0, 1.0, 1.0, 1.0 };

   public:

      /*
       *   Function prototype for Skybox object default constructor.  DO NOT USE.
       *   Precondition:   None.
       *   Postcondition:  A Skybox object has been instantiated with the default translation, scaling and rotation.  
       */
      Skybox();

      /*
       *   Function prototype for Skybox object constructor.
       *   Precondition:   None.
       *   Postcondition:  A Skybox object has been instantiated with the specified translation, scaling and rotation.
       *   Parameters:     (x, y, z) coordinates for the object's translation, (x, y, z) values for the object's scaling,
       *                   and (x, y, z) values for the object's rotation about the corresponding axes.  
       */
      Skybox(float x, float y, float z, float dx, float dy, float dz, float rx, float ry, float rz);

      /*
       *   Function prototype for Skybox object Initialize implementation.
       *   Precondition:   An instance of a Skybox object has been instantiated, and a valid bmp filename has been
       *                   passed into the function.
       *   Postcondition:  The texture for the object has been loaded from a bmp file and applied to the object's texture field.
       *   Parameter:      The filename for a valid bmp file in 3 X 8 bit RGB format, with maximum size of 256 X 256 pixels.  
       */
      int Initialize(const char* filename);

      /*
       *   Function prototype for Skybox object Render function implementaiton. 
       *   Precondition:   An instance of a Skybox object has been instantiated and the textures have been applied to the object by
       *                   a call to initialize.  This function must be called from within the display function of an OpenGL application
       *                   or undefined behavior will result.  Additionally, only one Skybox object should be rendered per scene.
       *   Postcondition:  The object has been rendered in the OpenGL window. 
       */
      void Render();

      /*
       *   Function prototype for Skybox object resolveCollision function implementation.
       *   Precondition:   An instance of a skybox object has been instantiated, and the object has been rendered to the scene.
       *   Postcondition:  If a Camera object has collided with the skybox, the collision has been resolved, and the Camera's
       *                   position has been updated such that the camera is prevented from "clipping" through the skybox.  
       *   Parameter:      The active Camera object.  
       */
      void resolveCollision(Camera* camera);

      /*
       *   Function prototype for Skybox object setPosition setter function.
       *   Precondition:   None.
       *   Postcondition:  The object's translation has been changed to the specified values.
       *   Parameters:     The desired (x, y, z) coordinates for the object's new translation.  
       */
      void setPosition(float x, float y, float z);

      /*
       *   Function prototype for Skybox object setScale setter function.
       *   Precondition:   None.
       *   Postcondition:  The object's scaling has been changed to the specified values.
       *   Parameters:     The desired (x, y, z) values of the object's scaling.  
       */
      void setScale(float x, float y, float z);

      /*
       *   Function prototype for Skybox object setRotation setter function.
       *   Precondition:   None.
       *   Postcondition:  The object's rotation about each axis has been changed to the specified values.
       *   Parameters:     The desired rotation about the x, y, z axes respectively.  
       */
      void setRotation(float x, float y, float z);

      /*
       *   Function prototype for Skybox object getPosX getter function.
       *   Precondition:   None.
       *   Postcondition:  The x-value of the object's translation has been returned to the caller.
       *   Return value:   The x-value of the object's translation.  
       */
      float getPosX();

      /*
       *   Function prototype for Skybox object getPosY getter function.
       *   Precondition:   None.
       *   Postcondition:  The y-value of the object's translation has been returned to the caller.
       *   Return value:   The y-value of the object's translation. 
       */
      float getPosY();

      /*
       *   Funciton prototype for Skybox object getPosZ getter function.
       *   Precondition:   None.
       *   Postcondition:  The z-value of the object's translation has been returned to the caller.
       *   Return value:   The z-value of the object's translation.  
       */
      float getPosZ();

      /*
       *   Function prototype for Skybox object getScaleX getter function.
       *   Precondition:   None.
       *   Postcondition:  The x-value of the object's scaling has been returned to the caller.
       *   Return value:   The x-scaling of the object. 
       */
      float getScaleX();

      /*
       *   Function prototype for Skybox object getScaleY getter function.
       *   Precondition:   None.
       *   Postcondition:  The y-value of the object's scaling has been returned to the caller.
       *   Return value:   The y-scaling of the object.  
       */
      float getScaleY();

      /*
       *   Function prototype for Skybox object getScaleZ getter function.
       *   Precondition:   None.
       *   Postcondition:  The z-value of the object's scaling has been returned to the caller.
       *   Return value:   The z-scaling of the object.  
       */
      float getScaleZ();

      /*
       *   Function prototype for Skybox object getRotX getter function.
       *   Precondition:   None.
       *   Postcondition:  The x-rotation of the object has been returned to the caller.
       *   Return value:   The object's rotation about the x-axis (in degrees).  
       */
      float getRotX();

      /*
       *   Function prototype for Skybox object getRotY getter function.
       *   Precondition:   None.
       *   Postcondition:  The y-rotation of the object has been returned to the caller.
       *   Return value:   The object's rotation about the y-axis (in degrees).  
       */
      float getRotY();

      /*
       *   Function prototype for Skybox object getRotZ getter function.
       *   Precondition:   None.
       *   Postcondition:  The z-rotation of the object has been returned to the caller.
       *   Return value:   The object's rotation about the z-axis (in degrees).  
       */
      float getRotZ();
};
