#pragma once
class Model
{
public:
	Model();
	~Model();
	void CalcNormV();
	void DrawModel();
private:
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

