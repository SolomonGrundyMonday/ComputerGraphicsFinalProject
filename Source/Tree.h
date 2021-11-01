/*
 *  Tree class declaration.
 *
 *  Created by Jeff Colgan, October 25, 2021,
 *  CSCI-4229 Computer Graphics: Final Project. 
 */

#pragma once
#include "GameObject.h"

#define SHRINK_FACTOR 0.7
#define LEAF_SIZE 0.3
#define BRANCH_NUM 3
#define BRANCH_RATIO 0.65

class Tree : public GameObject
{
   // Private member variables for translation, rotation, scaling and texture.
   private:
      unsigned char texture;
      unsigned char leafTex;
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
       *  Function declaration for private helper function branch.
       *  Based on the code from the in-class discussion of fractal trees. 
       */
      int branch(float l, float r);

      /*
       *  Function declaration for private helper function leaf. 
       *  Based on the code from the in-class discussion of fractal trees.
       */
      int leaf();

      /*
       *  Function declaration for private helper function branchFractal.
       *  Based on the code from the in-class discussion of fractal trees. 
       */
      int branchFractal(float l0, float r0);

   public:

      /*
       *   Function prototype for Tree object default constructor.  DO NOT USE.
       *   Precondition:  None.
       *   Postcondition: A Tree object has been instantiated at the origin (0, 0, 0), with 1.0
       *   scaling on all axes and 0.0 rotation about each axis.
       */
      Tree();

      /*
       *   Function prototype for Tree object constructor.
       *   Precondition:  None.
       *   Postcondition: A Tree object has been instantiated with the specified translation, scaling
       *                  and rotation.
       *   Parameters:    (x, y, z) coordinates for the objects translation, (x, y, z) values for the objects scaling,
       *                  (x, y, z) values for the objects rotation about the corresponding axis. 
       */
      Tree(float x, float y, float z, float dx, float dy, float dz, float rx, float ry, float rz);

      /*
       *   Function prototype for Tree object implementation of Initialize function (overridden from GameObject superclass).
       *   Precondition:  An instance of a Tree object has been instantiated and a valid RGB bitmap filename has been
       *                  provided.
       *   Postcondition: A texture has been loaded from a .bmp file and applied to the texture field of the object.
       *   Parameters:    The filename for a valid RGB 3 X 8 bit bitmap file of maximum size 512 X 512 pixels.
       */
      int Initialize(const char* filename);

      /*
       *   Funciton prototype for Tree object Render function implementation (overridden from GameObject superclass).
       *   Precondition:  An instance of a Tree object has been instantiated and the Initialize function has been
       *                  called on a valid bitmap file.  This function must be called from within the display function
       *                  of an OpenGL application, or undefined behavior will result.
       *   Postcondition: The object has been rendered in the OpenGL window. 
       */
      void Render();

      /*
       *   Function prototype for Tree object setPosition function.
       *   Precondition:  None.
       *   Postcondition: The translation of the Tree object has been changed to the specified values.
       *   Parameters:    The desired x, y, and z values for the Tree object's translation. 
       */
      void setPosition(float x, float y, float z);

      /*
       *   Function prototype for Tree object setScaling function.
       *   Precondition:  None.
       *   Postcondition: The scaling of the Tree object has been changed to the specified values. 
       *   Parameters:    The desired x, y and z values for the Tree object's scaling. 
       */
      void setScale(float x, float y, float z);

      /*
       *   Function prototype for Tree object setRotation function.
       *   Precondition:  None.
       *   Postcondition: The rotation of the Tree object has been changed to the specified values.
       *   Parameters:    The desired rotation about the x, y and z axes respectively. 
       */
      void setRotation(float x, float y, float z);

      /*
       *   Function prototype for Tree object getPosX getter function.
       *   Precondition:  None.
       *   Postcondition: The x-value of the Tree objects position has been returned to the caller.
       *   Return value:  The x-value of the object's position. 
       */
      float getPosX();

      /*
       *   Function prototype for Tree object getPosY getter function.
       *   Precondition:  None.
       *   Postcondition: The y-value of the Tree objects position has been returned to the caller.
       *   Return value:  The y-value of the object's position. 
       */
      float getPosY();

      /*
       *   Function prototype for Tree object getPosZ getter function.
       *   Precondition:  None.
       *   Postcondition: The z-value of the Tree object's position has been returned to the caller.
       *   Return value:  The z-value of the object's position. 
       */
      float getPosZ();

      /*
       *   Function prototype for Tree object getScaleX getter function.
       *   Precondition:  None.
       *   Postcondition: The x-value of the Tree object's scaling has been returned to the caller.
       *   Return value:  The object's x-scaling.  
       */
      float getScaleX();

      /*
       *    Function prototype for Tree object getScaleY getter function.
       *    Precondition:  None.
       *    Postcondition: The y-value of the Tree object's scaling has been returned to the caller.
       *    Return value:  The object's y-scaling. 
       */
      float getScaleY();

      /*
       *    Function prototype for Tree object getScaleZ getter function.
       *    Precondition:  None.
       *    Postcondition: The z-value of the Tree object's scaling has been returned to the caller.
       *    Return value:  The objects z-scaling. 
       */
      float getScaleZ();

      /*
       *    Function prototype for Tree object getRotX getter function.
       *    Precondition:  None.
       *    Postcondition: The Tree object's rotation about the x-axis has been returned to the caller.
       *    Return value:  The object's rotation about the x-axis. 
       */
      float getRotX();

      /*
       *    Function prototype for Tree object getRotY getter function.
       *    Precondition:  None.
       *    Postcondition: The Tree object's rotation about the y-axis has been returned to the caller.
       *    Return value:  The object's rotation about the y-axis.  
       */
      float getRotY();

      /*
       *    Function prototype for Tree object getRotZ getter function.
       *    Precondition:  None.
       *    Postcondition: The Tree object's rotation about the z-axis has been returned to the caller.
       *    Return value:  The object's rotation about the z-axis. 
       */
      float getRotZ();
};