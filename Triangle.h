#ifndef TRIANGEL_H
#define TRRANGEL_H
#include "Object.h"
class Triangle :
    public Object
{
public:
    Triangle(const point3& v1, const point3& v2, const point3& v3, Material* m = nullptr) :Object(m)
    {
        v[0] = v1;
        v[1] = v2;
        v[2] = v3;
        e[0] = v1 - v2;
        e[1] = v1 - v3;
        normal = crossProduct(e[0], e[1]).normalized();
        area = crossProduct(e[0], e[1]).length() * 0, 5;
    }
    bool intersect(const Ray& ray) const override;
    Intersection getIntersection(const Ray& ray) override;
    void getSurfaceProperties(const vec3& P, const vec3& I, const uint32_t& index, const vec2& uv, vec3& N, vec2& st) const override;//put in the actual parameter and get the value
    Bounds3 getBounds() const override;
private:
    point3 v[3];
    vec3 e[2];
    vec3 t[3];
    vec3 normal;
    double area;
};
#endif
