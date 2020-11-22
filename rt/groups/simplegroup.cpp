#include <rt/groups/simplegroup.h>
// #include <rt/intersection.h>

namespace rt {

BBox SimpleGroup::getBounds() const {
    /* TODO */ NOT_IMPLEMENTED;
}

Intersection SimpleGroup::intersect( const Ray& ray, float previousBestDistance) const {

	Intersection intersectionObj = Intersection::failure();
	Intersection intersectionObj_temp = Intersection::failure();

	for(uint iter=0; iter<this->primitives.size(); iter++)
	{
		intersectionObj_temp = this->primitives[iter]->intersect(ray, previousBestDistance);
		if(intersectionObj_temp)
		{
			intersectionObj = intersectionObj_temp;
			previousBestDistance = intersectionObj.distance;
		}
	}

	return intersectionObj;
}

void SimpleGroup::rebuildIndex() {
    //do nothing
}

void SimpleGroup::add(Primitive* p) {
	this->primitives.push_back(p);
}

void SimpleGroup::setMaterial(Material* m) {
    /* TODO */ NOT_IMPLEMENTED;
}

void SimpleGroup::setCoordMapper(CoordMapper* cm) {
    /* TODO */ NOT_IMPLEMENTED;
}

}
