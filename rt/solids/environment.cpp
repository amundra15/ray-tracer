#include <rt/solids/environment.h>

namespace rt {

	Environment::Environment(CoordMapper* texMapper, Material* material){
		this->texMapper = texMapper;
		this->material = material;
	}

	BBox Environment::getBounds() const {
		return BBox::full();
	}

	Intersection Environment::intersect(const Ray& ray, float previousBestDistance) const {
		return Intersection(FLT_MAX, ray, this, ray.d, Point::rep(0.0f));
	}

	Solid::Sample Environment::sample() const {
		/* TODO */ NOT_IMPLEMENTED;
	}

	float Environment::getArea() const {
		return FLT_MAX;
	}

}
