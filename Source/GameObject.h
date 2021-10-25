
#include "CSCIx229.h"
#include <string.h>
#include <stdlib.h>

class GameObject
{

   public:
      virtual int Initialize(const char* filename) = 0;
      virtual void Render() = 0;
};
