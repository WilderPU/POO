/* CÓDIGO DE WILDER */
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
//Movimiento y vista de la piramide
float elapt = 5, inc;
float movx = -10;
float escala = 15.0;
float fc = 1.0;
float FPS = 600;
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

//Class
Model* Piramide;
float mat_diff[] = { 0.6, 0.6, 0.8, 1.0 };

void IdLe()
{
	inc = 20.0 / (elapt * FPS);
	//fc = 1;
	if (movx >= 10.0)
		fc = -1;
	else if (movx <= -10.0)
		fc = 1;
	movx += inc * fc;
	glutPostRedisplay();
}


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

	//Inicialización de los colores
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_blanco);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse_blanco);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular_blanco);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess_blanco);


	Piramide = new Model(); //Inicializo la clase dinamica
	//Piramide->CalcNormModel();
	
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix(); //push 0
	//gluLookAt(0.0, 0.0, 10, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	//------ Trackball -----
	gltbMatrix();
	//----------------------

	// Piramide

	glPushMatrix();
	glTranslated(movx, 0.0, 0.0);
	Piramide->DrawModel(mat_diff); //Con esto graficamos la piramide
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
	glTranslatef(0.0, 0.0, -escala);
	//----------------------------
}


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
		dif = (end - start) * 1.0 / CLOCKS_PER_SEC;
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
}



//----- Tracknall -----------
void mouse(int button, int state, int x, int y)
{
	GLdouble model[4 * 4];
	GLdouble proj[4 * 4];
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


//------ Trackball--------------------

void motion(int x, int y)
{
	GLdouble model[4 * 4];
	GLdouble proj[4 * 4];
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
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(380, 380);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutCreateWindow("Trackball en OpenGL");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(IdLe);
	//------------------------
	//glutKeyboardUpFunc(keyboardUp); //Funcion de flanco de subida
	glutKeyboardFunc(keyboard); //Funcion de flanco de bajada
	//----- Trackball --------
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	//------------------------
	glutMainLoop();
	return 0;
}