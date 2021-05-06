#include "Renderer.h"
#include "Global.h"
#include "ConsoleNotifier.h"
#include "Sphere.h"
#include "PointLight.h"
#include <chrono>
#include <iostream>
int main()
{
	Material m1(color(1.0, 0.0, 0.0), vec3(0.0, 0.0, 0.0), MaterialType::REFLECTIVE_AND_REFRACTIVE);
	Material m2(color(1.0, 1.0, 1.0), vec3(0.0, 0.0, 0.0));
	Material m3(color(0.0, 0.0, 1.0), vec3(0.0, 0.0, 0.0));
	Material m4(color(1.0, 0.0, 0.0), vec3(0.0, 0.0, 0.0));
	Material m5(color(0.0, 1.0, 0.0), vec3(0.0, 0.0, 0.0));
	Material m6(color(0.0, 1.0, 0.0), vec3(0.0, 0.0, 0.0), MaterialType::DIFFUSE);

	Sphere sphere(point3(0.0,0.0,-20.0), 8.0, &m6);
	Sphere small1(point3(-10.0, 7.0, -14.0), 3.0, &m3);
	Sphere small2(point3(8.0, -2.0, -13.0), 2.0, &m4);
	Sphere small3(point3(-7.0, -2.0, -34.0), 3.0, &m5);
	Sphere earth(point3(0.0, -200008.0, -20.0), 200000.0, &m2);
	PointLight pointLight(point3(-40.0, 60.0, 0.0), vec3(1.0, 1.0, 1.0), 1.0, 0.0014, 0.00007);
	Scene scene = Scene();	//default scene parameter
	scene.addObject(&sphere);
	scene.addObject(&earth);
	scene.addObject(&small1);
	scene.addObject(&small2);
	scene.addObject(&small3);
	scene.addLight(&pointLight);
	Renderer r;

	auto start = std::chrono::system_clock::now();
	r.render(scene);
	auto stop = std::chrono::system_clock::now();

	std::cout << "Render complete: \n";
	std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::hours>(stop - start).count() << " hours\n";
	std::cout << "          : " << std::chrono::duration_cast<std::chrono::minutes>(stop - start).count()%60 << " minutes\n";
	std::cout << "          : " << std::chrono::duration_cast<std::chrono::seconds>(stop - start).count()%60 << " seconds\n";
	return 0;
}