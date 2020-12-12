#include <rt/groups/simplegroup.h>
// #include <rt/intersection.h>

namespace rt {


BBox SimpleGroup::getBounds() const {
    BBox b = BBox::empty();
	for (uint i = 0; i < primitives.size(); i++) {
		b.extend(primitives[i]->getBounds());
	};
	return b;
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
	for(uint iter=0; iter<this->primitives.size(); iter++)
		primitives[iter]->setMaterial(m);
}

void SimpleGroup::setCoordMapper(CoordMapper* cm) {
    /* TODO */ NOT_IMPLEMENTED;
}
float SimpleGroup::getArea() const {
		return 0;
	}
}
