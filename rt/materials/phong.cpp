#include <rt/materials/phong.h>
#include <rt/textures/texture.h>
#include <cmath>
#include <math.h>
#include <core/scalar.h>
namespace rt {

PhongMaterial::PhongMaterial(Texture* specular, float exponent)
{
	this->specular = specular;
	this->exponent = exponent;
}

//we have to implement purely glossy material here, thus we are ignoring the diffuse component
RGBColor PhongMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const {
	Vector reflectedLightDirection = (2 * dot(inDir, normal) * normal - inDir).normalize();
	    if (dot(reflectedLightDirection, normal) < 0 || dot(inDir, normal) < 0) return RGBColor(0, 0, 0);
	    float RV = dot(outDir.normalize(), reflectedLightDirection.normalize());
    if (RV < 0) return RGBColor(0, 0, 0);
	RGBColor brdf = specular->getColor(texPoint) * powf(RV, exponent);
    return brdf * (exponent + 2) / (2 * pi) * dot(inDir, normal);
}

RGBColor PhongMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
	return RGBColor::rep(0.0f);
}

Material::SampleReflectance PhongMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
	return SampleReflectance();
}

Material::Sampling PhongMaterial::useSampling() const {
	return Material::SAMPLING_NOT_NEEDED;
}

}