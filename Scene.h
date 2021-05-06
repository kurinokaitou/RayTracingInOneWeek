#ifndef SCENE_H
#define SCENE_H
#include <vector>
#include "Object.h"
#include "Ray.h"
#include "Intersection.h"
#include "Light.h"
#include "PointLight.h"
#include "Global.h"
class Scene
{
public:
	Scene() = default;
	Scene(int w, int h, double f, color c, int d):
		width(w), height(h),fov(f), backGround(c),maxDepth(d){}
	void addObject(Object* obj);
	void addObjects(std::vector<Object*> objs);
	int getObjNums() const { return objects.size(); }
	const std::vector<Object*>& getObjects() const { return objects; }
	void addLight(Light* light);
	void addLights(std::vector<Light*> lights);
	int getLightNum() const { return lights.size(); }
	const std::vector<Light*>& getLights() const { return lights; }
	color castRay(const Ray& ray, int depth) const;
	Intersection intersectBVH(const Ray& ray) const;
	Intersection intersectObjs(const Ray& ray) const;
	int getWidth() const { return width; }
	int getHeight() const { return height; }
	double getFov() const { return fov; }
	vec3 reflect(const vec3& in, const vec3& N) const;
	vec3 refract(const vec3& in, const vec3& N, double ior) const;
	double fresnel(const vec3& I, const vec3& N, const double& ior) const;
private:
	int width = 1280;
	int height = 960;
	double fov = 40;
	color backGround = vec3(0.6);
	int maxDepth = 20;
	std::vector<Object*> objects;
	std::vector<Light*> lights;
};
#endif
