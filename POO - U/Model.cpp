#include "Model.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

//				0  1  2
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
	for (int i = 0; i < nvert; i++) {
		V[i].ver[0] = vert_[i][0];
		V[i].ver[1] = vert_[i][1];
		V[i].ver[2] = vert_[i][2];
	}

	nface = 6;
	F = new face[nface];
	for (int i = 0; i < nface; i++) {
		F[i].tri[0] = face_[i][0];
		F[i].tri[1] = face_[i][1];
		F[i].tri[2] = face_[i][2];
	}


	
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

void Model::CalcNormV() {
	//Escribir función
}

void Model::DrawModel() {
	//Escribir función
}