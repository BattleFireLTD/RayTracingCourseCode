#include"Material.h"
#include"Ray.h"
#include<math.h>
bool LambertMaterial::Scatter(const Ray& input_ray, const HitPoint& hit_point, Ray& out_ray) {
	Vector3 random_vector = UnitRandomVector3InSphere();
	Vector3 new_direction = hit_point.mNormal + random_vector;
	out_ray.Set(hit_point.mPosition, new_direction, input_ray.mLightAttenuation*mDiffuse);
	return true;
}