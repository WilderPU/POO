/* CÓDIGO DE WILDER */
#pragma once
#include <iostream>
class Model
{
public: // Todos los metodos estan disponibles para todo el público
	Model();
	Model(std::string name);
	~Model();
	void DrawModel();
	void DrawModel(float diff[4]);
	
private: //Esta disponible solo para la clase
	void CalcNormModel();
	void Model::CalcNormV(double a[3], double b[3], double c[3], double N[3]);
	struct vertex
	{
		double ver[3];
	};
	struct face
	{
		int tri[3];
		double N[3];
	};
	int nvert, nface;
	vertex *V;
	face *F;
protected: //Esta disponible para las clases heredadas
	void ReadM3D(std::string name);
};

//Herencia
class Ken :public Model {
public:
	Ken(std::string name);
};
