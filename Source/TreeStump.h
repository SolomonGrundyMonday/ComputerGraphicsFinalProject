/*
 *  Class declaration for TreeStump class.
 *  Created by Jeff Colgan, November 27, 2021.
 *  CSCI-4229 Computer Graphics : Final Project. 
 */

#include "GameObject.h"

#pragma once

class TreeStump : public GameObject
{
   // Private member variables for translation, rotation, scaling and texture.
   private:
      unsigned char texture;
      unsigned char surface;
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
       *   Function prototype for TreeStump class getSide helper function.
       *   Precondition:  A TreeStump object has been instantiated and rendered to the scene, and a collision with the
       *                  active Camera object has been detected.
       *   Postcondition: The side of the object's hitbox that is experiencing the collision has been returned to the caller.
       *   Parameter:     The active Camera object.
       *   Return value:  The side of the object's hitbox with which the Camera is colliding. 
       */
      wall getSide(Camera* camera);

   public:

      /*
       *   Function prototype for TreeStump class default constructor.  DO NOT USE.
       *   Precondition:  None.
       *   Postcondition: A TreeStump object has been instantiated with the default translation at the origin, default scaling of
       *                  1.0 on all axes, and default rotation of 0.0 about each axis. 
       */
      TreeStump();

      /*
       *   Function prototype for TreeStump class constructor.
       *   Precondition:  None.
       *   Postcondition: A TreeStump object has been instantiated with the desired translation, rotation and scaling.
       *   Parameters:    (x, y, z) coordinates for the desired translation, x, y and z values for the desired scaling, and x, y and z
       *                  values for the desired rotation about each axis.  
       */
      TreeStump(float x, float y, float z, float dx, float dy, float dz, float rx, float ry, float rz);

      /*
       *   Function prototype for TreeStump class Initialize function implementation.
       *   Precondition:  A TreeStump object has been instantiated and a valid bmp filename has been passed into this function.
       *   Postcondition: A texure has been loaded from a bmp file and applied to the texture field.
       *   Paramter:      The filename for a .bmp file in RGB 3 X 8 bit format with maximum dimensions of 512 X 512 pixels.  
       */
      int Initialize(const char* filename);

      /*
       *   Function prototype for TreeStump class Render function implementation.
       *   Precondition:  A TreeStump object has been instantiated and initialized.  This function must be called from within the display
       *                  function of an OpenGL application or undefined behavior will result.  
       *   Postcondition: The object has been rendered to the OpenGL window.  
       */
      void Render();

      /*
       *   Function prototype for TreeStump class detectCollision function.
       *   Precondition:  A TreeStump object has been instantiated and rendered to the scene.
       *   Postcondition: The function returns true if the Camera is colliding with the object's hitbox, false otherwise.
       *   Parameter:     The active Camera object.
       *   Return value:  True if a collision is occuring, false otherwise. 
       */
      bool detectCollision(Camera* camera);

      /*
       *   Function prototype for TreeStump resolveCollision function implementation.
       *   Precondition:  An instance of a TreeStump object has been instantiated and rendered to the scene, and a collision with the active
       *                  active Camera is occuring.   
       *   Postcondition: If a Camera has collided with the object, the collision has been resolved, and the Camera eye position has been
       *                  updated accordingly.
       *   Parameter:     The active Camera object. 
       */
      void resolveCollision(Camera* camera);

      /*
       *   Function prototype for TreeStump class setPosition setter funciton.
       *   Precondition:  None.
       *   Postcondition: The translation of the object has been updated to the desired coordinates.
       *   Paramters:     The desired coordinates of the objet's translation. 
       */
      void setPosition(float x, float y, float z);

      /*
       *   Function prototype for TreeStump class setScale setter function.
       *   Precondition:  None.
       *   Postcondition: The scaling of the object has been set to the desired values.
       *   Parameters:    The desired x, y and z values for the object's scaling.  
       */
      void setScale(float x, float y, float z);

      /*
       *   Function prototype for TreeStump class setRotation setter function.
       *   Precondition:  None.
       *   Postcondition: The rotation about each axis has been set to the desired values.
       *   Parameters:    The desired rotation about the x, y and z axes (in degrees). 
       */
      void setRotation(float x, float y, float z);

      /*
       *   Function prototype for TreeStump class getPosX getter function.
       *   Precondition:  None.
       *   Postcondition: The x-value of the object's translation has been returned to the caller.
       *   Return value:  The x-value of the object's translation. 
       */
      float getPosX();

      /*
       *   Function prototype for TreeStump class getPosY getter function.
       *   Precondition:  None.
       *   Postcondition: The y-value of the object's translation has been returned to the caller.
       *   Return value:  The y-value of the object's translation. 
       */
      float getPosY();

      /*
       *   Function prototype for TreeStump class getPosZ getter function.
       *   Precondition:  None.
       *   Postcondition: The z-value of the object's translation has been returned to the caller.
       *   Return value:  The z-value of the object's translation. 
       */
      float getPosZ();

      /*
       *   Function prototype for TreeStump getScaleX getter function.
       *   Precondition:  None.
       *   Postcondition: The x-value of the object's scaling has been returned to the caller.
       *   Return value:  The x-value of the object's scaling. 
       */
      float getScaleX();

      /*
       *   Function prototype for TreeStump class getScaleY getter function.
       *   Precondition:  None.
       *   Postcondition: The y-value of the object's scaling has been returned to the caller.
       *   Return value:  The y-value of the object's scaling.  
       */
      float getScaleY();

      /*
       *   Function prototype for TreeStump class getScaleZ getter function.
       *   Precondition:  None.
       *   Postcondition: The z-value of the object's scaling has been returned to the caller.
       *   Return value:  The z-value of the object's scaling. 
       */
      float getScaleZ();

      /*
       *   Function prototype for TreeStump class getRotX getter function.
       *   Precondition:  None.
       *   Postcondition: The object's rotation about the x-axis has been returned to the caller.
       *   Return value:  The object's rotation about the x-axis.
       */
      float getRotX();

      /*
       *   Function prototype for TreeStump class getRotY getter function.
       *   Precondition:  None.
       *   Postcondition: The object's rotation about the y-axis has been returned to the caller.
       *   Return value:  The object's rotation about the y-axis. 
       */
      float getRotY();

      /*
       *   Function prototype for TreeStump class getRotZ getter function.
       *   Precondition:  None.
       *   Postcondition: The object's rotation about the z-axis has been returned to the caller.
       *   Return value:  The object's rotation about the z-axis. 
       */
      float getRotZ();
};
