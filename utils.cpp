#include"utils.h"
#include<functional>
static RenderableBuffer* sRenderableBuffer=nullptr;
void InitRenderableBuffer(HDC dc, int width, int height) {
    sRenderableBuffer = new RenderableBuffer;
    sRenderableBuffer->mDC = CreateCompatibleDC(dc);
    BITMAPINFO bitmapinfo = {};
    bitmapinfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bitmapinfo.bmiHeader.biPlanes = 1;
    bitmapinfo.bmiHeader.biBitCount = 32;
    bitmapinfo.bmiHeader.biCompression = BI_RGB;
    bitmapinfo.bmiHeader.biWidth = width;
    bitmapinfo.bmiHeader.biHeight = height;
    sRenderableBuffer->mBitmap = CreateDIBSection(sRenderableBuffer->mDC, &bitmapinfo, DIB_RGB_COLORS, (void**)&sRenderableBuffer->mColorBuffer, 0, 0);
    SelectObject(sRenderableBuffer->mDC, sRenderableBuffer->mBitmap);
    sRenderableBuffer->mWidth = width;
    sRenderableBuffer->mHeight = height;
    sRenderableBuffer->mPixelCount = width * height;
}
void SetColor(int x, int y, AByte r, AByte g, AByte b, AByte a) {
    AUint color=(a << 24) + (r << 16) + (g << 8) + b;
    int pixel_index = y * sRenderableBuffer->mWidth + x;
    if (pixel_index < sRenderableBuffer->mPixelCount) {
        sRenderableBuffer->mColorBuffer[pixel_index] = color;
    }
}
void ASwapBuffers(HDC dc) {
	BitBlt(dc, 0, 0, sRenderableBuffer->mWidth, sRenderableBuffer->mHeight, sRenderableBuffer->mDC, 0, 0, SRCCOPY);
}
float randf() {
    return float(rand()) / float(RAND_MAX);//0.0~1.0
}
float srandf() {
    return randf() * 2.0f - 1.0f;//-1.0~1.0
}