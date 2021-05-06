#ifndef BOUNDS3_H
#define BOUNDS3_H
#include "vec3.h"
#include "Ray.h"
#include <limits>
enum maxExtended
{
	X_AXIS,
	Y_AXIS,
	Z_AXIS
};

class Bounds3
{
public:
	friend inline Bounds3 Intersect(const Bounds3& a, const Bounds3& b);
	friend inline Bounds3 Union(const Bounds3& a, const Bounds3& b);
	friend inline Bounds3 Union(const Bounds3& a, const vec3& v);
public:
	point3 pmax;
	point3 pmin;
	Bounds3() {
		constexpr double nmax = std::numeric_limits<double>::max();
		constexpr double nmin = std::numeric_limits<double>::lowest();
		pmax = point3(nmax);
		pmin = point3(nmin);
	}
	Bounds3(const vec3& v) {
		pmax(v);
		pmin(v);
	}
	Bounds3(const vec3& v1, const vec3& v2) {
		pmax = vec3(std::max(v1[0], v2[0]), std::max(v1[1], v2[1]), std::max(v1[2], v2[2]));
		pmin = vec3(std::min(v1[0], v2[0]), std::min(v1[1], v2[1]), std::min(v1[2], v2[2]));
	}
	vec3 diagnol() const { return pmax - pmin; }
	int maxExtend() const {
		vec3 d = diagnol();
		if (d[0] > d[1] && d[0] > d[2]) {
			return X_AXIS;
		}
		else if(d[1] > d[2]){
			return Y_AXIS;
		}
		else {
			return Z_AXIS;
		}
	}
	double surfaceArea() const {
		vec3 d = diagnol();
		return 2 * (d[0] * d[1] + d[0] * d[2] * d[1] * d[2]);
	}
	vec3 centroid() const {
		return 0.5 * pmin + 0.5 * pmax;
	}
	bool intersectRay (const Ray& ray) const;
	
};

inline bool Bounds3::intersectRay(const Ray& ray) const
{
	std::array<bool, 3> isNeg(ray.isNeg);
	double tx_min = (pmin[0] - ray.ori[0]) * ray.dirInv[0];
	double tx_max = (pmax[0] - ray.ori[0]) * ray.dirInv[0];

	double ty_min = (pmin[1] - ray.ori[1]) * ray.dirInv[1];
	double ty_max = (pmax[1] - ray.ori[1]) * ray.dirInv[1];

	double tz_min = (pmin[2] - ray.ori[2]) * ray.dirInv[2];
	double tz_max = (pmax[2] - ray.ori[2]) * ray.dirInv[2];

	if (!isNeg[0]) {
		std::swap(tx_max, tx_min);
	}
	if (!isNeg[1]) {
		std::swap(ty_max, ty_min);
	}
	if (!isNeg[2]) {
		std::swap(tz_max, tz_min);
	}
	double t_enter = std::max(tx_min, std::max(ty_min, tz_min));
	double t_exit = std::min(tx_max, std::min(ty_max, tz_max));
	if (t_enter < t_exit && t_exit >= 0.0) return true;
	else return false;
}

inline Bounds3 Intersect(const Bounds3& a, const Bounds3& b)
{
	Bounds3 intersection;
	point3 npmin(fmax(a.pmin[0], b.pmin[0]), fmax(a.pmin[1], b.pmin[1]), fmax(a.pmin[2], b.pmin[2]));
	point3 npmax(fmin(a.pmax[0], b.pmax[0]), fmin(a.pmax[1], b.pmax[1]), fmin(a.pmax[2], b.pmax[2]));
	return Bounds3(npmin, npmax);
}

inline Bounds3 Union(const Bounds3& a, const Bounds3& b)
{
	Bounds3 unioned;
	point3 npmin(fmin(a.pmin[0], b.pmin[0]), fmin(a.pmin[1], b.pmin[1]), fmin(a.pmin[2], b.pmin[2]));
	point3 npmax(fmax(a.pmax[0], b.pmax[0]), fmax(a.pmax[1], b.pmax[1]), fmax(a.pmax[2], b.pmax[2]));
	return Bounds3(npmin, npmax);
}

inline Bounds3 Union(const Bounds3& a, const vec3& v)
{
	Bounds3 unioned;
	point3 npmin(fmin(a.pmin[0], v[0]), fmin(a.pmin[1], v[1]), fmin(a.pmin[2], v[2]));
	point3 npmax(fmax(a.pmax[0], v[0]), fmax(a.pmax[1], v[1]), fmax(a.pmax[2], v[2]));
	return Bounds3(npmin, npmax);
}

inline bool isOverlap(const Bounds3& a, const Bounds3& b) 
{
	bool x = (a.pmax[0] >= b.pmin[0]) && (a.pmin[0] <= b.pmax[0]);
	bool y = (a.pmax[1] >= b.pmin[1]) && (a.pmin[1] <= b.pmax[1]);
	bool z = (a.pmax[2] >= b.pmin[2]) && (a.pmin[2] <= b.pmax[2]);
	return (x && y && z);
}

#endif
