#pragma once
#include<Windows.h>

typedef unsigned int AUint;
typedef unsigned char AByte;
struct RenderableBuffer {
	HDC mDC;
	HBITMAP mBitmap;
	AUint* mColorBuffer;
	int mWidth;
	int mHeight;
	int mPixelCount;
};
void InitRenderableBuffer(HDC dc, int width, int height);
void SetColor(int x,int y,AByte r, AByte g, AByte b, AByte a);
void ASwapBuffers(HDC dc);
float randf();//0.0~1.0
float srandf();//-1.0~1.0