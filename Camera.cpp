#include"Camera.h"
#include"Ray.h"
#include<math.h>
Camera::Camera(float fov, float aspect) {
	mFOV = fov;
	mAspect = aspect;
	mNearPlaneWidth = 0.0f;
	mNearPlaneHeight = 0.0f;
}
void Camera::LookAt(const Vector3& position, const Vector3& center, const Vector3& up) {
	Vector3 camera_to_view_point = center - position;
	float distance = camera_to_view_point.Magnitude();
	float half_fov = mFOV / 2.0f;
	float radian_half_fov = half_fov * 3.14159f / 180.0f;
	float half_height = atanf(radian_half_fov)*distance;
	float half_width = half_height * mAspect;
	mNearPlaneWidth = half_width * 2.0f;
	mNearPlaneHeight = half_height * 2.0f;
	camera_to_view_point.Normalize();
	Vector3 right_direction = Cross(camera_to_view_point,up);
	right_direction.Normalize();
	Vector3 up_direction = Cross(right_direction, camera_to_view_point);
	up_direction.Normalize();
	mUVector = right_direction;
	mVVector = up_direction;
	mUSpanVector = mNearPlaneWidth * mUVector;
	mVSpanVector = mNearPlaneHeight * mVVector;
	mCenter = center;
	mPosition = position;
	mUp = up;
}
Ray Camera::GetRay(float u, float v) {
	u = u * 2.0f - 1.0f;
	v = v * 2.0f - 1.0f;
	Vector3 point_on_near_plane = mCenter+0.5f*u*mUSpanVector + 0.5f*v*mVSpanVector;
	return Ray(mPosition,point_on_near_plane-mPosition,Vector3(1.0f,1.0f,1.0f));
}