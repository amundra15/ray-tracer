#include <rt/groups/simplegroup.h>
// #include <rt/intersection.h>

namespace rt {

BBox SimpleGroup::getBounds() const {
    /* TODO */ NOT_IMPLEMENTED;
}

Intersection SimpleGroup::intersect( const Ray& ray, float previousBestDistance) const {

	Intersection intersectionObj ;

	for(uint iter=0; iter<this->primitives.size(); iter++)
	{
		intersectionObj = this->primitives[iter]->intersect(ray, previousBestDistance);
		if(intersectionObj)
			previousBestDistance = intersectionObj.distance;
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
