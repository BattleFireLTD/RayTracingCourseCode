#include"Scene.h"
#include"utils.h"
#include"Vector3.h"
#include"Camera.h"
#include"Ray.h"
#include"Material.h"
#include"Object.h"
#include"Sphere.h"
#include<Windows.h>
#pragma comment(lib,"winmm.lib")
static int sTotalPixelCount = 0;
static int sViewportWidth = 0, sViewportHeight = 0;
static Camera* sCamera = nullptr;
Sphere sphere(Vector3(0.0f,0.5f,0.0f),0.5f);
static Object* sRootObject = nullptr;
static Material* lambert = nullptr;
static int sSampleCount = 16;
static int sMaxBounceTime = 30;
void AddObject(Object* object) {
	if (sRootObject == nullptr) {
		sRootObject = object;
	}
	else {
		//link to linked list
		sRootObject->Append(object);
	}
}
void Init(int width, int height) {
	sTotalPixelCount = width * height;
	sViewportWidth = width;
	sViewportHeight = height;
	sCamera=new Camera(45.0f,float(width)/float(height));
	sCamera->LookAt(Vector3(3.0f,1.0f,3.0f),Vector3(0.0f,0.0f,0.0f),Vector3(0.0f,1.0f,0.0f));
	lambert = new LambertMaterial(Vector3(0.1f, 0.4f, 0.7f));
	Material* earth_material = new LambertMaterial(Vector3(0.5f,0.3f,0.1f));
	Material* metal_material = new MetalMaterial(Vector3(0.9f,0.9f,0.9f));
	AddObject(new Object(new Sphere(Vector3(0.0f,-1000.0f,0.0f),1000.0f),earth_material));
	AddObject(new Object(&sphere, lambert));
	AddObject(new Object(new Sphere(Vector3(-1.0f,0.5f, 0.3f), 0.5f), metal_material));
}
float GetEscaptedTime() {
	static unsigned long sTimeSinceComputerStart = 0;
	static unsigned long sLastFrameTime = 0;
	sTimeSinceComputerStart = timeGetTime();
	unsigned long frame_time = sLastFrameTime == 0 ? 0 : sTimeSinceComputerStart - sLastFrameTime;
	sLastFrameTime = sTimeSinceComputerStart;
	return float(frame_time) / 1000.0f;;
}
Vector3 GetEnviromentColor(const Ray& input_ray) {
	Vector3 bottom_color(1.0f,1.0f,1.0f);
	Vector3 top_color(0.5f, 0.7f, 1.0f);
	float factor = 0.5f*input_ray.mDirection.y+0.5f;
	return factor * top_color + (1.0f - factor) * bottom_color;
}
Vector3 RenderOneSample(Ray& input_ray,int bounce_time) {
	HitPoint hit_point;
	float max_distance = 1000.0f;
	Object* current_object = sRootObject;
	Object* hitted_object = nullptr;
	while (current_object != nullptr) {
		if (current_object->HitTest(input_ray, 0.01f, max_distance, hit_point)) {
			max_distance = hit_point.mDistance;
			hitted_object = current_object;
		}
		current_object = current_object->Next<Object>();
	}
	if (hitted_object != nullptr) {
		if (bounce_time < sMaxBounceTime) {
			Ray scatter_ray;
			if (hit_point.mMaterial->Scatter(input_ray, hit_point, scatter_ray)) {
				return RenderOneSample(scatter_ray,bounce_time+1);
			}
		}
		return Vector3(0.0f,0.0f,0.0f);
	}
	return GetEnviromentColor(input_ray) * input_ray.mLightAttenuation;
} 
void RenderOnePixel(int pixel_index) {
	int x = pixel_index % sViewportWidth;
	int y = pixel_index / sViewportWidth;
	Vector3 color;
	for (int i = 0; i < sSampleCount; ++i) {
		float offset_u = srandf() * 0.5f;
		float offset_v = srandf() * 0.5f;
		float u = (float(x) + offset_u) / sViewportWidth;//0.0~1.0
		float v = (float(y) + offset_v) / sViewportHeight;//0.0~1.0
		Ray ray = sCamera->GetRay(u, v);
		Vector3 current_color = RenderOneSample(ray,0);
		color = color + current_color;
	}
	color /= float(sSampleCount);
	AByte r = AByte(color.x * 255.0f); 
	AByte g = AByte(color.y * 255.0f); 
	AByte b = AByte(color.z * 255.0f); 
	SetColor(x, y, r, g, b, 255); 
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