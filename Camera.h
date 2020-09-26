#pragma once
#include"Vector3.h"
class Ray;
class Camera {
public:
	Vector3 mPosition, mCenter, mUp,mUVector,mVVector,mUSpanVector,mVSpanVector;
	float mFOV, mAspect,mNearPlaneWidth,mNearPlaneHeight;
	Camera(float fov,float aspect);
	void LookAt(const Vector3& position, const Vector3& center, const Vector3& up);
	Ray GetRay(float u,float v);
};