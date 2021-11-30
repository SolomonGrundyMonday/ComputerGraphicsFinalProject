/*
 *   Final Project Main Entry Point.
 *   Created by Jeff Colgan, October 26, 2021,
 *   CSCI-4229 Computer Graphics: Final Project.
 */
#include "CSCIx229.h"
#include "Cuboid.h"
#include "Tree.h"
#include "Shovel.h"
#include "Axe.h"
#include "Cabin.h"
#include "Skybox.h"
#include "Tent.h"
#include "Lantern.h"
#include "Horizon.h"
#include "TreeStump.h"
#include "CaveWall.h"
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
Horizon* horizon;
CaveWall* back;
CaveWall* left;
CaveWall* right;
CaveWall* front;
std::vector<CaveWall *> innerWalls;
std::vector<TreeStump *> stump;
std::vector<Tent *> tent;

const int treeCount = 38;
const int tentCount = 4;
const int stumpCount = 8;
const int wallCount = 9;

// Initialize game objects.
void initialize_objects()
{
   // Coordinates for Tree objects.
   float treeCoord[treeCount][2] = { {-27.0, -8.5}, {-16.0, -14.0}, {-18.0, -10.0},
                                     {-15.0, -3.0}, {-16.0, 4.0}, {-19.0, 9.0},
                                     {-17.0, 15.0}, {-15.0, 22.0}, {8.0, -22.0},
                                     {-22.0, -3.0}, {-23.0, 6.0}, {-22.0, 19.0},
                                     {3.0, -10.0}, {-9.0, -25.5}, {-14.0, -19.5},
                                     {-11.0, -12.5}, {-10.0, -6.0}, {-11.0, 1.5},
                                     {-12.0, 7.0}, {-10.5, 13.0}, {-11.5, 19.0},
                                     {-4.0, -23.0}, {-2.0, -14.5}, {-3.0, -10.0},
                                     {-7.0, 0.5}, {-4.0, 6.5}, {-5.0, 13.0},
                                     {-3.0, 17.0}, {-6.0, 23.0}, {-25.5, 11.5},
									 {-1.0, -4.5}, {9.0, 1.0}, {0.0, 11.5},
                                     {6.5, -11.0}, {4.0, -3.0}, {9.5, -6.5},
                                     {2.5, 6.5} };

   // Coordinates for Tent objects.
   float tentCoord[tentCount][2] = { {15.0, 10.0}, {15.0, 20.0}, {20.0, 10.0}, {20.0, 20.0} };

   // Coordinates for TreeStump objects.
   float stumpCoord[stumpCount][2] = { {5.0, 14.5}, {18.5, 15.0}, {4.0, 21.0},
                                       {3.5, 9.5}, {1.0, 17.0}, {6.5, 18.0},
                                       {9.0, 14.0}, {10.5, 7.5} };

   // Coordinates for inner walls of hedge maze area.
   float wallCoord[wallCount][4] = { {18.0, -3.5, 2.0, 0.0}, {21.75, -17.0, 2.0, 90.0}, {18.4, -1.0, 2.0, 90.0},
                                     {21.2, -3.2, 1.5, 90.0}, {20.0, -6.5, 2.2, 0.0}, {19.0, -11.1, 3.5, 90.0},
                                     {17.3, -16.6, 1.5, 0.0}, {21.0, -12.1, 1.0, 0.0}, {21.0, -11.8, 1.5, 90.0} };

   // Instantiate Trees.
   for (int i = 0; i < treeCount; i++)
   {
      tree.push_back(new Tree(treeCoord[i][0], 1.0, treeCoord[i][1], 1.0, 1.0, 1.0, 0.0, 0.0, 0.0));
      tree.at(i)->Initialize("Assets/Bark.bmp");
   }

   // Instantiate Tents.
   for (int i = 0; i < tentCount; i++)
   {
      tent.push_back(new Tent(tentCoord[i][0], 1.8, tentCoord[i][1], 1.0, 0.8, 1.0, 0.0, (i % 2) * 180.0, 0.0));
      tent.at(i)->Initialize("Assets/Canvas.bmp");
   }

   // Instantiate TreeStumps.
   for (int i = 0; i < stumpCount; i++)
   {
      stump.push_back(new TreeStump(stumpCoord[i][0], 1.0, stumpCoord[i][1], 0.1, 0.2, 0.1, 0.0, 0.0, 0.0));
      stump.at(i)->Initialize("Assets/Bark.bmp");
   }

   // Instantiate ground, camera.
   player = new Camera();

   // Work on solution to ground lighting...
   ground = new Cuboid(0.0, 0.0, 0.0, 35.0, 1.0, 35.0, 0.0, 0.0, 0.0);
   ground->Initialize("Assets/Dirt.bmp");

   // Instantiate skybox.
   sky = new Skybox(0.0, 25.0, 0.0, 30.0, 25.0, 30.0, 0.0, 0.0, 0.0);
   sky->Initialize("Assets/Stars.bmp");
   horizon = new Horizon(0.0, 3.0, 0.0, 29.9, 2.0, 29.9, 0.0, 0.0, 0.0);
   horizon->Initialize("Assets/Horizon.bmp");

   // Instantiate shovel, axe.
   shovel = new Shovel(18.5, 1.25, 14.85, 0.25, 0.25, 0.25, 55.0, 0.0, 0.0);
   shovel->Initialize("Assets/Wood.bmp");

   axe = new Axe(9.4, 1.45, 14.0, 0.4, 0.4, 0.4, 0.0, 0.0, 120.0);
   axe->Initialize("Assets/Wood.bmp");

   // Instantiate Cabin.
   cabin = new Cabin(-23.0, 2.0, -21.0, 3.0, 1.0, 5.0, 0.0, 0.0, 0.0);
   cabin->Initialize("Assets/Bricks.bmp");

   // Instantiate Lantern.
   lantern = new Lantern(18.5, 1.3, 15.0, 0.1, 0.1, 0.1, 0.0, 0.0, 0.0);
   lantern->Initialize("Assets/RustyMetal.bmp");

   // Instatiate Exterior walls of hedge maze.
   back = new CaveWall(18.25, 2.0, -17.8, 2.5, 2.0, 1.0, 0.0, 0.0, 0.0);
   back->Initialize("Assets/Hedge.bmp");

   left = new CaveWall(17.0, 2.0, -9.0, 10.0, 2.0, 1.0, 0.0, 90.0, 0.0);
   left->Initialize("Assets/Hedge.bmp");

   right = new CaveWall(21.0, 2.0, -9.0, 10.0, 2.0, 1.0, 0.0, -90.0, 0.0);
   right->Initialize("Assets/Hedge.bmp");

   front = new CaveWall(19.7, 2.0, 0.0, 2.5, 2.0, 1.0, 0.0, 180.0, 0.0);
   front->Initialize("Assets/Hedge.bmp");

   // Instantiate inner walls of hedge maze.
   for (int i = 0; i < wallCount; i++)
   {
      innerWalls.push_back(new CaveWall(wallCoord[i][0], 2.0, wallCoord[i][1], wallCoord[i][2], 2.0, 1.0, 0.0, wallCoord[i][3], 0.0));
      innerWalls.at(i)->Initialize("Assets/Hedge.bmp");
   }

}

// Display function, called by GLUT to update the screen.
void display()
{
   // Variables for Eye and Center vectors to reduce function calls in display.
   float Eye[3];
   float Center[3];

   Eye[0] = player->getEyeX();
   Eye[1] = player->getEyeY();
   Eye[2] = player->getEyeZ();

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

   // Resolve Horizon collisions (handles collisions for skybox).
   if (horizon->detectCollision(player))
      horizon->resolveCollision(player);

   // Resolve collisions for Cabin.
   cabin->resolveCollision(player);

   // Resolve collisions for Axe.
   if (axe->detectCollision(player))
      axe->resolveCollision(player);

   // Resolve collisions for Shovel.
   if (shovel->detectCollision(player))
      shovel->resolveCollision(player);

   // Resolve collisions for TreeStumps.
   for (int i = 0; i < stumpCount; i++)
   {
      if (stump.at(i)->detectCollision(player))
         stump.at(i)->resolveCollision(player);
   }

   // Resolve collisions for Trees.
   for (int i = 0; i < treeCount; i++)
   {
      tree.at(i)->resolveCollision(player);
   }

   // Resolve collisions for Tents.
   for (int i = 0; i < tentCount; i++)
   {
      if (tent.at(i)->detectCollision(player))
      {
         tent.at(i)->resolveCollision(player);
      }
   }

   // Resolve collisions for exterior hedge maze walls.
   if (back->detectCollision(player))
      back->resolveCollision(player);
   if (left->detectCollision(player))
      left->resolveCollision(player);
   if (right->detectCollision(player))
      right->resolveCollision(player);
   if (front->detectCollision(player))
      front->resolveCollision(player);

   // Resolve collisions for interior hedge maze walls.
   for (int i = 0; i < wallCount; i++)
   {
      if (innerWalls.at(i)->detectCollision(player))
         innerWalls.at(i)->resolveCollision(player);
   }

   // Update Camera center vector based on player movement.
   player->setCenterPos(Eye[0] + player->getCenterX(), player->getCenterY(), Eye[2] + player->getCenterZ());
   Center[0] = player->getCenterX();
   Center[1] = player->getCenterY();
   Center[2] = player->getCenterZ();
   gluLookAt(Eye[0], Eye[1], Eye[2], Center[0], Center[1], Center[2], player->getUpX(), player->getUpY(), player->getUpZ());

   player->shineLight();

   // Render Tree objects.
   for (int i = 0; i < treeCount; i++)
      tree.at(i)->Render();

   // Render Tent objects.
   for (int i = 0; i < tentCount; i++)
      tent.at(i)->Render();

   // Render TreeStump objects.
   for (int i = 0; i < stumpCount; i++)
      stump.at(i)->Render();

   // Render the ground.
   ground->Render();

   // Render Shovel object.
   shovel->Render();

   // Render Axe object.
   axe->Render();

   // Render Cabin object.
   cabin->Render();

   // Render Skybox/Horizon objects.
   sky->Render();
   horizon->Render();

   // Render Lantern, enable Lantern light source.
   lantern->Render();
   lantern->lightSource();

   // Render exterior hedge maze walls.
   back->Render();
   left->Render();
   right->Render();
   front->Render();

   // Render inner hedge maze walls.
   for (int i = 0; i < wallCount; i++)
      innerWalls.at(i)->Render();

   glWindowPos2i(5, 5);
   Print("Current position: (%.1lf, %.1lf, %.1lf)", player->getEyeX(), player->getEyeY(), player->getEyeZ());

   // Check for errors in GLUT, flush and swap buffers.
   ErrCheck("display");
   glFlush();
   glutSwapBuffers();
}

// Special function, called by GLUT when the user presses an arrow key.
void special(int key, int x, int y)
{
   // If the player presses right arrow, turn camera right.
   if (key == GLUT_KEY_RIGHT)
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
   // If the player presses the 'F' key, toggle the Camera flashlight component.
   else if (key == 'f' || key == 'F')
   {
      player->toggleLight();
   }
   // If the player presses the 'W' key, move the Camera forward.
   else if (key == 'w' || key == 'W')
   {
      player->MoveForward();
   }
   // If the player presses the 'S' key, move the Camera backward.
   else if (key == 's' || key == 'S')
   {
      player->MoveBackward();
   }
   // If the player presses the 'A' key, strafe the Camera to the left.
   else if (key == 'a' || key == 'A')
   {
      player->StrafeLeft();
   }
   // If the player presses the 'D' key, strafe the Camera to the right.
   else if (key == 'd' || key == 'D')
   {
      player->StrafeRight();
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