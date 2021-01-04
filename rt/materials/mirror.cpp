#include <rt/materials/mirror.h>
#include <core/scalar.h>

namespace rt {

MirrorMaterial::MirrorMaterial(float eta, float kappa)
{
	this->eta = eta;
	this->kappa = kappa;
}

RGBColor MirrorMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const {
	return RGBColor::rep(0.0f);
}

RGBColor MirrorMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
	return RGBColor::rep(0.0f);
}

Material::SampleReflectance MirrorMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
	Vector reflectedDirection = -outDir + 2 * dot(outDir,normal) * normal;
	
	float esks = sqr(eta) + sqr(kappa);
	float cosTheta = dot(outDir,normal) / (outDir.length()*normal.length());

	float r_parallel = (esks * sqr(cosTheta) - 2*eta*cosTheta + 1) / (esks * sqr(cosTheta) + 2*eta*cosTheta + 1);
	float r_perpendicular = (esks - 2*eta*cosTheta + sqr(cosTheta)) / (esks + 2*eta*cosTheta + sqr(cosTheta)); 

	float reflectance = 0.5f * (r_parallel + r_perpendicular);

	return SampleReflectance(reflectedDirection, RGBColor::rep(reflectance));

}

Material::Sampling MirrorMaterial::useSampling() const {
	return Material::SAMPLING_ALL;
}

}