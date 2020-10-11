#pragma once
#include"Vector3.h"
class Material;
class LinkedList {
public:
	LinkedList* mNext;
	LinkedList() {
		mNext = nullptr;
	}
	template<typename T>
	T* Next() {
		return (T*)mNext;
	}
	void Append(LinkedList* node) {
		if (mNext == nullptr) {
			mNext = node;
		}
		else {
			mNext->Append(node);
		}
	}
};
class Object : public LinkedList {
public:
	Geometry *mGeometry;
	Material *mMaterial;
	Object(Geometry * g, Material * m);
	void Set(Geometry* g, Material* m);
	bool HitTest(const Ray& input_ray, float min_distance, float max_distance, HitPoint& hit_point);
};