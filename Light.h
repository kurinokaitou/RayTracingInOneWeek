#ifndef LIGHT_H
#define LIGHT_H
#include "vec3.h"
class Light
{
public:
	Light():origin(point3(0.0, 0.0, 0.0)),intensity(vec3(1.0, 1.0, 1.0)){}
	Light(const point3 o, const vec3 i):origin(o),intensity(i){}
	virtual ~Light() = default;
	point3 getIntensity() { return intensity; }
	vec3 getOrigin() { return origin; }
private:
	point3 origin;
	vec3 intensity;
};
#endif



