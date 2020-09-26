#include"Scene.h"
#include"utils.h"
void Init(int width, int height) {
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; x++) {
			SetColor(x, y, 255, 0, 0, 255);
		}
	}
}
void Render() {

}