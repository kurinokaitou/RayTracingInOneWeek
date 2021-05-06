#ifndef VEC3_H
#define VEC3_H
#include <cmath>
#include <array>
#include <iostream>
#include "Global.h"
class vec3
{
public:
	friend inline std::ostream& operator<<(std::ostream& out, const vec3& v);
	friend inline vec3 operator+(const vec3& u, const vec3& v);
	friend inline vec3 operator-(const vec3& u, const vec3& v);
	friend inline vec3 operator*(const vec3& u, const vec3& v);
	friend inline vec3 operator*(double t, const vec3& v);
	friend inline vec3 operator*(const vec3& v, double t);
	friend inline vec3 operator/(vec3 v, double t);
	friend inline double dotProduct(const vec3& u, const vec3& v);
	friend inline vec3 crossProduct(const vec3& u, const vec3& v);
	friend inline vec3 bisector(const vec3& u, const vec3& v);
	friend inline vec3 randomVec3();
	friend inline vec3 randomVec3(double min, double max);
	friend inline vec3 ramdomVec3InSphere();

public:
	double e[3];
	vec3() :e{ 0.0, 0.0, 0.0 } {}
	vec3(double x) : e{x,x,x}{}
	vec3(double x,double y,double z):e{x,y,z}{}

	vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
	double operator[](int i) const { return e[i]; }
	double& operator[](int i) { return e[i]; }
	vec3& operator()(const vec3 b) {
		e[0] = b[0];
		e[1] = b[1];
		e[2] = b[2];
		return *this;
	}
	vec3& operator()(const double a) {
		e[0] = a;
		e[1] = a;
		e[2] = a;
	}
	vec3& operator=(const vec3 b) {
		e[0] = b[0];
		e[1] = b[1];
		e[2] = b[2];
		return *this;
	}

	vec3& operator+=(const vec3 b) {
		e[0] += b[0];
		e[1] += b[1];
		e[2] += b[2];
		return *this;
	}
	vec3& operator-=(const vec3 b) {
		e[0] -= b[0];
		e[1] -= b[1];
		e[2] -= b[2];
		return *this;
	}
	vec3& operator*=(const double t) {
		e[0] *= t;
		e[1] *= t;
		e[2] *= t;
		return *this;
	}
	vec3& operator/=(const double t) {
		return *this *= (1 / t);
	}
	double length() const {
		return std::sqrt(lengthSquared());
	}
	double lengthSquared()const {
		return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
	}
	vec3 norm() const {
		if (length() > 0) {
			double lengthInv = 1.0 / length();
			return vec3(e[0] * lengthInv, e[1] * lengthInv, e[2] * lengthInv);
		}
		else
			return *this;
	}
	vec3 normalized() const {
		if (length() > 0) {
			double lengthInv = 1.0 / length();
			vec3 v(e[0] * lengthInv, e[1] * lengthInv, e[2] * lengthInv);
			return v;
		}
		else {
			vec3 v(0.0, 0.0, 0.0);
			return v;
		}
	}
};

inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
	return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3& u, const vec3& v) {
	return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3& u, const vec3& v) {
	return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3& u, const vec3& v) {
	return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(double t, const vec3& v) {
	return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline vec3 operator*(const vec3& v, double t) {
	return t * v;
}

inline vec3 operator/(vec3 v, double t) {
	return (1 / t) * v;
}

inline double dotProduct(const vec3& u, const vec3& v) {
	return u.e[0] * v.e[0]
		+ u.e[1] * v.e[1]
		+ u.e[2] * v.e[2];
}

inline vec3 crossProduct(const vec3& u, const vec3& v) {
	return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
		u.e[2] * v.e[0] - u.e[0] * v.e[2],
		u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 bisector(const vec3& u, const vec3& v) {
	vec3 sumVec = u + v;
	return sumVec / sumVec.length();
}

inline vec3 randomVec3() {
	return vec3(Global::getRamdomDouble(), Global::getRamdomDouble(), Global::getRamdomDouble());
}

inline vec3 randomVec3(double min, double max) {
	return vec3(Global::getRamdomDouble(min, max), Global::getRamdomDouble(min, max), Global::getRamdomDouble(min, max));
}

inline vec3 ramdomVec3InSphere() {
	while (true) {
		vec3 s = randomVec3(-1.0, 1.0);
		if (s.lengthSquared() >= 1.0) continue;
		return s;
	}
}

using point3 = vec3;
using color = vec3;
#endif
