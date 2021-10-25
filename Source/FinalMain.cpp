#include "CSCIx229.h"
#include "Cuboid.h"

double dim = 5.0;
double asp = 1.0;
Cuboid ground;

void display()
{
   // Call object render functions here.
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glEnable(GL_DEPTH_TEST);

   glLoadIdentity();
   
   glEnable(GL_NORMALIZE);

   ground.Render();

   ErrCheck("display");
   glFlush();
   glutSwapBuffers();
}

void special(int key, int x, int y)
{
   if(key == GLUT_KEY_UP)
   {
      
   }
   else if (key == GLUT_KEY_DOWN)
   {
      
   }
   else if (key == GLUT_KEY_RIGHT)
   {
      
   }
   else if (key == GLUT_KEY_LEFT)
   {
      
   }

   Project(45, asp, dim);

   glutPostRedisplay();
}

void key(unsigned char key, int x, int y)
{
   if (key == 27)
   {
      exit(0);
   }

   glutPostRedisplay();
}

void reshape(int width, int height)
{
   glViewport(0, 0, RES*width, RES*height);
   asp = (height > 0) ? (double)width/height : 1;
   Project(45, asp, dim);
}

int main(int argc, char* argv[])
{
   glutInit(&argc, argv);

   glutInitWindowSize(500, 500);
   glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
   glutCreateWindow("Jeff Colgan");

#ifdef USEGLEW
   if(glewInit() != GLEW_OK) Fatal("Error initializing GLEW\n");
#endif

   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutSpecialFunc(special);
   glutKeyboardFunc(key);

   ground = Cuboid(0.0, 0.0, 0.0, 50.0, 1.0, 50.0, 0.0, 0.0, 0.0);
   ground.Initialize("Dirt.bmp");

   ErrCheck("init");
   glutMainLoop();

   return 0;
}