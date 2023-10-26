#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h> //libreria de tiempo
#include <GL/glut.h>

//------ trackball----------
#include "trackball.h" //implementacion del Trackball
//-----------------------

// Incluimos la clase
#include "Model.h"

//var tiempo
clock_t start, end;


//------ Trackball ------------
static GLint      mouse_state;
static GLint      mouse_button;
GLdouble   pan_x = 0.0;
GLdouble   pan_y = 0.0;
GLdouble   pan_z = 0.0;
//-----------------------------

//parametros de la fuente de luz
float LightPos[] = { 0.0f, 0.0f, 1.0f, 0.0f };
float LightAmb[] = { 0.5f, 0.5f, 0.5f, 1.0f };
float LightDif[] = { 1.0f, 1.0f, 1.0f, 1.0f };
float LightSpc[] = { 1.0f, 1.0f, 1.0f, 1.0f };

//Azul
float mat_ambient_azul[] = { 0.0, 0.0, 0.25, 1.0 };
float mat_diffuse_azul[] = { 0.0, 0.0, 1.0, 1.0 };
float mat_specular_azul[] = { 1.0, 1.0, 1.0, 1.0 };
float mat_shininess_azul = 100.0;
//Blanco
float mat_ambient_blanco[] = { 0.25, 0.25, 0.25, 1.0 };
float mat_diffuse_blanco[] = { 1.0, 1.0, 1.0, 1.0 };
float mat_specular_blanco[] = { 1.0, 1.0, 1.0, 1.0 };
float mat_shininess_blanco = 100.0;



/*
//Piramide               0    1     2
double vert[5][3] = { { 0.5, 0.0, -0.5}, // 0
					  {-0.5, 0.0, -0.5}, // 1
					  {-0.5, 0.0,  0.5}, // 3
					  { 0.5, 0.0,  0.5}, // 4
					  { 0.0, 1.0,  0.0}  // 5
};

//					0  1  2
int face[6][3] = { {0, 1, 4},  //0
				   {1, 2, 4},  //1
				   {2, 3, 4},  //2
				   {3, 0, 4},  //3
				   {3, 2, 0},  //4
				   {2, 1, 0}   //5
};
*/

//Class
Model *Piramide;

//Prototipos de funciones
//void CalcNormV(double a[3], double b[3], double c[3], double N[3]);


/*
void CalcNormV(double a[3], double b[3], double c[3], double N[3])
{
	double Vab[3], Vac[3], norm;

	for (int i = 0; i < 3; i++)
	{
		Vab[i] = b[i] - a[i];
		Vac[i] = c[i] - a[i];
	}

	N[0] = Vab[1] * Vac[2] - Vab[2] * Vac[1];
	N[1] = Vab[2] * Vac[0] - Vab[0] * Vac[2];
	N[2] = Vab[0] * Vac[1] - Vab[1] * Vac[0];

	norm = sqrt(N[0] * N[0] + N[1] * N[1] + N[2] * N[2]);

	for (int i = 0; i < 3; i++)
		N[i] = N[i] / norm; //Este es el vector normal (unitario)
}
*/




void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glLightfv(GL_LIGHT0, GL_POSITION, LightPos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, LightSpc);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	//------ Trackball -----------
	gltbInit(GLUT_LEFT_BUTTON/*GLUT_MIDDLE_BUTTON*/);
	//----------------------------
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //FILL para mostrar la figura solida - LINE para ver solo las lineas - POINT para mostrar los vertices
	
	Piramide = new Model(); //Inicializo la clase dinamica
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix(); //push 0
	//gluLookAt(0.0, 0.0, 10, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	//------ Trackball -----
	gltbMatrix();
	//----------------------

	// esfera 1
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_blanco);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse_blanco);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular_blanco);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess_blanco);
	
	glPushMatrix();
	//Piramide->CalcNormModel();
	Piramide->DrawModel();
	//Piramide->CalcNormModel();
	/*
	int dirf; //direccion en la lista de caras del vertice j
	double N[3], a[3], b[3], c[3];
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			a[j] = vert[face[i][0]][j];
			b[j] = vert[face[i][1]][j];
			c[j] = vert[face[i][2]][j];
		}

		CalcNormV(a, b, c, N);
		glNormal3dv(N);
		for (int j = 0; j < 3; j++)
		{
			dirf = face[i][j];
			glVertex3d(vert[dirf][0], vert[dirf][1], vert[dirf][2]);
		}
	}
	glEnd();
	*/
	glPopMatrix();

	glPopMatrix(); //fin push 0
	glFlush();
	glutSwapBuffers();
}


void reshape(int w, int h)
{
	if (!h)
		return;

	//------ Trackball --------
	gltbReshape(w, h);
	//-------------------------

	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 0.01, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//------ Trackball -----------
	glTranslatef(0.0, 0.0, -5.0);
	//----------------------------
}//*/


void keyboard(unsigned char key, int x, int y)
{

 switch (key)
   {
	 double dif;
   case 27: 
	   delete Piramide; //Finalizamos la clase dinamica
	   exit(0);	
	   break;

   case 's':
   case 'S':
	   start = clock();
	   printf("input down or socd:2\n");
	   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	   glutPostRedisplay();
	   break;

   case 'd':
   case 'D':
	   end = clock();
	   dif = (end-start) * 1.0 / CLOCKS_PER_SEC;
	   printf("input down or socd:6, %lg(sec)\n", dif);
	   break;

   case 'N':
   case 'n':
	   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	   glLineWidth(3.0);
	   glutPostRedisplay();
	   break;
   case 'b':
   case 'B':
	   glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	   glPointSize(5.0);
	   glutPostRedisplay();
	   break;
   case 'm':
   case 'M':
	   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	   glutPostRedisplay();
	   break;

   }
}//*/



//----- Tracknall -----------
void mouse(int button, int state, int x, int y)
{
 GLdouble model[4*4];
 GLdouble proj[4*4];
 GLint view[4];

 // fix for two-button mice -- left mouse + shift = middle mouse
 if (button == GLUT_LEFT_BUTTON && glutGetModifiers() & GLUT_ACTIVE_SHIFT)
	button = GLUT_MIDDLE_BUTTON;
 gltbMouse(button, state, x, y);
 mouse_state = state;
 mouse_button = button;
 if (state == GLUT_DOWN && button == GLUT_MIDDLE_BUTTON)
	{
	glGetDoublev(GL_MODELVIEW_MATRIX, model);
	glGetDoublev(GL_PROJECTION_MATRIX, proj);
	glGetIntegerv(GL_VIEWPORT, view);
	gluProject((GLdouble)x, (GLdouble)y, 0.0,
				model, proj, view,
				&pan_x, &pan_y, &pan_z);
	gluUnProject((GLdouble)x, (GLdouble)y, pan_z,
				 model, proj, view,
				 &pan_x, &pan_y, &pan_z);
	pan_y = -pan_y;
	}
 glutPostRedisplay();
}
//*/

//------ Trackball--------------------

void motion(int x, int y)
{
 GLdouble model[4*4];
 GLdouble proj[4*4];
 GLint view[4];

 gltbMotion(x, y);
 if (mouse_state == GLUT_DOWN && mouse_button == GLUT_MIDDLE_BUTTON)
	{
	glGetDoublev(GL_MODELVIEW_MATRIX, model);
	glGetDoublev(GL_PROJECTION_MATRIX, proj);
	glGetIntegerv(GL_VIEWPORT, view);
	gluProject((GLdouble)x, (GLdouble)y, 0.0,
				model, proj, view,
				&pan_x, &pan_y, &pan_z);
	gluUnProject((GLdouble)x, (GLdouble)y, pan_z,
				model, proj, view,
				&pan_x, &pan_y, &pan_z);
	pan_y = -pan_y;
	}
 glutPostRedisplay();
}//*/

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(380, 380);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutCreateWindow("Trackball en OpenGL");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	//----- Trackball --------
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	//------------------------
	glutMainLoop();
	return 0;
}