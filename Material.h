#pragma once
#include"Vector3.h"
class Ray;
class Material {
public:
	virtual bool Scatter(const Ray& input_ray,const HitPoint& hit_point,Ray &out_ray)=0;
};
class LambertMaterial : public Material {
public:
	Vector3 mDiffuse;
	LambertMaterial(const Vector3& diffuse) { mDiffuse = diffuse; }
	bool Scatter(const Ray& input_ray, const HitPoint& hit_point, Ray& out_ray);
};
class MetalMaterial : public Material {
public:
	Vector3 mDiffuse;
	MetalMaterial(const Vector3& diffuse) { mDiffuse = diffuse; }
	bool Scatter(const Ray& input_ray, const HitPoint& hit_point, Ray& out_ray);
};