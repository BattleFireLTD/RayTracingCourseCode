#include"Ray.h"
Ray::Ray(const Vector3& origin, const Vector3& direction, const Vector3& attenuation) {
	Set(origin, direction, attenuation);
}
void Ray::Set(const Vector3& origin, const Vector3& direction, const Vector3& attenuation) {
	mOrigin = origin;
	mDirection = direction;
	mDirection.Normalize();
	mLightAttenuation = attenuation;
}
Vector3 Ray::PointAt(float k) const {
	return mOrigin + k * mDirection;
}