#include"Scene.h"
#include"utils.h"
#include"Vector3.h"
void Init(int width, int height) {
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; x++) {
			SetColor(x, y, 255, 0, 0, 255);
		}
	}
	Vector3 v(1.0f,1.0f,0.0f);
	v.Normalize();
	Vector3 v2 = v;
}
void Render() {

}