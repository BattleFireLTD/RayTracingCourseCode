#pragma once
#include"Vector3.h"
class Ray;
class Texture2D;
class Material {
public:
	virtual bool Scatter(const Ray& input_ray,const HitPoint& hit_point,Ray &out_ray)=0;
	virtual Vector3 Emmit(const HitPoint& hit_point) {
		return Vector3(0.0f,0.0f,0.0f);
	}
};
class LambertMaterial : public Material {
public:
	Texture2D *mDiffuseTexture;
	LambertMaterial(Texture2D* diffuse) { mDiffuseTexture = diffuse; }
	bool Scatter(const Ray& input_ray, const HitPoint& hit_point, Ray& out_ray);
};
class MetalMaterial : public Material {
public:
	Texture2D* mDiffuseTexture;
	MetalMaterial(Texture2D* diffuse) { mDiffuseTexture = diffuse; }
	bool Scatter(const Ray& input_ray, const HitPoint& hit_point, Ray& out_ray);
};
class LightMaterial : public Material {
public:
	Texture2D* mDiffuseTexture;
	float mIntensity;
	LightMaterial(Texture2D* diffuse) { mDiffuseTexture = diffuse; mIntensity = 1.0f; }
	bool Scatter(const Ray& input_ray, const HitPoint& hit_point, Ray& out_ray) {
		return false;
	}
	Vector3 Emmit(const HitPoint& hit_point);
};