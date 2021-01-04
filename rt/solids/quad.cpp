#include <rt/solids/quad.h>
#include <core/random.h>

namespace rt {

Quad::Quad(const Point& origin, const Vector& span1, const Vector& span2, CoordMapper* texMapper, Material* material)
{
    this->origin = origin;
	this->span1 = span1;
	this->span2 = span2;
	this->n = cross(span1, span2).normalize();

	this->bbox = BBox(min(origin, origin+span1+span2), max(origin, origin+span1+span2));

	this->material = material;
	this->texMapper = texMapper;
}

BBox Quad::getBounds() const {
	return bbox;
}

Intersection Quad::intersect(const Ray& ray, float previousBestDistance) const {

	//edge projection
	Vector pvec = cross(ray.d, span2);
	float det = dot(span1, pvec);

	//reject intersection if parallel to the plane
	if(fabs(det) <= epsilon)
		return Intersection::failure();

	const Vector tvec = ray.o - origin;
	const Vector qvec = cross(tvec, span1);

	const float u = dot(tvec, pvec) / det;
	const float v = dot(ray.d, qvec) / det;
	//no w as in triangle

	//these are not barycentric coordinates, but each of them has to be >=0 and <=1
	if(u < -epsilon || v < -epsilon || u > 1.0f + epsilon || v > 1.0f + epsilon)
		return Intersection::failure();

	const float dist = dot(span2, qvec) / det;

	//if all solutions are behind the ray, return failure
	if(dist < epsilon)
		return Intersection::failure();		

	//if found solution is better than previousBestDistance, use it, else return failure
	if(dist < previousBestDistance)
		return Intersection(dist, ray, this, n, Point(u,v,0));

	//nothing found -> return failure
	return Intersection::failure();
}

Solid::Sample Quad::sample() const {
	float eps1 = rt::random();
	float eps2 = rt::random();

	struct Sample s = {origin + eps1*span1 + eps2*span2, n};
	return s;
}

float Quad::getArea() const {
	float area = cross(span1,span2).length();
    return area;
}

}


//credit: intersection code taken from Omercan Yazici's tutorial presentaion.