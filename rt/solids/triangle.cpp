#include <rt/solids/triangle.h>
#include <core/random.h>

namespace rt {

Triangle::Triangle(Point vertices[3], CoordMapper* texMapper, Material* material)
{
    this->v1 = vertices[0];
	this->v2 = vertices[1];
	this->v3 = vertices[2];
	
	n = cross(v2-v1, v3-v1).normalize();

    Point min_point = rt::min(rt::min(this->v1, this->v2), this->v3);
	Point max_point = rt::max(rt::max(this->v1, this->v2), this->v3);
	this->bbox = BBox(min_point, max_point);

	this->material = material;
	this->texMapper = texMapper;
}

Triangle::Triangle(const Point& v1, const Point& v2, const Point& v3, CoordMapper* texMapper, Material* material)
{
    this->v1 = v1;
	this->v2 = v2;
	this->v3 = v3;
    
	n = cross(v2-v1, v3-v1).normalize();

    Point min_point = rt::min(rt::min(this->v1, this->v2), this->v3);
	Point max_point = rt::max(rt::max(this->v1, this->v2), this->v3);
	this->bbox = BBox(min_point, max_point);
	
	this->material = material;
	this->texMapper = texMapper;
}

BBox Triangle::getBounds() const {
	return bbox;
}

Intersection Triangle::intersect(const Ray& ray, float previousBestDistance) const {

	//edges
	const Vector e1 = v1 - v3;
	const Vector e2 = v2 - v3;

	//edge projections
	const Vector pvec = cross(ray.d, e2);
	const float det = dot(e1, pvec);

	//reject intersection if parallel to the plane
	if(fabs(det) <= epsilon)
		return Intersection::failure();

	const Vector tvec = ray.o - v3;
	const Vector qvec = cross(tvec, e1);

	const float idet = 1.0f / det;
	const float u = dot(tvec, pvec) * idet;
	const float v = dot(ray.d, qvec) * idet;
	//no need for w, as w=1-u-v

	//check for barycentric coordinates validity
	if(u < -epsilon || v < -epsilon || u+v > 1.0f + epsilon)
		return Intersection::failure();

	const float dist = dot(e2, qvec) * idet;

	//if all solutions are behind the ray, return failure
	if(dist < epsilon)
		return Intersection::failure();		

	//if found solution is better than previousBestDistance, use it, else return failure
	if(dist < previousBestDistance)
		return Intersection(dist, ray, this, n, Point(u,v,1-u-v));

	//nothing found -> return failure
	return Intersection::failure();

}

Solid::Sample Triangle::sample() const {
	float eps1 = random();
	float eps2 = random();

	struct Sample s;
	s.normal = n;

	if(eps1+eps2 < 1.0f)
		s.point = (1.0f-eps1-eps2)*v1 + eps1*v2 + eps2*v3;
	else
		s.point =  (eps1+eps2-1.0f)*v1 + (1.0f-eps1)*v2 + (1.0f-eps2)*v3;

	return s;
}

float Triangle::getArea() const {
    float area = cross ((v2-v1),(v3-v1)).length()/2.0f;
    return area;
}

}


//credit: intersection code taken from Omercan Yazici's tutorial presentaion.