#ifndef OBJECT_H
#define OBJECT_H
#include "vec3.h"
#include "Global.h"
#include "Material.h"
#include "Intersection.h"
#include "Bounds3.h"
#include "Ray.h"
#include "vec2.h"
class Object
{
public:
	Material* material;
	Object() {
		material = new Material();
	}
	Object(Material* m){
		material = m;
	}
	virtual ~Object() {}
	virtual bool intersect(const Ray& ray) const = 0;
	virtual Intersection getIntersection(const Ray& ray) = 0;
	virtual void getSurfaceProperties(const vec3& P, const vec3& I, const uint32_t& index, const vec2& uv, vec3& N, vec2& st) const = 0;//put in the actual parameter and get the value
	virtual Bounds3 getBounds() const = 0;
};
#endif



