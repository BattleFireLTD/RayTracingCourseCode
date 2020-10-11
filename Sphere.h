#pragma once
#include"Vector3.h"
class Sphere : public Geometry {
public:
	Vector3 mOrigin;
	float mRadius;
	Sphere(const Vector3& origin, float radius);
	void Set(const Vector3& origin, float radius);
	bool HitTest(const Ray& input_ray, float min_distance, float max_distance, HitPoint& hit_point);
	void CalculateTexcoord(const Vector3 & pos_on_sphere,float &u,float &v);
};