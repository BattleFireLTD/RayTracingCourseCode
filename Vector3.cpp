#include"Vector3.h"
#include<math.h>
#include"utils.h"
Vector3 Vector3::operator*(const Vector3& v)const {
	return Vector3(x*v.x,y*v.y,z*v.z);
}
Vector3 Vector3::operator+(const Vector3& v)const {
	return Vector3(x + v.x, y + v.y, z + v.z);
}
Vector3 Vector3::operator-(const Vector3& v)const {
	return Vector3(x - v.x, y - v.y, z - v.z);
}
void Vector3::operator*=(float scale) {
	x *= scale;
	y *= scale;
	z *= scale;
}
Vector3 Vector3::operator/(float scale)const {
	return Vector3(x/scale,y/scale,z/scale);
}
void Vector3::operator/=(float scale) {
	x /= scale;
	y /= scale;
	z /= scale;
}
void Vector3::operator=(const Vector3& v) {
	x = v.x;
	y = v.y;
	z = v.z;
}
float Vector3::Magnitude() {
	return sqrtf(x*x+y*y+z*z);
}
void Vector3::Normalize() {
	float magnitude = Magnitude();
	x /= magnitude;
	y /= magnitude;
	z /= magnitude;
}
Vector3 operator*(float f, const Vector3& v) {
	return Vector3(f * v.x, f * v.y, f * v.z);
}
float Dot(const Vector3& l, const Vector3& r) {
	return l.x * r.x + l.y * r.y + l.z * r.z;
}
Vector3 Cross(const Vector3& l, const Vector3& r) {
	return Vector3(l.y*r.z-l.z*r.y,l.z*r.x-l.x*r.z,l.x*r.y-l.y*r.x);
}
Vector3 Reflect(const Vector3& v, const Vector3& n) {
	return v - 2.0f * (Dot(v, n) * n);
}
Vector3 UnitRandomVector3InSphere() {
	Vector3 random_vector(srandf(),srandf(),srandf());
	random_vector.Normalize();
	return random_vector;
}