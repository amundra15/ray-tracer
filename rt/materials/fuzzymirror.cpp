#include <rt/materials/fuzzymirror.h>
#include <rt/solids/disc.h>
#include <cmath>

namespace rt {

FuzzyMirrorMaterial::FuzzyMirrorMaterial(float eta, float kappa, float fuzzyangle)
{
	this->eta = eta;
	this->kappa = kappa;
	this->fuzzyangle = fuzzyangle;
}

RGBColor FuzzyMirrorMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const {
	return RGBColor::rep(0.0f);
}

RGBColor FuzzyMirrorMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
	return RGBColor::rep(0.0f);
}

Material::SampleReflectance FuzzyMirrorMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
	
	Vector reflectedDirection = -outDir + 2 * dot(outDir,normal) * normal;
	
	//perturbation
	Point discCenter = texPoint + reflectedDirection.normalize();
	Vector discNormal = -reflectedDirection.normalize();
	float discRadius = tan(fuzzyangle);
	Disc perturbationDisc = Disc(discCenter, discNormal, discRadius, nullptr, nullptr);

	Point perturbationDiscPoint = perturbationDisc.sample().point;
	Vector perturbedReflectedDirection = perturbationDiscPoint - texPoint;


	float esks = sqr(eta) + sqr(kappa);
	float cosTheta = dot(outDir,normal) / (outDir.length()*normal.length());

	float r_parallel = (esks * sqr(cosTheta) - 2*eta*cosTheta + 1) / (esks * sqr(cosTheta) + 2*eta*cosTheta + 1);
	float r_perpendicular = (esks - 2*eta*cosTheta + sqr(cosTheta)) / (esks + 2*eta*cosTheta + sqr(cosTheta)); 

	float reflectance = 0.5f * (r_parallel + r_perpendicular);

	return SampleReflectance(perturbedReflectedDirection.normalize(), RGBColor::rep(reflectance));
}

Material::Sampling FuzzyMirrorMaterial::useSampling() const {
	return Material::SAMPLING_ALL;
}

}
