#include"Material.h"
#include"Ray.h"
#include"Texture.h"
#include<math.h>
bool LambertMaterial::Scatter(const Ray& input_ray, const HitPoint& hit_point, Ray& out_ray) {
	Vector3 random_vector = UnitRandomVector3InSphere();
	Vector3 new_direction = hit_point.mNormal + random_vector;
	out_ray.Set(hit_point.mPosition, new_direction, 
		input_ray.mLightAttenuation* mDiffuseTexture->Sample(hit_point.mU,hit_point.mV));
	return true;
}
bool MetalMaterial::Scatter(const Ray& input_ray, const HitPoint& hit_point, Ray& out_ray) {
	Vector3 new_direction = Reflect(input_ray.mDirection,hit_point.mNormal);
	out_ray.Set(hit_point.mPosition, new_direction, 
		input_ray.mLightAttenuation *mDiffuseTexture->Sample(hit_point.mU, hit_point.mV));
	return true;
}
Vector3 LightMaterial::Emmit(const HitPoint& hit_point) {
	return mIntensity * mDiffuseTexture->Sample(hit_point.mU, hit_point.mV);
}