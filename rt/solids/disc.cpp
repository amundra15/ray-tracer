#include <rt/solids/disc.h>

namespace rt {

Disc::Disc(const Point& center, const Vector& normal, float radius, CoordMapper* texMapper, Material* material)
{
    c = center;
    n = normal.normalize();
    r = radius;
}

BBox Disc::getBounds() const {
    /* TODO */ NOT_IMPLEMENTED;
}

Intersection Disc::intersect(const Ray& ray, float previousBestDistance) const {
	
	//intersect with the plane
	float Nr = dot(c-ray.o, n);
	float Dr = dot(ray.d, n);

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
			//disc condition
			if(dot(intersectionPoint-c,intersectionPoint-c) < r*r)
				return Intersection(dist, ray, this, n, intersectionPoint);
		}

	}
	return Intersection::failure();
}

Solid::Sample Disc::sample() const {
    NOT_IMPLEMENTED;
}

float Disc::getArea() const {
	float area = pi*r*r;
	return area;
}

}
