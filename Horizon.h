/*
 *   Class declaration for Horizon class.
 *   Created by Jeff Colgan, November 25, 2021.
 *   CSCI-4229 Computer Graphics : Final Project. 
 */

#pragma once

#include "GameObject.h"

class Horizon : public GameObject
{
   // Private member variables for translation, scaling and texture.
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
      const float black[4] = { 1.0, 1.0, 1.0, 1.0 };

      /*
       *   Function prototype for Horizon object getSide helper function.
       *   Precondition:  The object has been instantiated and rendered to the scene.
       *   Postcondition: The wall with which the Camera object is colliding is returned to the caller.
       *   Parameter:     The active Camera object.
       *   Return value:  The side of the object's hitbox that is experiencing a collision with the Camera.   
       */
      wall getSide(Camera* camera);

   public:

      /*
       *   Function prototype for Horizon object default constructor.  DO NOT USE.
       *   Precondition:  None.
       *   Postcondition: A Horizon object has been instantiated with the default translation, rotation and scaling.
       */
      Horizon();

      /*
       *   Function prototype for Horizon object constructor.
       *   Precondition:  None.
       *   Postcondition: A Horizon object has been instantiated with the specified translation, scaling and rotation.
       *   Parameters:    (x, y, z) coordinates for the object's translation, (x, y, z) values for the object's scaling, 
       *                  and (x, y, z) values for the object's rotation about the corresponding axis. 
       */
      Horizon(float x, float y, float z, float dx, float dy, float dz, float rx, float ry, float rz);

      /*
       *   Function prototype for Horizon object Initialize implementation.
       *   Precondition:  An instance of a Horizon object has been instantiated, and a valid bmp filename has been passed
       *                  into the function.
       *   Postcondition: The texture for the object has been loaded from a bmp file and applied to the texture field.
       *   Parameter:     The filename for a valid bmp file in 3 X 8 bit RGB format, with maximum size of 512 X 512 pixels. 
       */
      int Initialize(const char* filename);

      /*
       *   Function prototype for Horizon object Render function implementation.
       *   Precondition:  An instance of a Horizon object has been instantiated and the textures have been loaded by a call
       *                  to initialize.  This function must be called from within the display function of an OpenGL application,
       *                  or undefined behavior will result.       
       *   Postcondition: The object has been rendered in the OpenGL window. 
       */
      void Render();

      /*
       *   Function prototype for Horizon object detectColision function.
       *   Precondition:   The Horizon object has been instantiated and rendered to the scene.
       *   Postcondition:  The function returns true if a collision has occured with the active Camera object, false otherwise.
       *   Paramter:       The active Camera object.  
       *   Return value:   True if the active camera is colliding with the object, false otherwise. 
       */
      bool detectCollision(Camera* camera);

      /*
       *   Function prototype for Horizon object resolveCollision function implementation.
       *   Precondition:   The Horizon object has been instantiated and rendered to the scene.
       *   Postcondition:  The function has resolved the collision, preventing the Camera object from "clipping through" the object.
       *   Parameter:      The active Camera object.  
       */
      void resolveCollision(Camera* camera);

      /*
       *   Function prototype for Horizon object setPosition setter function.
       *   Precondition:  None.
       *   Postcondition: The object's translation has been changed to the specified values.
       *   Parameters:    The desired (x, y, z) coordinates for the object's new translation. 
       */
      void setPosition(float x, float y, float z);

      /*
       *   Function prototype for Horizon object setScale setter function.
       *   Precondition:  None.
       *   Postcondition: The object's scaling has been changed to the specified values.
       *   Parameters:    The desired (x, y, z) values of the object's new scaling. 
       */
      void setScale(float x, float y, float z);

      /*
       *   Function prototype for Horizon object setRotation setter function.
       *   Precondition:  None.
       *   Postcondition: The object's roatation about each axis has been changed to the specified values.
       *   Parameters:    The desired rotation about the x, y, z axes respectively (in degrees). 
       */
      void setRotation(float x, float y, float z);

     /*
      *    Function prototype for Horizon object getPosX getter function.
      *    Precondition:  None.
      *    Postcondition: The x-value of the object's translation has been returned to the caller.
      *    Return value:  The x-value of the object's translation.  
      */
     float getPosX();

     /*
      *    Function prototype for Horizon object getPosY getter function.
      *    Precondition:  None.
      *    Postcondition: The y-value of the object's translation has been returned to the caller.
      *    Return value:  The y-value of the object's translation. 
      */
     float getPosY();

     /*
      *    Function prototype for Horizon object getPosZ getter function.
      *    Precondition:  None.
      *    Postcondition: The z-value of the object's translation has been returned to the caller.
      *    Return value:  The z-value of the object's translation. 
      */
     float getPosZ();

     /*
      *    Function prototype for Horizon object getScaleX getter function.
      *    Precondition:  None.
      *    Postcondition: The x-value of the object's translation has been returned to the caller.
      *    Return value:  The x-value of the object's scaling. 
      */
     float getScaleX();

     /*
      *    Function prototype for Horizon object getScaleY getter function.
      *    Precondition:  None.
      *    Postcondition: The y-value of the object's scaling has been returned to the caller.
      *    Return value:  The y-value of the object's scaling.  
      */
     float getScaleY();

     /*
      *    Function prototype for Horizon object getScaleZ getter function.
      *    Precondition:  None.
      *    Postcondition: The z-value of the object's scaling has been returned to the caller.
      *    Return value:  The z-value of the object's scaling.  
      */
     float getScaleZ();

     /*
      *    Function prototype for Horizon object getRotX getter function.
      *    Precondition:  None.
      *    Postcondition: The x-rotation of the object has been returned to the caller.
      *    Return value:  The object's rotation about the x-axis (in degrees). 
      */
     float getRotX();

     /*
      *    Function prototype for Horizon object getRotY getter function.
      *    Precondition:  None.
      *    Postcondition: The y-rotation of the object has been returned to the caller.
      *    Return value:  The object's rotation about the y-axis (in degrees).  
      */
     float getRotY();

     /*
      *    Function prototype for Horizon object getRotZ getter function.
      *    Precondition:  None.
      *    Postcondition: The z-rotation of the object has been returned to the caller.
      *    Return value:  The object's roatation about the z-axis (in degrees).  
      */
     float getRotZ();
};