#include <rt/solids/infiniteplane.h>

namespace rt {

InfinitePlane::InfinitePlane(const Point& origin, const Vector& normal, CoordMapper* texMapper, Material* material)
{
    o = origin;
    n = normal;
}

BBox InfinitePlane::getBounds() const {
    /* TODO */ NOT_IMPLEMENTED;
}

Intersection InfinitePlane::intersect(const Ray& ray, float previousBestDistance) const {
	float Nr = dot(this->o-ray.o, n);
	float Dr = dot(ray.d, this->n);

	if(Dr == 0)
	{
		if(Nr == 0)
		{
			//infinte intersections
			// return //TODO_a
		}
	}
	else
	{
		float dist = Nr / Dr;
		if(dist>0 && dist<previousBestDistance)
		{
			Point intersectionPoint = ray.o + (dist*ray.d);
			return Intersection(dist, ray, this, n, intersectionPoint);
		}
	}
	return Intersection::failure();
}

Solid::Sample InfinitePlane::sample() const {
    /* TODO */ NOT_IMPLEMENTED;
}

float InfinitePlane::getArea() const {
    /* TODO */ NOT_IMPLEMENTED;
}

}
