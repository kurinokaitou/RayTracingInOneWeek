#ifndef VEC2_H
#define VEC2_H
class vec2
{
public:
    vec2() : e{0.0,0.0} {}
    vec2(double a) : e{ a, a } {}
    vec2(double a, double b) :e{ a, b } {}
    vec2 operator * (const double& r) const { return vec2(e[0] * r, e[1] * r); }
    vec2 operator + (const vec2& v) const { return vec2(e[0] + v.e[0], e[0] + v.e[0]); }
    double e[2];
};
#endif
