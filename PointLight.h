#ifndef POINTLIGHT_H
#define POINTLIGHT_H
#include "Light.h"
class PointLight :
    public Light
{
public:
    PointLight(const point3 o,const vec3 i, const double c,const double l,const double q):Light(o,i),Kc(c),Kl(l),Kq(q){}
    double Kc;
    double Kl;
    double Kq;
};
#endif

