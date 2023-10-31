/* CÓDIGO DE WILDER */
#pragma once
#include <iostream>
class Model
{
public:
	Model();
	Model(std::string name);
	~Model();
	void DrawModel();
	void DrawModel(float diff[4]);
	
private:
	void CalcNormModel();
	void Model::CalcNormV(double a[3], double b[3], double c[3], double N[3]);
	void ReadM3D(std::string name);
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
};



