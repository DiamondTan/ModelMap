#pragma once
#include "MyList.h"
#include "OBJ.h"
#include <string>
#include <vector>


#define SOFA			0
#define BED			1
#define TABLE			2
#define CHAIR			3
#define CABINET		4
#define LIGHT			5
#define OTHER			6

class COBJManager
{
//private:
public:
	struct file
	{
		std::string fileName;
		std::string name;
		int type;
		file()
		{

		}
		file(char * fileName, int type) :fileName(fileName), type(type)
		{
				if (type<0 || type >OTHER)
					type = OTHER;
				this->type = type;
			int n1 = this->fileName.find_last_of('/');
			this->name = this->fileName.substr(n1 + 1);
		}
		file(std::string fileName, int type) :fileName(fileName), type(type)
		{
			if (type<0 || type >OTHER)
				type = OTHER;
			this->type = type;
			int n1 = this->fileName.find_last_of('/');
			this->name = this->fileName.substr(n1 + 1);
		}
		int getType()
		{
			return this->type;
		}
		bool operator==(file pThis)
		{
			if (this->fileName == pThis.fileName && this->type == pThis.type)
			{
				return true;
			}
			
			return false;
		}
	};
public:
	static COBJManager*GetInstance();
	static void DestoryInstance();
	void addfile(file);
	int getfileSize() const;
	file * gatfileAt(int );
	void setShowObj(char *);
	void setShowObj(std::string);
//	static int getShow();
//	static void setShow(int );
	virtual ~COBJManager();
	COBJ* getAt(const int i) const;
	static COBJ* getShowOBJ();
	int getSize() const;
	void addOBJ(COBJ );
	static void delShowObj();
//	void addDraw(int);
	//int getDrawAt(int i) const;
	//int getDrawSize() const;
private:
	/*struct file
	{
		std::string fileName;
		int type;
		file(char * fileName, int type) :fileName(fileName), type(type)
		{

		}
		file(std::string fileName, int type) :fileName(fileName), type(type)
		{

		}
	};*/
	COBJManager();
//	static int show;
	static COBJManager* m_pOBJManager;
	static COBJ *showOBJ;
	MyList<file> fileList;
	MyList<COBJ> DrawList;
	/*std::vector<int> DrawList;*/
};

