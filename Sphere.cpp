#include "Sphere.h"
// judge whether the ray intersect with the sphere.
bool Sphere::intersect(const Ray& ray) const 
{
	vec3 oc = ray.ori - center;
	double a = dotProduct(ray.dir, ray.dir);
	double b = 2.0 * dotProduct(ray.dir, oc);
	double c = dotProduct(oc, oc) - radius * radius;
	double discrimination = b * b - 4.0 * a * c;
	return (discrimination > 0);
}

//get the current sphere surface properties on the intersection point P.
void Sphere::getSurfaceProperties(const vec3& P, const vec3& I, const uint32_t& index, const vec2&  uv, vec3& N, vec2& st) const
{
	vec3 normdir = P - center;
	N = normdir.normalized();
}

// judge whether a ray intersect with the sphere and return the intersection
Intersection Sphere::getIntersection(const Ray& ray)
{
    Intersection result;
    result.happened = false;
    vec3 L = ray.ori - center;
    double a = dotProduct(ray.dir, ray.dir);
    double b = 2 * dotProduct(ray.dir, L);
    double c = dotProduct(L, L) - radius * radius;
    double t0, t1;
    if (!Global::solveQuadratic(a, b, c, t0, t1)) return result;
    if (t0 < 0) t0 = t1;
    if (t0 < 0) return result;
    result.happened = true;
    result.coords = vec3(ray.ori + ray.dir * t0);
    result.normal = vec3(result.coords - center).normalized();
    result.object = this;
    result.distance = t0;
    return result;
}

//get the bounding box of the sphere
Bounds3 Sphere::getBounds() const
{
	return Bounds3(
		vec3(center + vec3(radius)),
		vec3(center - vec3(radius))
	);
}