#include <rt/materials/lambertian.h>
#include <core/scalar.h>

namespace rt {

LambertianMaterial::LambertianMaterial(Texture* emission, Texture* diffuse)
{
	this->emission = emission;
	this->diffuse = diffuse;
}

RGBColor LambertianMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const {
	float cosTheta = dot(inDir,normal) / (inDir.length()*normal.length());
	return diffuse->getColor(texPoint) * cosTheta / pi;
}

RGBColor LambertianMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
	return emission->getColor(texPoint);
}

Material::SampleReflectance LambertianMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
	return SampleReflectance();
}

Material::Sampling LambertianMaterial::useSampling() const {
	return Material::SAMPLING_NOT_NEEDED;
}

}