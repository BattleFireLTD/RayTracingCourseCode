#pragma once
class Vector3 {
public:
	union{
		float v[3];
		struct {
			float x, y, z;
		};
	};
	Vector3() { x = 0.0f; y = 0.0f; z = 0.0f; };
	Vector3(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
	Vector3(const Vector3& v) {
		x = v.x;
		y = v.y;
		z = v.z;
	}
	Vector3 operator*(const Vector3& v)const;//component wise
	Vector3 operator+(const Vector3& v)const;
	void operator*=(float scale);
	Vector3 operator/(float scale)const;
	void operator/=(float scale);
	void operator=(const Vector3& v);
	float operator[](int index) { return v[index]; };
	void Normalize();
	float Magnitude();
};
Vector3 operator*(float f, const Vector3& v);
float Dot(const Vector3& l, const Vector3& r);
