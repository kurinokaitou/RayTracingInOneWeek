#ifndef RENDERER_H
#define RENDERER_H
#include "Scene.h"
#include "Progress.h"
#include <list>
#include <fstream>
#define SAMPLE_PER_PIXEL 8
#define PIXEL_PER_RAY 0.125
class Renderer
{
	std::list<Progress*> m_progressList;
public:
	void render(const Scene& scene);
	void addProgress(Progress* p);
	void removeProgress(Progress* p);
protected:
	virtual void onUpdateProgresses(double value);
};
#endif
