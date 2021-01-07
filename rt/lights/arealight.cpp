#include <rt/lights/arealight.h>

#include <core/color.h>

namespace rt {

AreaLight::AreaLight(Solid* source)
{
	this->source = source;
}

LightHit AreaLight::getLightHit(const Point& p) const {
    
	Point position = source->sample().point;

    Vector dir = position - p;
    float len = dir.length();

    LightHit l;
    l.direction = dir/len;
    l.distance = len - 0.0001*len;	//you always need to reduce the distance of a light which is gonna appear in your scene. this is so that the shadow ray doesn't intersect with the light solid and create shadow everywhere in your scene.
    l.distance = len - 0.0001*len;
    l.normal = source->sample().normal;

    return l;
}

RGBColor AreaLight::getIntensity(const LightHit& irr) const {
	//the third paramter here is a vector going from the area light source to the object
	// RGBColor intensity = source->material->getEmission(const Point& texPoint, irr.normal, -irr.direction);

	//dummy arguments for now, as per the sheet.
	RGBColor intensity = source->material->getEmission(Point(), Vector(), Vector());
	float cosTheta = std::abs(dot(irr.normal,irr.direction));

	RGBColor temp = intensity * source->getArea() * cosTheta/(irr.distance * irr.distance);

	return intensity * source->getArea() * cosTheta/(irr.distance * irr.distance);
}

}