#include <rt/solids/aabox.h>

namespace rt {

AABox::AABox(const Point& corner1, const Point& corner2, CoordMapper* texMapper, Material* material)
{
	this->corner1 = corner1;	
	this->corner2 = corner2;	
}

BBox AABox::getBounds() const {
    /* TODO */ NOT_IMPLEMENTED;
}

Solid::Sample AABox::sample() const {
    NOT_IMPLEMENTED;
}

float AABox::getArea() const {
    /* TODO */ NOT_IMPLEMENTED;
}

Intersection AABox::intersect(const Ray& ray, float previousBestDistance) const {
	
	//intersection distances of the ray with the 6 planes defined by the 2 points
	//refernce: https://developer.arm.com/documentation/100140/0302/advanced-graphics-techniques/implementing-reflections-with-a-local-cubemap/ray-box-intersection-algorithm
	Vector t1 = (corner1 - ray.o) / ray.d;
	Vector t2 = (corner2 - ray.o) / ray.d;


	//intersection criteria
	//closer and farther plane intersection points for each dimension
	Vector t_near = min(t1,t2);		//point of intersection with three closer xyz planes
	Vector t_far = max(t1,t2);		//point of intersection with three farther xyz planes

	float t_near_farthest = std::max(std::max(t_near.x,t_near.y),t_near.z);		//largest distance among the three closer planes 
	float t_far_closest = std::min(std::min(t_far.x,t_far.y),t_far.z);			//shortest distance among the three farther planes

	if(t_near_farthest < t_far_closest)		//ray enters the box in all dimensions before exiting any
	{
		//t_near_farthest is the intersection point
		if(t_near_farthest>0 && t_near_farthest<previousBestDistance)
		{
			Point intersectionPoint = ray.o + t_near_farthest*ray.d;
			
			//TODO_a: implemet this with switch
          	Vector n;
			n = t_near_farthest == t1.x ? Vector(-1, 0, 0) : n;
			n = t_near_farthest == t2.x ? Vector(1, 0, 0) : n;
			n = t_near_farthest == t1.y ? Vector(0, -1, 0) : n;
			n = t_near_farthest == t2.y ? Vector(0, 1, 0) : n;
			n = t_near_farthest == t1.z ? Vector(0, 0, -1) : n;
			n = t_near_farthest == t2.z ? Vector(0, 0, 1) : n;

			return Intersection(t_near_farthest, ray, this, n, intersectionPoint);
		}
	}
	return Intersection::failure();
}

}
