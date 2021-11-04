#include "CSCIx229.h"
#include "Cuboid.h"
#include "Camera.h"
#include "Tree.h"
#include "Shovel.h"
#include "Axe.h"
#include "Cabin.h"
#include <vector>

Cuboid ground;
Camera player;
std::vector<Tree *> tree;
Shovel* shovel;
Axe* axe;
Cabin* cabin;

void display()
{
   // Call object render functions here.
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glEnable(GL_DEPTH_TEST);

   glLoadIdentity();

   player.Turn();
   gluLookAt(player.getEyeX(), player.getEyeY(), player.getEyeZ(), player.getCenterX() + player.getEyeX(), player.getCenterY(), player.getCenterZ() + player.getEyeZ(), player.getUpX(), player.getUpY(), player.getUpZ());
   
   glEnable(GL_NORMALIZE);

   for (int i = 0; i < 10; i++)
      tree.at(i)->Render();

   ground.Render();
   shovel->Render();
   axe->Render();
   cabin->Render();

   ErrCheck("display");
   glFlush();
   glutSwapBuffers();
}

void special(int key, int x, int y)
{
   if(key == GLUT_KEY_UP)
   {
      player.MoveForward();
   }
   else if (key == GLUT_KEY_DOWN)
   {
      player.MoveBackward();
   }
   else if (key == GLUT_KEY_RIGHT)
   {
      int theta = player.getTheta() + 5;
      theta %= 360;
      player.setTheta(theta);
   }
   else if (key == GLUT_KEY_LEFT)
   {
      int theta = player.getTheta() - 5;
      theta %= 360;
      player.setTheta(theta);
   }

   Project(45, player.getAsp(), player.getDim());

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
   double asp;
   
   glViewport(0, 0, RES*width, RES*height);
   asp = (height > 0) ? (double)width/height : 1;
   player.setAsp(asp);
   Project(45, player.getAsp(), player.getDim());
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

   player = Camera();

   for (int i = 0; i < 10; i++)
   {
      tree.push_back(new Tree(i*10.0, 1.0, i*10.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0));
      tree.at(i)->Initialize("Bark.bmp");
   }

   shovel = new Shovel(-15.0, 3.0, -15.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0);
   shovel->Initialize("Wood.bmp");

   axe = new Axe(-15.0, 0.5, 0.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0);
   axe->Initialize("Wood.bmp");

   cabin = new Cabin(10.0, 3.0, 0.0, 6.0, 2.0, 9.0, 0.0, 180.0, 0.0);
   cabin->Initialize("Bricks.bmp");

   ErrCheck("init");
   glutMainLoop();

   return 0;
}