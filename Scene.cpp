#include"Scene.h"
#include"utils.h"
#include"Vector3.h"
#include"Camera.h"
#include"Ray.h"
#include"Sphere.h"
#include<Windows.h>
#pragma comment(lib,"winmm.lib")
static int sTotalPixelCount = 0;
static int sViewportWidth = 0, sViewportHeight = 0;
static Camera* sCamera = nullptr;
Sphere sphere(Vector3(0.0f,0.0f,-5.0f),0.5f);
void Init(int width, int height) {
	sTotalPixelCount = width * height;
	sViewportWidth = width;
	sViewportHeight = height;
	sCamera=new Camera(45.0f,float(width)/float(height));
	sCamera->LookAt(Vector3(0.0f,0.0f,0.0f),Vector3(0.0f,0.0f,-1.0f),Vector3(0.0f,1.0f,0.0f));
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
	float u = float(x) / sViewportWidth;
	float v = float(y) / sViewportHeight;
	Ray ray = sCamera->GetRay(u, v);
	HitPoint hit_point;
	if (sphere.HitTest(ray, 0.0f, 100.0f, hit_point)) {
		float rf = hit_point.mNormal.x * 0.5f + 0.5f;
		float gf = hit_point.mNormal.y * 0.5f + 0.5f;
		float bf = hit_point.mNormal.z * 0.5f + 0.5f;
		AByte r = AByte(rf * 255.0f);
		AByte g = AByte(gf * 255.0f);
		AByte b = AByte(bf * 255.0f);
		SetColor(x, y, r, g, b, 255);
	}
	else {
		float rf = ray.mDirection.x > 0.0f ? ray.mDirection.x : -ray.mDirection.x;
		float gf = ray.mDirection.y > 0.0f ? ray.mDirection.y : -ray.mDirection.y;
		float bf = ray.mDirection.z > 0.0f ? ray.mDirection.z : -ray.mDirection.z;
		AByte r = AByte(rf * 255.0f);
		AByte g = AByte(gf * 255.0f);
		AByte b = AByte(bf * 255.0f);
		SetColor(x, y, r, g, b, 255);
	}
}
void Render() {
	static int sCurrentRenderedPixel = 0;
	float current_render_time = 0.0f;
	while (sCurrentRenderedPixel<sTotalPixelCount) {
		RenderOnePixel(sCurrentRenderedPixel);
		sCurrentRenderedPixel++;
		current_render_time += GetEscaptedTime();
		if (current_render_time > 0.016f) {
			break;
		}
	}
}