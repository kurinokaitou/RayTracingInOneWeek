#ifndef INTERSECTION_H
#define INTERSECTION_H
#include "Material.h"
#include "vec3.h"
class Object;
class Material;
class Intersection
{
public:
	Intersection()
	{
		object = nullptr;
		coords = vec3();
		normal = vec3();
		distance = std::numeric_limits<double>::max();
		happened = false;
		
	}
	Intersection(Object* obj, vec3 c, vec3 norm, bool h = false){
		object = obj;
		coords = c;
		normal = norm;
		happened = h;
		distance = std::numeric_limits<double>::max();
	}
	bool happened;
	Object* object;
	vec3 coords;
	vec3 normal;
	double distance; //distance between the origin coordinate of ray and the current intersection

};
#endif
