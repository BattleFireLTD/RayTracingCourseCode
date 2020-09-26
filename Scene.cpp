#include"Scene.h"
#include"utils.h"
#include"Vector3.h"
#include"Camera.h"
#include"Ray.h"
void Init(int width, int height) {
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; x++) {
			SetColor(x, y, 255, 0, 0, 255);
		}
	}
	Vector3 v(1.0f,1.0f,0.0f);
	v.Normalize();
	Vector3 v2 = v;
	Camera camera(45.0f,float(width)/float(height));
	camera.LookAt(Vector3(0.0f,0.0f,1.0f),Vector3(0.0f,0.0f,0.0f),Vector3(0.0f,1.0f,0.0f));
	Ray ray = camera.GetRay(0.5f, 0.5f);
}
void Render() {

}