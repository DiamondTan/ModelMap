#include "stdafx.h"
#include "OBJManager.h"

COBJManager* COBJManager::m_pOBJManager = NULL;
//int COBJManager::show = -1;
COBJ *COBJManager::showOBJ = NULL; 



COBJManager::COBJManager()
{
	showOBJ = NULL;
	srand(time(NULL));
}

void COBJManager::setShowObj(char *filename)
{
	showOBJ = new COBJ(filename);
}

void COBJManager::setShowObj(std::string filename)
{
	showOBJ = new COBJ(filename);
}

COBJManager::~COBJManager()
{
	if (showOBJ)
	{
		delete showOBJ;
		showOBJ = NULL;
	}
}

COBJ* COBJManager::getShowOBJ()
{
	return showOBJ;
}

void COBJManager::delShowObj()
{
	if (showOBJ)
		delete showOBJ;
	showOBJ = NULL;
}

COBJ* COBJManager::getAt(const int i) const
{
	try{
		return this->DrawList.at(i);
	}
	catch (std::out_of_range err)
	{
		//MessageBox(NULL,L"ERROR",(LPCWSTR)err.what(),MB_OK|MB_ICONERROR);
		MessageBox(NULL, L"ERROR", L"数组越界", MB_OK | MB_ICONERROR);
	}
	return this->DrawList.at(this->getSize() - 1);
}




COBJManager* COBJManager::GetInstance()
{
	if (COBJManager::m_pOBJManager == NULL)
	{
		m_pOBJManager = new COBJManager;
	}

	return m_pOBJManager;
}

void COBJManager::DestoryInstance()
{
	if (COBJManager::m_pOBJManager != NULL)
	{
		delete m_pOBJManager;
	}

}

int COBJManager::getfileSize() const
{
	return this->fileList.getSize();
}
COBJManager::file* COBJManager::gatfileAt(int i)
{
	return this->fileList.at(i);
}
void COBJManager::addfile(file file)
{
	COBJManager::file* pThis;
	for (int i = 0; i < this->getfileSize(); i++)
	{
		pThis = this->gatfileAt(i);
		if (*pThis == file)
		{
			return;
		}

	}
	this->fileList.Add(file);
}


int COBJManager::getSize() const
{
	return (this->DrawList).getSize();
}
//
void COBJManager::addOBJ(COBJ obj)
{
	/*COBJ* pThis;
	for (int i = 0; i < this->getSize(); i++)
	{
		pThis = this->getAt(i);
		if (*pThis == obj)
		{
			return;
		}

	}*/
	this->DrawList.Add(obj);
}
//void COBJManager::addDraw(int value)
//{
//	this->DrawList.Add(value);
//}
//int COBJManager::getDrawAt(int i) const
//{
//	try{
//		return (this->DrawList.at(i));
//	}
//	catch (std::out_of_range err)
//	{
//		//MessageBox(NULL,L"ERROR",(LPCWSTR)err.what(),MB_OK|MB_ICONERROR);
//		MessageBox(NULL, L"ERROR", L"数组越界", MB_OK | MB_ICONERROR);
//	}
//	return (this->DrawList.at(this->getSize() - 1));
//}
//
//int COBJManager::getDrawSize() const 
//{
//	return (this->DrawList).size();
//}
//int COBJManager::getShow()
//{
//	return COBJManager::show;
//}
//
//void COBJManager::setShow(int show)
//{
//	COBJManager::show = show;
//}