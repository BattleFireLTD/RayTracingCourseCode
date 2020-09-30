#pragma once
#include"Vector3.h"
class Ray {
public:
	Vector3 mOrigin, mDirection, mLightAttenuation;
	Ray(const Vector3& origin, const Vector3& direction, const Vector3& attenuation);
	void Set(const Vector3& origin, const Vector3& direction, const Vector3& attenuation);
	Vector3 PointAt(float k) const;
};