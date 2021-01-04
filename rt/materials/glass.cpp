#include <rt/materials/glass.h>
#include <core/scalar.h>
#include <core/random.h>

namespace rt {

GlassMaterial::GlassMaterial(float eta)
{
	this->eta = eta;
}

RGBColor GlassMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const {
	return RGBColor::rep(0.0f);
}

RGBColor GlassMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
	return RGBColor::rep(0.0f);
}

Material::SampleReflectance GlassMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
	
	float eta_t;
	if(dot(outDir,normal) > 0.0f)	//incoming ray from above the solid
		eta_t = eta;
	else							//incoming ray coming from below the solid
		eta_t = 1.0f/eta;


	float cosTheta_i = std::abs(dot(outDir,normal) / (outDir.length()*normal.length()));
	float cosTheta_t_sqr = 1 - (1 - sqr(cosTheta_i))/sqr(eta_t);

	if(cosTheta_t_sqr < 0.0f)
	{
		////total internal reflection - all the energy is reflected, non transmitted
		//reflected ray
		Vector reflectedDirection = -outDir + 2 * dot(outDir,normal) * normal;
		return SampleReflectance(reflectedDirection, RGBColor::rep(1.0f));
	}


	float cosTheta_t = sqrt(cosTheta_t_sqr);
	float r_parallel = (eta_t*cosTheta_i - cosTheta_t) / (eta_t*cosTheta_i + cosTheta_t);
	float r_perpendicular = (cosTheta_i - eta_t*cosTheta_t) / (cosTheta_i + eta_t*cosTheta_t);
	float reflectance = 0.5f * (sqr(r_parallel) + sqr(r_perpendicular));

	if(random() > 0.5f)
	{
		//reflected ray
		Vector reflectedDirection = -outDir + 2 * dot(outDir,normal) * normal;
		return SampleReflectance(reflectedDirection, 2*RGBColor::rep(reflectance));			//multiplied by 2 to compensate for the energy loss, when not considering the other ray
	}
	else
	{
		//refracted ray
		Vector refractedRay = ((cosTheta_i*normal - outDir) / eta_t) - normal * cosTheta_t;

		//not sure about the reason behind this, the Drone CI tests suggest this
		float transmittance;
		if(dot(outDir,normal) > 0.0f)
			transmittance = (1.0f-reflectance)/sqr(eta_t);
		else
			transmittance = 1.0f-reflectance;

		return SampleReflectance(refractedRay, 2*RGBColor::rep(transmittance));			//multiplied by 2 to compensate for the energy loss, when not considering the other ray
	}
}


Material::Sampling GlassMaterial::useSampling() const {
    return Material::SAMPLING_ALL;
}

}