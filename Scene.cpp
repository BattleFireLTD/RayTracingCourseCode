#include"Scene.h"
#include"utils.h"
#include"Vector3.h"
#include"Camera.h"
#include"Ray.h"
#include<Windows.h>
#pragma comment(lib,"winmm.lib")
static int sTotalPixelCount = 0;
static int sViewportWidth = 0, sViewportHeight = 0;
void Init(int width, int height) {
	sTotalPixelCount = width * height;
	sViewportWidth = width;
	sViewportHeight = height;
	Vector3 v(1.0f,1.0f,0.0f);
	v.Normalize();
	Vector3 v2 = v;
	Camera camera(45.0f,float(width)/float(height));
	camera.LookAt(Vector3(0.0f,0.0f,1.0f),Vector3(0.0f,0.0f,0.0f),Vector3(0.0f,1.0f,0.0f));
	Ray ray = camera.GetRay(0.5f, 0.5f);
}
float GetEscaptedTime() {
	static unsigned long sTimeSinceComputerStart = 0;
	static unsigned long sLastFrameTime = 0;
	sTimeSinceComputerStart = timeGetTime();
	unsigned long frame_time = sLastFrameTime == 0 ? 0 : sTimeSinceComputerStart - sLastFrameTime;
	sLastFrameTime = sTimeSinceComputerStart;
	return float(frame_time) / 1000.0f;;
}
void RenderOnePixel(int pixel_index) {
	int x = pixel_index % sViewportWidth;
	int y = pixel_index / sViewportWidth;
	SetColor(x, y, 255, 0, 255, 255);
}
void Render() {
	static int sCurrentRenderedPixel = 0;
	float current_render_time = 0.0f;
	while (sCurrentRenderedPixel<sTotalPixelCount) {
		RenderOnePixel(sCurrentRenderedPixel);
		sCurrentRenderedPixel++;
		current_render_time += GetEscaptedTime();
		if (true || current_render_time > 0.0001f) {
			break;
		}
	}
}