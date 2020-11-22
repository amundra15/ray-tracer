#include <rt/intersection.h>

namespace rt {

Intersection::Intersection(float distance, const Ray& ray, const Solid* solid, const Vector& normal, const Point& local)
{
	this->ray = ray;
	this->distance = distance;
	this->solid = solid;
	this->normal_vec = normal;
	this->intersection_flag = true;
}

Intersection::operator bool() {
	return intersection_flag;
}

Intersection Intersection::failure() {
	Intersection failure_obj = Intersection();
	failure_obj.intersection_flag = false;
	return failure_obj;
}

Point Intersection::hitPoint() const {
    return ray.o + distance*ray.d;
}

Vector Intersection::normal() const {
	return normal_vec;
}

Point Intersection::local() const {
    /* TODO */ NOT_IMPLEMENTED;
}

}
