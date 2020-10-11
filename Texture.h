#pragma once
#include"Vector3.h"
class Ray;
class Texture2D {
public:
	virtual Vector3 Sample(float u,float v) = 0;
};
class TextureRGB : public Texture2D {
public:
	unsigned char* mImageFileContent;
	unsigned char* mRGBPixel;
	int mWidth, mHeight;
	TextureRGB();
	~TextureRGB();
	void Set(const char* image_path);
	Vector3 Sample(float u, float v);
};