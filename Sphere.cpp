#include"Sphere.h"
#include"Ray.h"
#include<math.h>

Sphere::Sphere(const Vector3& origin, float radius) {
	mOrigin = origin;
	mRadius = radius;
}
void Sphere::Set(const Vector3& origin, float radius) {
	mOrigin = origin;
	mRadius = radius;
}
bool Sphere::HitTest(const Ray& input_ray, float min_distance, float max_distance, HitPoint& hit_point) {
	Vector3 sphere_center_to_ray = input_ray.mOrigin - mOrigin;
	float a = Dot(input_ray.mDirection, input_ray.mDirection);
	float b = 2.0f * Dot(sphere_center_to_ray, input_ray.mDirection);
	float c = Dot(sphere_center_to_ray, sphere_center_to_ray) - mRadius * mRadius;
	float determinant = b * b - 4.0f * a * c;
	bool isHited = false;
	float distance = -1.0f;
	if (determinant > 0.0f) {
		distance = (-b - sqrtf(determinant))/ (2.0f * a);
		if (distance > min_distance && distance < max_distance) {
			isHited = true;
		}
		else {
			distance = (-b + sqrtf(determinant)) / (2.0f * a);
			if (distance > min_distance && distance < max_distance) {
				isHited = true;
			}
		}
	}
	else if (determinant == 0.0f) {
		distance = -b / (2.0f * a);
		if (distance > min_distance && distance < max_distance) {
			isHited = true;
		}
	}
	if (isHited) {
		hit_point.mPosition = input_ray.PointAt(distance);
		Vector3 normal = hit_point.mPosition - mOrigin;
		normal.Normalize();
		hit_point.mDistance = distance;
		hit_point.mNormal = normal;
		CalculateTexcoord(hit_point.mPosition,hit_point.mU, hit_point.mV);
	}
	return isHited;
}
#define PI 3.1415926f
void Sphere::CalculateTexcoord(const Vector3& pos_on_sphere, float& u, float& v) {
	float a = atan2f(pos_on_sphere.z, pos_on_sphere.x);
	float b = asinf(pos_on_sphere.y);
	a = a + PI;
	u = a / (2.0f * PI);
	b = b + PI / 2.0f;
	v = b / PI;
}