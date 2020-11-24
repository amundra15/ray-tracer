#include <rt/solids/infiniteplane.h>

namespace rt {

InfinitePlane::InfinitePlane(const Point& origin, const Vector& normal, CoordMapper* texMapper, Material* material)
{
    o = origin;
    n = normal.normalize();
}

BBox InfinitePlane::getBounds() const {
    /* TODO */ NOT_IMPLEMENTED;
}

Intersection InfinitePlane::intersect(const Ray& ray, float previousBestDistance) const {
	
	//intersection with a plane happens when p satisfies: (p-p0).n = 0 and p = origin+t*direction
	//substituting p, you get t = {(p0-origin).n}/direction.n
	float Nr = dot(this->o-ray.o, n);	//numerator
	float Dr = dot(ray.d, this->n);		//denominator

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
