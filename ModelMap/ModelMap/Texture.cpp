#include "stdafx.h"
#include "Texture.h"

#pragma comment(lib, "glaux.lib")

CTexture::CTexture()
{
	/*初始化程远志为0*/
	image = 0;
	imageWidth = 0;
	imageHeight = 0;
}

CTexture::CTexture(const char *fileName)
{
	/*初始化程远志为0*/
	image = 0;
	imageWidth = 0;
	imageHeight = 0;
	this->Loadbitmap(fileName);
}

CTexture::~CTexture()
{
	FreeImage();  /*释放图像数据占用的内存*/
}

/*装载一个位图文件*/
bool CTexture::Loadbitmap(const char *fileName)
{
	FILE *File = NULL;									// File Handle

	if (!fileName)										// Make Sure A Filename Was Given
	{
		return false;									// If Not Return NULL
	}

	fopen_s(&File,fileName, "r");							// Check To See If The File Exists

	if (!File)											// Does The File Exist?
	{
		MessageBox(NULL,L"打开文件错误",L"ERROR",MB_OK|MB_ICONERROR);
	}

	fclose(File);									// Close The Handle
	this->TextureImage[0] = auxDIBImageLoadA(fileName);				// Load The Bitmap And Return A Pointer

	this->imageWidth = TextureImage[0]->sizeX;
	this->imageHeight = TextureImage[0]->sizeY;
	this->image = TextureImage[0]->data;

	return true;  /*成功返回*/
}

/*释放内存*/
void CTexture::FreeImage()
{
	/*释放内存*/
	/*if (image)
	{
		delete[] image;
		image = 0;
	}*/

	if (TextureImage[0])									// If Texture Exists
	{
		if (TextureImage[0]->data)							// If Texture Image Exists
		{
			free(TextureImage[0]->data);					// Free The Texture Image Memory
			TextureImage[0]->data = NULL;
		}

		free(TextureImage[0]);								// Free The Image Structure
		TextureImage[0] = NULL;
	}
}