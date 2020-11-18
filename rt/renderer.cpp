#include <core/scalar.h>
#include <core/image.h>
#include <rt/renderer.h>
#include <rt/ray.h>
#include <iostream>
#include <rt/cameras/camera.h>		//Added by Akshay

namespace rt {

Renderer::Renderer(Camera* cam, Integrator* integrator)
    : cam(cam), integrator(integrator), samples(1)
{}

void Renderer::render(Image& img) {
    /* TODO */ NOT_IMPLEMENTED;
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
