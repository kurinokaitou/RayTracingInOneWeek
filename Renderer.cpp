#include "Renderer.h"
#include "ConsoleNotifier.h"
void Renderer::addProgress(Progress* p)
{
	m_progressList.push_back(p);
}
void Renderer::removeProgress(Progress* p) 
{
	m_progressList.remove(p);
}

void Renderer::render(const Scene& scene)
{
	ConsoleNotifier cn;
	addProgress(&cn);// add subscribe
	unsigned int width = scene.getWidth();
	unsigned int height = scene.getHeight();
	std::vector<color> frameBuffer(width * height);
	double scale = std::tan(Global::deg2rad(scene.getFov()));
	double aspectRatio = (double)width / (double)height;
	vec3 eyePos = vec3(0.0, 3.0, 0.0);
	int m = 0;
	for (unsigned int j = 0; j < height; j++) {
		for (unsigned int i = 0; i < width; i++) {
			for (unsigned int k = 0; k < SAMPLE_PER_PIXEL; k++) {	// MSAA
				double xoffset = Global::getRamdomDouble(-0.5, 0.5);			
				double yoffset = Global::getRamdomDouble(-0.5, 0.5);
				double x = (2 * ((i + xoffset) + 0.5) / width - 1) * aspectRatio * scale;
				double y = (1 - 2 * ((j + yoffset) + 0.5) / height) * scale;
				vec3 dir = vec3(x, y, -1.0f);
				dir = dir.norm();
				Ray ray(eyePos, dir);
				frameBuffer[m] += scene.castRay(ray, 0) * PIXEL_PER_RAY; // stored in NDC space
			}
			m++;
		}
		onUpdateProgresses(j / (double)height);
	}
	onUpdateProgresses(1.0);
	FILE* fp;
	fopen_s(&fp,"binary.ppm", "wb");
	(void)fprintf_s(fp, "P6\n%d %d\n255\n", width,height);
	for (auto i = 0; i < height * width; ++i) {
		static unsigned char color[3];
		color[0] = (unsigned char)(255 * Global::clamp(0.0, 1.0, frameBuffer[i][0]));
		color[1] = (unsigned char)(255 * Global::clamp(0.0, 1.0, frameBuffer[i][1]));
		color[2] = (unsigned char)(255 * Global::clamp(0.0, 1.0, frameBuffer[i][2]));
		fwrite(color, 1, 3, fp);
	}
	fclose(fp);
}

void Renderer::onUpdateProgresses(double value)
{
	std::list<Progress*>::iterator it = m_progressList.begin();
	while (it != m_progressList.end()) {
		(*it)->updateProgress(value);
		it++;
	}
}