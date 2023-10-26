#pragma once
class Model
{
public:
	Model();
	~Model();
	void CalcNormModel();
	void DrawModel();
private:
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
};

