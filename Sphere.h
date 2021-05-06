#ifndef SPHERE_H
#define SPHERE_H
#include "Object.h"
#include "vec3.h"
#include "vec2.h"
class Sphere :
    public Object
{
public:
    Sphere() {
        center = point3(0.0);
        radius = 0.0;
        areaSurface = 0.0;
    }
    Sphere(const point3& c,const double r,Material* m = new Material() ) : Object(m), center(c), radius(r){
        areaSurface = 4.0 * M_PI * radius * radius;
    }
    point3 getCenter() const { return center; }
    double getRadius() const { return radius; }
    double getAreaSurface() const { return areaSurface; }
    bool intersect(const Ray& ray) const override;
    Intersection getIntersection(const Ray& ray) override;
    void getSurfaceProperties(const vec3& P, const vec3& I, const uint32_t& index, const vec2& uv, vec3& N, vec2& st) const override; 
    Bounds3 getBounds() const override;
private:
    point3 center;
    double radius;
    double areaSurface;
};
#endif

