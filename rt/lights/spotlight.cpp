#include <rt/lights/spotlight.h>

namespace rt {

SpotLight::SpotLight(const Point& position, const Vector& direction, float angle, float power, const RGBColor& intensity)
{
    this->pos = position;
    this->direction = direction;
    this->angle = angle;
    this->power = power;
    this->intensity = intensity;
}



LightHit SpotLight::getLightHit(const Point & p) const
{
    Vector dir = pos - p;
    float len = dir.length();

    LightHit l;
    l.direction = dir/len;
    l.distance = len;
    l.normal = -dir/len;
    return l;
}

RGBColor SpotLight::getIntensity(const LightHit& irr) const 
{    
    float l_cosine = dot(-direction.normalize(),irr.direction.normalize());
    float spot_cosine = cos(angle);
 
    if (l_cosine > spot_cosine) { 
    	float r = 1 / (irr.distance * irr.distance);
       return intensity * powf(l_cosine,power)*r;
    }
    else{
        return RGBColor(0, 0, 0);
    }    

}

}
