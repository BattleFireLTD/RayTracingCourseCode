#pragma once
#include"Vector3.h"
class Ray;
class Texture2D;
class Material {
public:
	virtual bool Scatter(const Ray& input_ray,const HitPoint& hit_point,Ray &out_ray)=0;
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