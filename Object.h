#pragma once
#include"Vector3.h"
class Material;
class Object {
public:
	Geometry *mGeometry;
	Material *mMaterial;
	Object(Geometry * g, Material * m);
	void Set(Geometry* g, Material* m);
	bool HitTest(const Ray& input_ray, float min_distance, float max_distance, HitPoint& hit_point);
};