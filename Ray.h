#ifndef RAY_H
#define RAY_H
#include "vec3.h"
#include <iostream>
class Ray
{
public:
	point3 ori;
	vec3 dir;
	vec3 dirInv;
	std::array<bool, 3> isNeg;
	double t;
	double t_min;
	double t_max;
public:
	Ray(const point3& p, const vec3& d, const double time = 0):ori(p), dir(d),t(time){
		dirInv = vec3(1.0 / d[0], 1.0 / d[1], 1.0 / d[2]);
		isNeg[0] = d[0] < 0;
		isNeg[1] = d[1] < 0;
		isNeg[2] = d[2] < 0;
		t_min = 0.0;
		t_max = std::numeric_limits<double>::max();
	}
	vec3 operator()(double time) const { return ori + dir * time; }
	std::ostream& operator<<(std::ostream& os) {
		os << "origin:" << ori << " " << "dir:" << dir << " " << "time:" << t << std::endl;
		return os;
	}
};
#endif

