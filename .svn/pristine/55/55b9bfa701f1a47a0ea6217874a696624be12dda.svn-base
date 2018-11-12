#include "stdafx.h"
#include "OBJ.h"


float COBJ::modelCenter[3] = { 0.0f, 0.0f, 0.0f };

COBJ::COBJ()
: pModel(NULL)
//, name("")
, xTra(0.0)
, yTra(0.0)
, zTra(0.0)
, xRot(0.0)
, scale(15.0)
, m_bDraw(false)
{
	
}

COBJ::COBJ(char * fileName)
:FileName(fileName)
//, name("")
, pModel(NULL)
, xTra(0.0)
, yTra(0.0)
, zTra(0.0)
, xRot(0.0)
, scale(15.0)
, m_bDraw(false)
{

	Init();
	
}

bool COBJ::operator==(COBJ& pThis)
{
	if (this->FileName ==pThis.FileName )
	{
		return true;
	}

	return false;
}
//
//int COBJ::getType() const
//{
//	return this->type;
//}
//
//void COBJ::setType(int type)
//{
//	if (type<0 || type >OTHER)
//		type = OTHER;
//	this->type = type;
//}
//
//std::string COBJ::getName()
//{
//	return this->name;
//}


COBJ::COBJ(std::string fileName)
:FileName(fileName)
//, name("")
, pModel(NULL)
, xTra(0.0)
, yTra(0.0)
, zTra(0.0)
, xRot(0.0)
, scale(15.0)
, m_bDraw(false)
{

	Init();
	
}


COBJ::~COBJ()
{
	if (pModel)
	{
		glmDraw(pModel, GLM_FLAT);
	}
	
}

bool COBJ::ReadFile(std::string fileName)
{
	if (this->FileName.empty())
	{
		return false;
	}

	// If there is a obj model has been loaded, destroy it
	if (pModel)
	{
		return true;
	}

	this->FileName=fileName;

	Init();



	return true;
}

void COBJ::LoadOBJ()
{
	if (pModel)
		return;


	// Load the new obj model
	pModel = glmReadOBJ((this->FileName).c_str());

	// Generate normal for the model
	glmFacetNormals(pModel);

	// Scale the model to fit the screen
	glmUnitize(pModel, modelCenter);

	glmScale(pModel, this->scale);

	glmDimensions(pModel, dimensions);

	this->yTra = dimensions[2]/2;

	m_bDraw = true;
}

void COBJ::Init()
{

	//int n1=FileName.find_last_of('/');
	//this->name = FileName.substr(n1+1);


	

	color[0] = rand() % 255;
	color[1] = rand() % 255;
	color[2] = rand() % 255;

	

	
}

bool COBJ::ReadFile(char *fileName)
{
	if (this->FileName.empty())
	{
		return false;
	}

	// If there is a obj model has been loaded, destroy it
	if (pModel)
	{
		return false;
	}

	this->FileName=fileName;

	Init();

	return true;
}

void COBJ::setLocation(float xTra, float zTra)
{
	this->xTra = xTra;
//	this->yTra = yTra;
	this->zTra = zTra;
}

void COBJ::draw()
{
	glPushMatrix();

	//glColor3i(255,0,0);
	glColor3f(1.0,0.0,0.0);

	glTranslatef(xTra, yTra, zTra);

	glRotatef(xRot, 1.0, 0.0, 0.0);
	if (pModel && m_bDraw)
	{
		//glCallList(this->OBJList);
		glmDraw(pModel, GLM_FLAT);
	}

	glPopMatrix();
}