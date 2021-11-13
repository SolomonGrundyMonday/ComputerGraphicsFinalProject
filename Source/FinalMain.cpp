/*
 *   Final Project Main Entry Point.
 *   Created by Jeff Colgan, October 26, 2021,
 *   CSCI-4229 Computer Graphics: Final Project.
 */
#include "CSCIx229.h"
#include "Cuboid.h"
#include "Camera.h"
#include "Tree.h"
#include "Shovel.h"
#include "Axe.h"
#include "Cabin.h"
#include "Skybox.h"
#include "Lantern.h"
#include "Tent.h"
#include <vector>

// Variables for graphical objects.
Cuboid* ground;
Camera* player;
std::vector<Tree *> tree;
Shovel* shovel;
Axe* axe;
Cabin* cabin;
Skybox* sky;
Lantern* lantern;
std::vector<Tent *> tent;

const int treeCount = 42;
const int tentCount = 3;

// Initialize game objects.
void initialize_objects()
{
   // Coordinates for Tree objects.
   float treeCoord[treeCount][2] = { {-43.0, -20.0}, {-44.0, -10.0}, {-45.0, -2.0},
                                     {-44.0, 5.0}, {-42.0, 13.0}, {-45.0, 21.0},
                                     {-46.0, 30.0}, {-39.0, 28.0}, {-42.0, 35.0},
                                     {-37.0, -17.0}, {-35.0, -8.0}, {-38.0, 2.0},
                                     {-34.0, 10.0}, {-36.0, 22.0}, {-28.0, -45.0},
                                     {-26.0, -38.0}, {-25.0, -29.0}, {-29.0, -17.0},
                                     {-27.0, -4.0}, {-28.0, 6.0}, {-26.0, 18.0},
                                     {-29.0, 26.0}, {-27.0, 33.0}, {-19.0, -44.0},
                                     {-17.0, -34.0}, {-24.0, -20.0}, {-18.0, -11.0},
                                     {-15.0, -3.0}, {-17.0, 7.0}, {-19.0, 16.0},
                                     {-17.0, 24.0}, {-5.0, -44.0}, {-7.0, -38.0},
                                     {-4.0, -29.0}, {-11.0, -25.0}, {-6.0, -14.0},
                                     {-12.0, -17.0}, {-5.0, -4.0}, {-4.0, 7.0}, 
                                     {-7.0, 18.0}, {-3.0, 25.0}, {-8.0, 10.0} };

   float tentCoord[tentCount][2] = {{15.0, 10.0}, {20.0, 15.0}, {25.0, 10.0} };

   // Instantiate Trees.
   for (int i = 0; i < treeCount; i++)
   {
      tree.push_back(new Tree(treeCoord[i][0], 1.0, treeCoord[i][1], 1.0, 1.0, 1.0, 0.0, 0.0, 0.0));
      tree.at(i)->Initialize("Assets/Bark.bmp");
   }

   // Instantiate Tents.
   for (int i = 0; i < tentCount; i++)
   {
      tent.push_back(new Tent(tentCoord[i][0], 1.8, tentCoord[i][1], 1.0, 0.8, 1.0, 0.0, i * 90.0 + 90.0, 0.0));
      tent.at(i)->Initialize("Assets/Canvas.bmp");
   }

   // Instantiate ground, camera.
   player = new Camera();
   ground = new Cuboid(0.0, 0.0, 0.0, 50.0, 1.0, 50.0, 0.0, 0.0, 0.0);
   ground->Initialize("Assets/Dirt.bmp");

   // Instantiate skybox.
   sky = new Skybox(0.0, 0.0, 0.0, 50.0, 50.0, 50.0, 0.0, 0.0, 0.0);
   sky->Initialize("Assets/Stars.bmp");

   // Instantiate shovel, axe.
   shovel = new Shovel(-15.0, 2.0, -15.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0);
   shovel->Initialize("Assets/Wood.bmp");
   axe = new Axe(-15.0, 1.5, 0.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0);
   axe->Initialize("Assets/Wood.bmp");

   // Instantiate Cabin.
   cabin = new Cabin(-42.0, 3.0, -39.0, 5.0, 2.0, 7.0, 0.0, 0.0, 0.0);
   cabin->Initialize("Assets/Bricks.bmp");

   lantern = new Lantern(-36.0, 1.2, -30.0, 0.1, 0.1, 0.1, 0.0, 0.0, 0.0);
   lantern->Initialize("Assets/RustyMetal.bmp");
}

// Display function, called by GLUT to update the screen.
void display()
{
   // Clear the buffers, enable depth test.
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glEnable(GL_DEPTH_TEST);

   // Enable normals, lighting.
   glShadeModel(GL_SMOOTH);
   glEnable(GL_NORMALIZE);
   glEnable(GL_LIGHTING);
   glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
   glEnable(GL_COLOR_MATERIAL);

   // Clear transformations and apply camera movement.
   glLoadIdentity();
   player->Turn();
   player->setCenterPos(player->getEyeX() + player->getCenterX(), player->getCenterY(), player->getEyeZ() + player->getCenterZ());
   gluLookAt(player->getEyeX(), player->getEyeY(), player->getEyeZ(), player->getCenterX(), player->getCenterY(), player->getCenterZ(), player->getUpX(), player->getUpY(), player->getUpZ());
   lantern->setPosition(player->getEyeX(), player->getEyeY(), player->getEyeZ());
   lantern->Render();

   // Render Tree objects.
   for (int i = 0; i < treeCount; i++)
      tree.at(i)->Render();

   for (int i = 0; i < tentCount; i++)
      tent.at(i)->Render();

   // Render other objects.
   ground->Render();
   shovel->Render();
   axe->Render();
   cabin->Render();
   sky->Render();

   glWindowPos2i(5, 5);
   Print("Eye position (%.1lf, %.1lf, %.1lf)", player->getEyeX(), player->getEyeY(), player->getEyeZ());

   // Check for errors in GLUT, flush and swap buffers.
   ErrCheck("display");
   glFlush();
   glutSwapBuffers();
}

// Special function, called by GLUT when the user presses an arrow key.
void special(int key, int x, int y)
{
   // If the player presses up arrow, move camera forward.
   if(key == GLUT_KEY_UP)
   {
      player->MoveForward();
   }
   // If the player presses down arrow, move camera backward.
   else if (key == GLUT_KEY_DOWN)
   {
      player->MoveBackward();
   }
   // If the player presses right arrow, turn camera right.
   else if (key == GLUT_KEY_RIGHT)
   {
      int theta = player->getTheta() + 5;
      theta %= 360;
      player->setTheta(theta);
   }
   // If the player presses left arrow, turn camera left.
   else if (key == GLUT_KEY_LEFT)
   {
      int theta = player->getTheta() - 5;
      theta %= 360;
      player->setTheta(theta);
   }

   // Set projection and update display.
   Project(45, player->getAsp(), player->getDim());
   glutPostRedisplay();
}

// Key function, called by GLUT when the player presses a key.
void key(unsigned char key, int x, int y)
{
   // If the player presses the 'escape' key, exit the application.
   if (key == 27)
   {
      exit(0);
   }

   glutPostRedisplay();
}

// Reshape function, called by GLUT when the application window is resized.
void reshape(int width, int height)
{
   double asp;
   
   // Specify viewport, set new aspect ratio, set projection.
   glViewport(0, 0, RES*width, RES*height);
   asp = (height > 0) ? (double)width/height : 1;
   player->setAsp(asp);
   Project(45, player->getAsp(), player->getDim());
}

// Main entry point.
int main(int argc, char* argv[])
{
   // Initialize GLUT.
   glutInit(&argc, argv);

   // Create 500 X 500 window, enable true color RGB, depth buffer, double buffering, name window.
   glutInitWindowSize(500, 500);
   glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
   glutCreateWindow("Jeff Colgan");

#ifdef USEGLEW
   if(glewInit() != GLEW_OK) Fatal("Error initializing GLEW\n");
#endif

   // Specify displaym reshape, special and key functions.
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutSpecialFunc(special);
   glutKeyboardFunc(key);

   // Initialize graphical objects.
   initialize_objects();

   // Check for errors and pass control to GLUT.
   ErrCheck("init");
   glutMainLoop();

   return 0;
}