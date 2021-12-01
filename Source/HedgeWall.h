/*
 *   HedgeWall class declaration.
 *   Created by Jeff Colgan, November 25, 2021.
 *   Computer Graphics Final Project. 
 */

#pragma once

#include "GameObject.h"

class HedgeWall : public GameObject
{
   // Private member variables for position, rotation, scaling and textures.
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

      /*
       *   Function prototype for CaveWall getSide helper function.
       *   Precondition:   A CaveWall object has been instantiated and rendered to the scene.
       *   Postcondition:  The side of the CaveWall hitbox that has been collided by the Camera has been returned
       *                   to the caller.
       *   Parameter:      The active Camera object.
       *   Return value:   The side of the CaveWall hitbox with which the Camera object is colliding. 
       */
      wall getSide(Camera* camera);

   public:

      /*
       *   Function prototype for CaveWall class default constructor. DO NOT USE.
       *   Precondition:   None.
       *   Postcondition:  A CaveWall object has been instantiated with the default translation, scaling and rotation. 
       */
      HedgeWall();

      /*
       *   Function prototype for CaveWall class constructor.
       *   Precondition:   None.
       *   Postcondition:  A CaveWall object has been instantiated with the specified translation, scaling and rotation.
       *   Parameters:     (x, y, z) coordinates for the object's translation, (x, y, z) values for the object's scaling
       *                   and (x, y, z) values for the object's rotation about the corresponding axis.
       */
      HedgeWall(float x, float y, float z, float dx, float dy, float dz, float rx, float ry, float rz);

      /*
       *   Function prototype for CaveWall class Initialize function implementation.
       *   Precondition:   A CaveWall object has been instantiated and a valid bmp filename has been passed into this function.
       *   Postcondition:  A texture has been loaded from a bmp file and applied to the texture field.
       *   Parameters:     The filename for a .bmp file in RGB 3 X 8 bit format with maximum size of 512 X 512 pixels.   
       */
      int Initialize(const char* filename);

      /*
       *   Function prototype for CaveWall class Render function implementation.
       *   Precondition:   A CaveWall object has been instantiated and initialized.  This function must be called from within the
       *                   display function of an OpenGL application, or undefined behavior will result.
       *   Postcondition:  The object has been rendered to the OpenGL window.   
       */
      void Render();

      /*
       *   Function prototype for CaveWall class detectCollision function implementation.
       *   Precondition:   A CaveWall object has been instantiated and rendered to the scene.
       *   Postcondition:  The function returns true if the Camera is colliding with the CaveWall hitbox, false otherwise.
       *   Parameter:      The active Camera object.
       *   Return value:   True if a collision has occured, false otherwise. 
       */
      bool detectCollision(Camera* camera);

      /*
       *   Function prototype for CaveWall class resolveCollision function implementation.
       *   Precondition:   An instance of a CaveWall object has been instantiated and rendered to the scene.
       *   Postcondition:  The collision has been resolved, and the Camera eye position has been updated to appropriate values.
       *   Parameter:      The active Camera object. 
       */
      void resolveCollision(Camera* camera);

      /*
       *   Function prototype for CaveWall class setPosition function.
       *   Precondition:   None.
       *   Postcondition:  The translation of the object has been set to the specified values.
       *   Parameters:     The desired (x, y, z) coordinates of the object's translation. 
       */
      void setPosition(float x, float y, float z);

      /*
       *   Function prototype for CaveWall class setScale function.
       *   Precondition:   None.
       *   Postcondition:  The scaling of the object has been set to the specified values.
       *   Parameters:     The desired (x, y, z) scaling of the object. 
       */
      void setScale(float x, float y, float z);

      /*
       *   Function prototype for CaveWall class setRotation function.
       *   Precondition:   None.
       *   Postcondition:  The rotation of the object has been set to the specified values.
       *   Parameters:     The desired rotation about the x, y, z axes respectively (in degrees). 
       */
      void setRotation(float x, float y, float z);

      /*
       *   Function prototype for CaveWall class getPosX getter function.
       *   Precondition:   None.
       *   Postcondition:  The x-value of the object's translation has been returned to the caller.
       *   Return value:   The x-value of the object's translation. 
       */
      float getPosX();

      /*
       *   Function prototype for CaveWall class getPosY getter function.
       *   Precondition:   None.
       *   Postcondition:  The y-value of the object's translation has been returned to the caller.
       *   Return value:   The y-value of the object's translation. 
       */
      float getPosY();

      /*
       *    Function prototype for CaveWall class getPosZ getter function.
       *    Precondition:   None.
       *    Postcondition:  The z-value of the object's translation has been returned to the caller.
       *    Return value:   The z-value of the object's translation. 
       */
      float getPosZ();

      /*
       *    Function prototype for CaveWall class getScaleX getter function.
       *    Precondition:   None.
       *    Postcondition:  The x-scaling of the object has been returned to the caller.
       *    Return value:   The object's x-scaling.  
       */
      float getScaleX();

      /*
       *    Function prototype for CaveWall class getScaleY getter function.
       *    Precondition:   None.
       *    Postcondition:  The y-scaling of the object has been returned to the caller.
       *    Return value:   The object's y-scaling. 
       */
      float getScaleY();

      /*
       *    Function prototype for CaveWall class getScaleZ getter function.
       *    Precondition:   None.
       *    Postcondition:  The z-scaling of the object has been returned to the caller.
       *    Return value:   The object's z-scaling. 
       */
      float getScaleZ();

      /*
       *    Function prototype for CaveWall class getRotX getter function.
       *    Precondition:   None.
       *    Postcondition:  The object's x-rotation has been returned to the caller.
       *    Return value:   The object's rotation about the x-axis (in degrees).  
       */
      float getRotX();

      /*
       *    Function prototype for CaveWall class getRotY getter function.
       *    Precondition:   None.
       *    Postocndition:  The object's y-rotation has been returned to the caller.
       *    Return value:   The object's rotation about the y-axis (in degrees). 
       */
      float getRotY();

      /*
       *    Function prototype for CaveWall class getRotZ getter function.
       *    Precondition:   None.
       *    Postcondition:  The object's z-rotation has been returned to the caller.
       *    Return value:   The object's rotation about the z-axis (in degrees).  
       */
      float getRotZ();
};