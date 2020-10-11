#include"Texture.h"
#include"utils.h"
TextureRGB::TextureRGB() {
	mImageFileContent = nullptr;
	mRGBPixel = nullptr;
	mWidth = 0;
	mHeight = 0;
}
TextureRGB::~TextureRGB() {
	if (mImageFileContent != nullptr) {
		delete[] mImageFileContent;
	}
}
void TextureRGB::Set(const char* image_path) {
	int file_size = 0;
	mImageFileContent = LoadFileContent(image_path, file_size);
	mRGBPixel = DecodeBMP(mImageFileContent, mWidth, mHeight);
}
Vector3 TextureRGB::Sample(float u, float v) {
	int x = int(u * mWidth);
	int y = int(v * mHeight);
	x = x < 0 ? 0 : x;
	y = y < 0 ? 0 : y;
	x = x > (mWidth - 1) ? (mWidth - 1) : x;
	y = y > (mHeight - 1) ? (mHeight - 1) : y;
	int pixel_data_start_index = 3*(x + y * mWidth);
	float r = float(mRGBPixel[pixel_data_start_index]) / 255.0f;
	float g = float(mRGBPixel[pixel_data_start_index+1]) / 255.0f;
	float b = float(mRGBPixel[pixel_data_start_index+2]) / 255.0f;
	return Vector3(r,g,b);
}
