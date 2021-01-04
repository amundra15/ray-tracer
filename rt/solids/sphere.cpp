#include <rt/solids/sphere.h>

namespace rt {

Sphere::Sphere(const Point& center, float radius, CoordMapper* texMapper, Material* material)
{
    c = center;
    r = radius;
    
	this->material = material;
	this->texMapper = texMapper;
}

BBox Sphere::getBounds() const {
    return BBox(c - Vector(r, r, r), c + Vector(r, r, r));
}

Intersection Sphere::intersect(const Ray& ray, float previousBestDistance) const {
	
	float t = FLT_MAX;
	Vector diff = ray.o - c;

	//solve quadratice in t
	float A = dot(ray.d,ray.d);
	float B = 2*dot(ray.d,diff);
	float C = dot(diff,diff)-r*r;

	float discriminator = B*B - 4*A*C;

	if(discriminator<0)
		t = -1;		//will result in intersection failure
	else if(discriminator==0)
		t = -B/(2*A);
	else
	{
		float t1 = (-B-sqrt(discriminator)) / (2*A);
		float t2 = (-B+sqrt(discriminator)) / (2*A);

		//select the minimum positive value between the two
		if (t1 > 0)
			t = std::min(t1,t);
		if (t2 > 0)
			t = std::min(t2,t);
	}

	//consider intersection only if it is in the direction of the camera
	if(t>0 && t<previousBestDistance)
	{
		Point intersectionPoint = ray.o + (t*ray.d);
		Vector normal = (intersectionPoint - c) / r;		//normalised
		return Intersection(t, ray, this, normal, intersectionPoint);
	}
	else
		return Intersection::failure();

}

Solid::Sample Sphere::sample() const {
	NOT_IMPLEMENTED;
}

float Sphere::getArea() const {
	float area = 4.0f*pi*r*r;
	return area;
}

}
