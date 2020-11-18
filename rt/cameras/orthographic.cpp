#include <rt/cameras/orthographic.h>
#include <rt/ray.h>

namespace rt {

OrthographicCamera::OrthographicCamera(const Point& center, const Vector& forward, const Vector& up, float scaleX, float scaleY)
{
	this->center = center;
	this->d = forward.length();
	this->w = -forward.normalize();
	this->u = scaleX * cross(up,w).normalize() / 2.0;
	this->v = scaleY * cross(w,u).normalize() / 2.0;

}

Ray OrthographicCamera::getPrimaryRay(float x, float y) const {
    Point pixel_location = center + x*u + y*v;
    return Ray(pixel_location,-w);
}

}
