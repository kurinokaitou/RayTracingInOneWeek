#include "Scene.h"
 void Scene::addObject(Object* obj)
{
	objects.push_back(obj);
}
 void Scene::addObjects(std::vector<Object*> objs)
{
	for (auto obj : objs) {
		addObject(obj);
	}
}

void Scene::addLight(Light* light)
{
	lights.push_back(light);
}
void Scene::addLights(std::vector<Light*> lights)
{
	for (auto light : lights) {
		addLight(light);
	}
}

// get the intersection of between ray and current scene build with BVH
Intersection Scene::intersectBVH(const Ray& ray) const
{
	// return this->bvh->getIntersection(ray); 
	return Intersection();
}

// get the intersection of between ray and current scene directyly test with objects
Intersection Scene::intersectObjs(const Ray& ray) const
{
	double minHitDistance = std::numeric_limits<double>::max();
	Intersection minHit = objects.front()->getIntersection(ray);
	for (auto obj : objects) {
		Intersection hit = obj->getIntersection(ray);
		if (hit.distance < minHitDistance) {
			minHitDistance = hit.distance;
			minHit = hit;
		}
	}
	return minHit;
}

// cast ray from the viewport and return the color of ray
color Scene::castRay(const Ray& ray,const int depth) const
{
	if (depth > maxDepth) {
		return color(0.0);
	}
	Intersection interP;
	color hitColor = backGround;	
	interP = intersectObjs(ray);
	uint32_t index = 0;
	vec2 uv = vec2();
	vec2 st = vec2();
	if (interP.happened) {
		Object* obj = interP.object;
		Material* m = obj->material;
		vec3 N = vec3();
		vec3 hitPoint = interP.coords;
		vec3 eyePos = ray.ori;
		interP.object->getSurfaceProperties(hitPoint, ray.dir, index, uv, N, st); // dynamic bonds on multiple objs
		double Ka = m->getKa();
		double Kd = m->getKd();
		double Ks = m->getKs();
		double specularExponent = m->getSpecular();
		double albedo = m->getAlbedo();
		hitColor = vec3();
		vec3 La = vec3();
		vec3 Ld = vec3();
		vec3 Ls = vec3();
		vec3 shadowPointOrig = (dotProduct(ray.dir, N) < 0) ?
			hitPoint + N * EPSILON :
			hitPoint - N * EPSILON;
		vec3 reflectDir;
		vec3 reflectOri;
		vec3 refractDir;
		vec3 refractOri;
		vec3 reflectCol;
		vec3 refractCol;
		vec3 targetDir;
		double kr = fresnel(ray.dir, N, m->getIor());
		switch (interP.object->material->getType())
		{
			case MaterialType::DIFFUSE:
				targetDir = hitPoint + N + ramdomVec3InSphere() - hitPoint; // select a random direction from the hitting poing;
				hitColor = albedo * castRay(Ray(hitPoint, targetDir.normalized()), depth + 1);
				break;
			case MaterialType::REFLECTIVE_AND_REFRACTIVE:
				reflectDir = reflect(ray.dir, N);
				reflectOri = (dotProduct(reflectDir, N) < 0) ? hitPoint - N * EPSILON : hitPoint + N * EPSILON;
				refractDir = refract(ray.dir, N, m->getIor());
				refractOri = (dotProduct(refractDir, N) < 0) ? hitPoint - N * EPSILON : hitPoint + N * EPSILON;
				reflectCol = castRay(Ray(reflectOri, reflectDir), depth + 1)*0.90;
				refractCol = castRay(Ray(refractOri, refractDir), depth + 1)*0.90;
				hitColor = kr * reflectCol + (1 - kr) * refractCol;
				break;
			case MaterialType::REFLECTIVE:
				reflectDir = reflect(ray.dir, N);
				reflectOri = (dotProduct(reflectDir, N) < 0) ? hitPoint - N * EPSILON : hitPoint + N * EPSILON;
				hitColor = castRay(Ray(reflectOri, reflectDir), depth + 1) * (1 - kr);
				break;
			default:		// add a blinn-Phoneg lighting model for the sphere
				//hitColor = color(N/2.0 + vec3(0.5));			//check for normal
				for (int i = 0; i < getLightNum(); i++) {
					auto light = dynamic_cast<PointLight*>(getLights()[i]);
					vec3 intensity = light->getIntensity();
					vec3 pos = light->getOrigin();
					vec3 lightDir = pos - hitPoint;
					vec3 viewDir = eyePos - hitPoint;
					double lightDis2 = lightDir.lengthSquared();
					double lightDis = lightDir.length();
					lightDir = lightDir.normalized();
					viewDir = viewDir.normalized();
					vec3 half = bisector(lightDir, viewDir).normalized();
					bool isInShadow = intersectObjs(Ray(shadowPointOrig, lightDir)).happened;
					La = Ka * intensity;
					double angleCos = std::max(0.0, dotProduct(N, lightDir));
					Ld = Kd * intensity * std::max(0.0, dotProduct(N,lightDir));
					Ls = Ks * intensity * std::pow(std::max(0.0,dotProduct(N,half)), specularExponent);
					double attenuation = 1.0 / (light->Kc + light->Kl * lightDis + light->Kq * lightDis2);

					hitColor +=  attenuation * (La + (Ld + Ls)* (1 - isInShadow)) * obj->material->getBaseColor();
				}
				break;
		}
	}
	return hitColor;
}

vec3 Scene::reflect(const vec3& in, const vec3& N) const 
{
	return in - 2 * dotProduct(in, N) * N;
}

double Scene::fresnel(const vec3& I, const vec3& N, const double& ior) const
{
	double kr;
	double cosi = Global::clamp(-1, 1, dotProduct(I, N));
	double etai = 1, etat = ior;
	if (cosi > 0) { std::swap(etai, etat); }
	// Compute sini using Snell's law
	double sint = etai / etat * sqrtf(std::max(0.0, 1 - cosi * cosi));
	// Total internal reflection
	if (sint >= 1) {
		kr = 1;
	}
	else {
		double cost = sqrtf(std::max(0.0, 1 - sint * sint));
		cosi = fabsf(cosi);
		double Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost));
		double Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost));
		kr = (Rs * Rs + Rp * Rp) / 2;
	}
	// As a consequence of the conservation of energy, transmittance is given by:
	// kt = 1 - kr;
	return kr;
}

vec3 Scene::refract(const vec3& in, const vec3& N, double ior) const
{
	double cosi = Global::clamp(-1, 1, dotProduct(in, N));
	double etai = 1.0, etat = ior;
	vec3 n = N;
	if (cosi < 0) { cosi = -cosi; }
	else { std::swap(etai, etat); n = -N; }
	double eta = etai / etat;
	double k = 1 - eta * eta * (1 - cosi * cosi);
	return k < 0 ? 0 : eta * in + (eta * cosi - std::sqrt(k)) * n;
}