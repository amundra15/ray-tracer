#include <rt/materials/phong.h>
#include <rt/textures/texture.h>
#include <cmath>

namespace rt {

PhongMaterial::PhongMaterial(Texture* specular, float exponent)
{
	this->specular = specular;
	this->exponent = exponent;
}

//we have to implement purely glossy material here, thus we are ignoring the diffuse component
RGBColor PhongMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const {
	Vector reflectedLightDirection = -inDir + 2 * dot(inDir,normal) * normal;
	float brdf = std::pow(dot(reflectedLightDirection, outDir), exponent) / dot(inDir, normal);

    return brdf * specular->getColor(texPoint);
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