#include <rt/solids/disc.h>
#include <core/random.h>
#include <cmath>

namespace rt {

Disc::Disc(const Point& center, const Vector& normal, float radius, CoordMapper* texMapper, Material* material)
{
    c = center;
    n = normal.normalize();
    r = radius;

	this->material = material;
	this->texMapper = texMapper;
}

BBox Disc::getBounds() const {
    return BBox(c - Vector(r, r, r), c + Vector(r, r, r));

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

Vector polar2cartesian(float r, float theta, Vector n)
{
    //construct an orthogonal basis using disc normal
    float minVal = std::min(std::min(n.x,n.y),n.z);

    Vector s_;
    if(abs(minVal-n.x) <= epsilon)
        s_ = Vector(0,-n.z,n.y);
    else if(abs(minVal-n.y) <= epsilon)
        s_ = Vector(-n.z,0,n.x);
    else if(abs(minVal-n.z) <= epsilon)
        s_ = Vector(-n.y,n.x,0);

    Vector s = s_.normalize();
    Vector t = cross(n,s).normalize();

    float x = r * cos(theta);
    float y = r * sin(theta);

    return x*s + y*t;
}

Solid::Sample Disc::sample() const {

	float e1 = rt::random();
	float e2 = rt::random();

	Vector perturbation = polar2cartesian(e1*r, sqrt(e2)*2*pi, n);

	Sample sample = {c + perturbation, n};
		
	return sample;
}

float Disc::getArea() const {
	float area = pi*r*r;
	return area;
}

}
