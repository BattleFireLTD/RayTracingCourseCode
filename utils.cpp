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
unsigned char* LoadFileContent(const char* path, int& file_size) {
    FILE* file = fopen(path, "rb");
    if (file!=nullptr) {
        fseek(file, 0,SEEK_END);
        file_size = ftell(file);
        if (file_size > 0) {
            rewind(file);
            unsigned char* content = new unsigned char[file_size+1];
            fread(content, 1, file_size, file);
            content[file_size] = 0;
            fclose(file);
            return content;
        }
        fclose(file);
    }
    return nullptr;
}
unsigned char* DecodeBMP(unsigned char* bmp_file_content, int& width, int& height) {
    if (0x4D42 == *((unsigned short*)bmp_file_content)) {
        int pixel_data_offset = *((int*)(bmp_file_content + 10));
        width = *((int*)(bmp_file_content + 18));
        height = *((int*)(bmp_file_content + 22));
        unsigned char * pixel_data = bmp_file_content + pixel_data_offset;
        //bgr->rgb
        for (int i = 0; i < width * height; i++) {
            int pixel_data_start_index = i * 3;
            unsigned char r = pixel_data[pixel_data_start_index+2];
            pixel_data[pixel_data_start_index+2]=pixel_data[pixel_data_start_index];
            pixel_data[pixel_data_start_index] = r;
        }
        return pixel_data;
    }
    return nullptr;
}