#include <rt/solids/environment.h>

namespace rt {

	Environment::Environment(CoordMapper* texMapper, Material* material){
		this->texMapper = texMapper;
		this->material = material;
	}

	BBox Environment::getBounds() const {
		return BBox::full();
	}

	Intersection Environment::intersect(const Ray& ray, float previousBestDistance) const 
	{	
		return Intersection(FLT_MAX, ray, this, -ray.d, Point::rep(0.0f));

		//Note: playing around with the normal vector direction here can give different projections (persp, cylindrical, spherical) on the final projected image - see the corr reference file
	}

	Solid::Sample Environment::sample() const {
		/* TODO */ NOT_IMPLEMENTED;
	}

	float Environment::getArea() const {
		return FLT_MAX;
	}

}
