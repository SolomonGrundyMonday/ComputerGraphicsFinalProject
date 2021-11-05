#include "Cabin.h"

int zh = 90;
int th = 0.0;
int ph = 0.0;
double asp = 1.0;
double dim = 4.0;
Cabin* cabin;

void display()
{
   float Ambient[] = {0.0, 0.0, 0.0, 1.0};
   float Diffuse[] = {1.0, 1.0, 1.0, 1.0};
   float Specular[] = {0.0, 0.0, 0.0, 1.0};
   float Position[] = {5*Cos(zh), 0.0, 5*Sin(zh), 1.0};
   double Ex = -2*dim*Sin(th)*Cos(ph);
   double Ey = 2*dim*Sin(ph);
   double Ez = 2*dim*Cos(th)*Cos(ph);

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glEnable(GL_DEPTH_TEST);

   glLoadIdentity();
   gluLookAt(Ex, Ey, Ez, 0, 0, 0, 0, Cos(ph), 0);

   glShadeModel(GL_SMOOTH);

   glColor3f(1.0, 1.0, 1.0);
   glPushMatrix();
   glTranslated(Position[0], Position[1], Position[2]);
   glScaled(0.1, 0.1, 0.1);
   glutSolidSphere(1.0, 16, 16);
   glPopMatrix();

   glEnable(GL_NORMALIZE);
   glEnable(GL_LIGHTING);
   glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
   glEnable(GL_COLOR_MATERIAL);
   glEnable(GL_LIGHT0);

   glLightfv(GL_LIGHT0, GL_AMBIENT, Ambient);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, Diffuse);
   glLightfv(GL_LIGHT0, GL_SPECULAR, Specular);
   glLightfv(GL_LIGHT0, GL_POSITION, Position);

   cabin->Render();

   ErrCheck("display");
   glFlush();
   glutSwapBuffers();
}

void idle()
{
   double t = glutGet(GLUT_ELAPSED_TIME)/1000.0;
   zh = fmod(90.0*t,360.0);
   glutPostRedisplay();
}

void special(int key, int x, int y)
{
   if(key == GLUT_KEY_RIGHT)
   {
      th += 5;
   }
   else if (key == GLUT_KEY_LEFT)
   {
      th -= 5; 
   }
   else if (key == GLUT_KEY_UP)
   {
      ph += 5;
   }
   else if (key == GLUT_KEY_DOWN)
   {
      ph -= 5;
   }

   th %= 360;
   ph %= 360;

   Project(45, asp, dim);

   glutPostRedisplay();
}

void key(unsigned char key, int x, int y)
{
   if (key == 27)
      exit(0);

   glutPostRedisplay();
}

void reshape(int width, int height)
{
   glViewport(0, 0, RES * width, RES * height);
   asp = (height > 0) ? (double)width/height : 1;
   Project(45, asp, dim);
}

int main(int argc, char* argv[])
{
   glutInit(&argc, argv);

   glutInitWindowSize(500, 500);
   glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
   glutCreateWindow("Lighting Test");

#ifdef USEGLEW
   if(glewInit() != GLEW_OK) Fatal("Error initializing GLEW\n");
#endif

   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutSpecialFunc(special);
   glutKeyboardFunc(key);
   glutIdleFunc(idle);

   cabin = new Cabin(0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0);
   cabin->Initialize("Assets/Bricks.bmp");

   ErrCheck("init");
   glutMainLoop();

   return 0;
}