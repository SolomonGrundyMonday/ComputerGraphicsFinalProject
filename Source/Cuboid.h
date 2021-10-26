/*
 *   Class declaration for Cuboid subclass of GameObject.
 *
 *   Created by Jeff Colgan, October 25, 2021,
 *   CSCI-4229 Final Project : Haunted Forest project.
 *
 *   This class creates and renders a basic cuboid object in OpenGL,
 *   applying lighting and texture to the object.
 *   Specifications:
 *   This class is to be used as follows.  The default constructor exists
 *   purely for C++ standards, it is intended that you use the 9-argument
 *   constructor to specify a translation, rotation and scaling to the object.
 *   Additionally, the Initialize() method should be called outside of the main
 *   programming loop, before control of the program is passed to GLUT - this
 *   method loads the texture, so attempting to render the object without first
 *   calling Initialize results in undefined behavior.  Calling Initialize from
 *   within the main GLUT loop will result in severe performance loss.
 */

#pragma once
#include "GameObject.h"

class Cuboid : public GameObject
{
   // private member variables for texture, position, rotation and scaling.
   private:
      unsigned char texture;
	  float xPos;
	  float yPos;
	  float zPos;
	  float xScale;
	  float yScale;
	  float zScale;
	  float xRot;
	  float yRot;
	  float zRot;

   public:
      /*
       *   Function prototype for Cuboid object default constructor.
       *   Precondition:  None.
       *   Postcondition: A Cuboid object has been created at the origin (0, 0, 0), with 1.0
       *                  scaling along each axis and 0.0 rotation about each axis. 
       */
      Cuboid();

      /*
       *   Function prototype for Cuboid object constructor.
       *   Precondition:  None.
       *   Postcondition: A Cuboid object has been created with the specified translation, scaling and
       *                  rotation. 
       *   Parameters:    (x, y, z) coordinates for the objects desired translation, (x, y, z) values for the objects
       *                  desired scaling, (x, y, z) values for the objects desired rotation. 
       */
      Cuboid(float x, float y, float z, float scaleX, float scaleY, float scaleZ, float rotX, float rotY, float rotZ);

      /*
       *    Function prototype for Cuboid object Initialize function.
       *    Precondition:  An instance of a cuboid object has been instantiated, and a valid RGB bitmap filename
       *                   has been provided as the argument.
       *    Postcondition: A texture has been loaded from a .bmp file and applied to the texture field of the
       *                   object.
       *    Parameters:    The filename for a valid RGB 3 X 8 bit bitmap file of maximum size 512 X 512 pixels. 
       */
      int Initialize(const char* filename);

      /*
       *    Function prototype for Cuboid object Render function.
       *    Precondition:  An instance of a Cuboid object has been instantiated and the Initialize function has been
       *                   called on a valid bitmap file.  This function must be called from within the display function
       *                   of an OpenGL application, or undefined behavior will result.
       *    Postcondition: The object has been rendered in the OpenGL window.  
       */
      void Render();

      /*
       *    Function prototype for Cuboid object getPosX function.
       *    Precondition:  None.
       *    Postcondition: The x-translation value has been returned to the caller.  
       *    Return value:  The x-value of the Cuboid's translation.
       */
      float getPosX();

      /*
       *     Function prototype for Cuboid object getPosY function.
       *     Precondition:  None.
       *     Postcondition: The y-translation value has been returned to the caller. 
       *     Return value:  The y-value of the Cuboid's translation. 
       */
      float getPosY();

      /*
       *     Function prototype for Cuboid object getPosZ function.
       *     Precondition:  None.
       *     Postcondition: The z-translation value has been returned to the caller. 
       *     Return value:  The z-value of the Cuboid's translation. 
       */
      float getPosZ();

      /*
       *     Function prototype for Cuboid object getScaleX function.
       *     Precondition:  None.
       *     Postcondition: The x-scaling value has been returned to the caller. 
       *     Return value:  The x-value of the Cuboid's scaling. 
       */
      float getScaleX();

      /*
       *     Function prototype for Cuboid object getScaleY function.
       *     Precondition:  None.
       *     Postcondition: The y-scaling value has been returned to the caller.  
       *     Return value:  The y-value of the Cuboid's scaling. 
       */
      float getScaleY();

      /*
       *     Funciton prototype for Cuboid object getScaleZ function.
       *     Precondition:  None.
       *     Postcondition: The z-scaling value has been returned to the caller.  
       *     Return value:  The z-value of the Cuboid's scaling. 
       */
      float getScaleZ();

      /*
       *     Function prototype for Cuboid object getRotX function.
       *     Precondition:  None.
       *     Postcondition: The x-rotation value has been returned to the caller.
       *     Return value:  The Cuboid's rotation about the x-axis (degrees).  
       */
      float getRotX();

      /*
       *     Function prototype for Cuboid object getRotY function.
       *     Precondition:  None.
       *     Postcondition: The y-rotation value has been returned to the caller.
       *     Return value:  The Cuboid's rotation about the y-axis (degrees).  
       */
      float getRotY();

      /*
       *     Funciton prototype for Cuboid object getRotZ function.
       *     Precondition:  None.
       *     Postcondition: The z-rotation value has been returned to the caller. 
       *     Return value:  The Cuboid's rotation about the z-axis (dgrees).
       */
      float getRotZ();

      /*
       *     Function prototype for Cuboid object setPosition function.
       *     Precondition:  None.
       *     Postcondition: The objects translation has been changed to the specified x, y, z values.
       *     Parameters:    The desired translation of the object.  If these are invalid coordinates,
       *                    undefined behavior will result. 
       */
      void setPosition(float x, float y, float z);

      /*
       *     Function prototype for Cuboid object setScale function.
       *     Precondition:  None.
       *     Postcondition: The objects scaling has been changed to the specified x, y, z values.
       *     Parameters:    The desired scaling of the object.   If these values are < 0, undefined
       *                    behavior will result.
       */
      void setScale(float x, float y, float z);

      /*
       *     Function prototype for Cuboid object setRotation function.
       *     Precondition:  None.
       *     Postcondition: The objects rotation has been changed to the specified x, y, z values.
       *     Parameters:    The desired rotation of the object about each axis in degrees.  
       */
      void setRotation(float x, float y, float z);
};