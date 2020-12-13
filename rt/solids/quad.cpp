#include <rt/solids/quad.h>

namespace rt {

Quad::Quad(const Point& origin, const Vector& span1, const Vector& span2, CoordMapper* texMapper, Material* material)
{
    this->origin = origin;
	this->span1 = span1;
	this->span2 = span2;
	this->n = cross(span1, span2).normalize();
	a = origin;
	b = origin + span1;
	c = origin + span2;
	d = origin + span1 + span2;

	this->t1 = Triangle(a, b, c, texMapper, material);
	this->t2 = Triangle(b, d, c, texMapper, material);

	this->material = material;
}

BBox Quad::getBounds() const {
	BBox b = BBox::empty();
		b.extend(t1.getBounds());
		b.extend(t2.getBounds());
		return b;
}

Intersection Quad::intersect(const Ray& ray, float previousBestDistance) const {

	Intersection t1_intersect = t1.intersect(ray, previousBestDistance);
	
	Vector s = t1_intersect.hitPoint() - a;
	Vector vec1 = Vector(a.x, a.y, a.z);
	Vector vec2 = Vector(b.x, b.y, c.z);
	Vector vec3 = Vector(c.x, c.y, c.z);
	//Vector s  = ray.0-vec1;
	Vector e1 = vec2-vec1;
	Vector e2 = vec3-vec1;  
	float denom = dot(cross(ray.d, e2), e1);
	float b1 = dot(cross(ray.d, e2), s) / denom;
	float b2 = dot(cross(s, e1), ray.d) / denom;
	if (t1_intersect && t1_intersect.distance > 0 && t1_intersect.distance < previousBestDistance) 
	{
    	//Point intersectionPoint = Point(dot(p_a, span1) / denom, dot(p_a, span2) / denom, 0);
    	return Intersection(t1_intersect.distance, ray, this, t1_intersect.normal(),  Point((1-b1-b2), b1, b2));
    }
    		
    Intersection t2_intersect = t2.intersect(ray, previousBestDistance);
    if (t2_intersect && t2_intersect.distance > 0 && t2_intersect.distance < previousBestDistance) {
    	Vector s = t2_intersect.hitPoint() - a;
    	Vector vec1 = Vector(a.x, a.y, a.z);
    	Vector vec2 = Vector(b.x, b.y, c.z);
    	Vector vec3 = Vector(c.x, c.y, c.z);
    	//Vector s  = ray.0-vec1;
    	Vector e1 = vec2-vec1;
    	Vector e2 = vec3-vec1;  
    	float denom = dot(cross(ray.d, e2), e1);
    	float b1 = dot(cross(ray.d, e2), s) / denom;
    	float b2 = dot(cross(s, e1), ray.d) / denom;

		//Point intersectionPoint = Point(dot(p_a, span1) / denom, dot(p_a, span2) / denom, 0);
    	return Intersection(t2_intersect.distance, ray, this, t2_intersect.normal(), Point((1-b1-b2), b1, b2));
    	}

    	return Intersection::failure();
}

Solid::Sample Quad::sample() const {
    /* TODO */ NOT_IMPLEMENTED;
}

float Quad::getArea() const {
	float area = cross(span1,span2).length();
    return area;
}

}