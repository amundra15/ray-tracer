
#include <core/scalar.h>
#include <core/random.h>
#include <core/image.h>
#include <rt/renderer.h>
#include <rt/ray.h>
#include <iostream>
#include <rt/cameras/camera.h>
#include <rt/integrators/integrator.h>

#include <omp.h>

namespace rt {

Renderer::Renderer(Camera* cam, Integrator* integrator)
    : cam(cam), integrator(integrator), samples(1)
{}

void Renderer::render(Image& img) {

	const uint height = img.height();
	const uint width = img.width();

	const float two_by_width = 2.0/width;
	const float two_by_height = 2.0/height;

	// #pragma omp parallel for 									//31.81 seconds
	// #pragma omp parallel for collapse(2) schedule(static)		//30.93 seconds
	#pragma omp parallel for collapse(2) schedule(dynamic)		//11.71seconds
	for(uint j = 0; j < height; j++) 
	{
		for(uint i = 0; i < width; i++) 
		{
			RGBColor radiance = RGBColor::rep(0.0f);
			float disp_x, disp_y;
	
			for(int iter = 0; iter < this->samples; iter++)
			{
				if(this->samples == 1)
				{
					disp_x = 0.5f;
					disp_y = 0.5f;
				}
				else
				{
					//super sampling
					disp_x = random();
					disp_y = random();
				}
					
				float x = (two_by_width*(i+disp_x)) - 1.0;
				float y = 1.0- (two_by_height*(j+disp_y));
		
				rt::Ray r = cam->getPrimaryRay(x,y);
				radiance = radiance + integrator->getRadiance(r);
			}
			
			img(i,j) = radiance / this->samples;
			img(i,j) = img(i,j).gamma(1.0f/2.2f);
		}
	}
}

}

rt::RGBColor a1computeColor(rt::uint x, rt::uint y, rt::uint width, rt::uint height);

namespace rt {

void Renderer::test_render1(Image& img) {
	
	uint height = img.height();
	uint width = img.width();

	for(uint y = 0; y < height; y++)
	{
		for(uint x = 0; x < width; x++)
		{
			img(x,y) = a1computeColor(x,y,width,height);
		}
	}

}
}

rt::RGBColor a2computeColor(const rt::Ray& r);

namespace rt {

void Renderer::test_render2(Image& img) {

	uint height = img.height();
	uint width = img.width();

	float two_by_width = 2.0/width;
	float two_by_height = 2.0/height;

	for(uint j = 0; j < height; j++)
	{
		for(uint i = 0; i < width; i++)
		{
			float x = (two_by_width*(i+0.5)) - 1.0;
			float y = 1.0- (two_by_height*(j+0.5));
			rt::Ray r = cam->getPrimaryRay(x,y);
			img(i,j) = a2computeColor(r);
		}
	}

}

}