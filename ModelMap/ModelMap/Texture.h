#pragma once

#define BITMAP_ID 0x4D42	/**< λͼ�ļ��ı�־ */

class CTexture
{
public:
	CTexture();
	CTexture(const char *filename);
	~CTexture();

	bool Loadbitmap(const char *filename);   /*װ��һ��bmp�ļ�*/
	void FreeImage();				/*�ͷ�ͼ������*/
	AUX_RGBImageRec *TextureImage[1];
	unsigned int ID;     /*���������ID��*/
	int imageWidth;      /*ͼ����*/
	int imageHeight;     /*ͼ��߶�*/
	unsigned char *image;  /*ָ��ͼ�����ݵ�ָ��*/
};

