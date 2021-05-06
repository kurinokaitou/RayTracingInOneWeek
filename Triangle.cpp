#include "Triangle.h"
bool Triangle::intersect(const Ray& ray) const
{
    return true;
}

Intersection Triangle::getIntersection(const Ray& ray)
{
    Intersection inter;

    if (dotProduct(ray.dir, normal) > 0)
        return inter;
    double uu, vv, t_tmp = 0;
    vec3 pvec = crossProduct(ray.dir, e[1]);
    double det = dotProduct(e[0], pvec);
    if (fabs(det) < EPSILON)
        return inter;

    double det_inv = 1. / det;
    vec3 tvec = ray.ori - v[0];
    uu = dotProduct(tvec, pvec) * det_inv;
    if (uu < 0 || uu > 1)
        return inter;
    vec3 qvec = crossProduct(tvec, e[0]);
    vv = dotProduct(ray.dir, qvec) * det_inv;
    if (vv < 0 || uu + vv > 1)
        return inter;
    t_tmp = dotProduct(e[1], qvec) * det_inv;

    // TODO find ray triangle intersection
    if (t_tmp < 0)
    {
        return inter;
    }
    inter.distance = t_tmp;
    inter.coords = ray(t_tmp);
    inter.happened = true;
    inter.normal = normal;
    inter.object = this;
    inter.object->material = material;
    return inter;
}

void Triangle::getSurfaceProperties(const vec3& P, const vec3& I, const uint32_t& index, const vec2& uv, vec3& N, vec2& st) const
{

}

Bounds3 Triangle::getBounds() const
{
    return Bounds3();
}