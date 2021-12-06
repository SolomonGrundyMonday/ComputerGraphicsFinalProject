/*
 *   GameObject abstract superclass declaration.
 *   
 *   Created by Jeff Colgan, October 25, 2021,
 *   CSCI-4229 Computer Graphics: Final Project.
 *
 *   This is the abstract superclass for all rendered GameObjects
 *   All rendered 3D objects should inherit from this class. 
 */
#pragma once
#include "CSCIx229.h"
#include "Camera.h"
#include <string.h>
#include <stdlib.h>

// Enum for the walls of a GameObject's hit boxe.
enum wall {
   FRONT,
   FRONT_RIGHT,
   FRONT_LEFT,
   LEFT,
   RIGHT,
   BACK,
   NONE
};

class GameObject
{

   public:
      /*
       *   Function prototype for pure virtual Initialize function.  
       *   All subclasses of GameObject must implement this function.
       */
      virtual int Initialize(const char* filename) = 0;

      /*
       *    Function prototype for pure virtual Render function.
       *    All subclasses of GameObject must implement this function. 
       */
      virtual void Render() = 0;

      /*
       *    Function prototype for pure virtual resolveCollision function.
       *    All subclasses of Gameobject must implement this function. 
       */
      virtual void resolveCollision(Camera* camera) = 0;
};
