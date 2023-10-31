/* CÓDIGO DE WILDER */
#include "Model.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glut.h>
#include <math.h>
#include <time.h>

#include "Model.h"

//Piramide               0    1     2
double vert_[5][3] = {{ 0.5, 0.0, -0.5}, // 0
					  {-0.5, 0.0, -0.5}, // 1
					  {-0.5, 0.0,  0.5}, // 3
					  { 0.5, 0.0,  0.5}, // 4
					  { 0.0, 1.0,  0.0}  // 5
};

//				    0  1  2
int face_[6][3] = {{0, 1, 4},  //0
				   {1, 2, 4},  //1
				   {2, 3, 4},  //2
				   {3, 0, 4},  //3
				   {3, 2, 0},  //4
				   {2, 1, 0}   //5
};


Model::Model() //Inicializar datos de piramides
{
	nvert = 5;
	V = new vertex[nvert]; //Inicia memoria dinamica
	for (int j = 0; j < nvert; j++)
		for (int i = 0; i < 3; i++)
			V[j].ver[i] = vert_[j][i];
	
	nface = 6;
	F = new face[nface];
	for (int i = 0; i < nface; i++)
		for (int j = 0; j < 3; j++)
			F[i].tri[j] = face_[i][j];

	CalcNormModel();
	//DrawModel();
	
}
Model::~Model()
{
	if (V != NULL)
		delete V; //Cierra la memoria dinamica, es IMPORTANTE para que no queden los datos en la RAM

	

	if (F != NULL)
		delete F;
}

/* EL & apunta a una variable, este es un apuntador por referencia.
En cambio los apuntadores * son un tipo de dato.
*/


void Model::CalcNormModel()
{
	for (int i = 0; i < nface; i++) // V[ 1 nertice de una cara]
		CalcNormV(V[F[i].tri[0]].ver, V[F[i].tri[1]].ver, V[F[i].tri[2]].ver, F[i].N);
}

void Model::DrawModel(float dif[4]) {
	glMaterialfv(GL_FRONT, GL_SPECULAR, dif);
	DrawModel();
}

void Model::DrawModel()
{
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < 6; i++)
	{
		glNormal3dv(F[i].N);
		for (int j = 0; j < 3; j++)
			glVertex3d(V[F[i].tri[j]].ver[0], V[F[i].tri[j]].ver[1], V[F[i].tri[j]].ver[2]);
	}
	glEnd();
}

void Model::CalcNormV(double a[3], double b[3], double c[3], double N[3])
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