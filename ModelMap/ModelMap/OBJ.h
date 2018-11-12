#pragma once
#include <string>
#include <stdlib.h>
#include "glm.h"



class COBJ
{
public:
	COBJ();
	COBJ(char *);
	COBJ(std::string);
	virtual ~COBJ();
	bool ReadFile(char *);
	bool ReadFile(std::string);
	void LoadOBJ();
	void Init();
	//int getType() const;
	//void setType(int );
//	std::string getName();
	virtual void draw();
	void setLocation(float,float);
	bool operator==(COBJ &);
private:
	float xTra;
	float yTra;
	float zTra;
	float xRot;
	GLfloat dimensions[3];
	bool m_bDraw;
	GLMmodel* pModel ;
	float scale;
	//int glName;
	std::string FileName;
//	std::string name; 
	int color[3];
	static float modelCenter[3];
};

