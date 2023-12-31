#include <rt/solids/aabox.h>

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

namespace rt {

AABox::AABox(const Point& corner1, const Point& corner2, CoordMapper* texMapper, Material* material)
{
	this->corner1 = corner1;	
	this->corner2 = corner2;	
  	minimum = min(corner1, corner2);
	maximum = max(corner1, corner2);

	this->material = material;
	this->texMapper = texMapper;
}

BBox AABox::getBounds() const {
    return BBox(minimum, maximum);
}

Solid::Sample AABox::sample() const {
    NOT_IMPLEMENTED;
}

float AABox::getArea() const {
	float side_xy = (maximum.x - minimum.x) * (maximum.y - minimum.y);
	float side_yz = (maximum.y - minimum.y) * (maximum.z - minimum.z);
	float side_xz = (maximum.x - minimum.x) * (maximum.z - minimum.z);
  	float area = 2 * (side_xy + side_yz + side_xz);

	return area;
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

          	Vector n;
			if(t_near_farthest == t_near.x)
				n = Vector(-1*sgn(ray.d.x), 0, 0);
			else if(t_near_farthest == t_near.y)
				n = Vector(0, -1*sgn(ray.d.y), 0);
			else
				n = Vector(0, 0, -1*sgn(ray.d.z));

			return Intersection(t_near_farthest, ray, this, n, intersectionPoint);
		}
	}
	return Intersection::failure();
}

}
