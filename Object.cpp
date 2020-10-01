#include"Object.h"
#include"Ray.h"
#include"Material.h"
#include<math.h>

Object::Object(Geometry* g, Material* m) {
	mGeometry = g;
	mMaterial = m;
}
void Object::Set(Geometry* g, Material* m) {
	mGeometry = g;
	mMaterial = m;
}
bool Object::HitTest(const Ray& input_ray, float min_distance, float max_distance, HitPoint& hit_point) {
	if (mGeometry->HitTest(input_ray, min_distance, max_distance, hit_point)) {
		hit_point.mMaterial = mMaterial;
		return true;
	}
	return false;
}