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
    l.distance = len;
    l.normal = source->sample().normal;

    return l;
}

RGBColor AreaLight::getIntensity(const LightHit& irr) const {
	//the third paramter here is a vector going from the area light source to the object
	// RGBColor intensity = source->material->getEmission(const Point& texPoint, irr.normal, -irr.direction);

	//dummy arguments for now, as per the sheet.
	RGBColor intensity = source->material->getEmission(Point(), Vector(), Vector());
	float cosTheta = std::abs(dot(irr.normal,irr.direction));

	return  intensity * source->getArea() * cosTheta/(irr.distance * irr.distance);
}

}