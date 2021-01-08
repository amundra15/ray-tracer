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
	
	//TODO: or the competetion, you can implement reflectivity as a function of incident angle, given by Fresnel equation.
	//check the pdf for the formula.

	//refraction index value depends on whether the ray is entering or leaving a material 
	float eta_t;
	if(dot(outDir,normal) > 0.0f)	//incoming ray from above the solid
		eta_t = eta;
	else							//incoming ray coming from below the solid
		eta_t = 1.0f/eta;


	float cosTheta_i = std::abs(dot(outDir,normal) / (outDir.length()*normal.length()));
	float cosTheta_t_sqr = 1 - (1 - sqr(cosTheta_i))/sqr(eta_t);


	//total internal reflection - all the energy is reflected, non transmitted
	if(cosTheta_t_sqr < 0.0f)
	{
		//reflected ray
		Vector reflectedDirection = -outDir + 2 * dot(outDir,normal) * normal;
		return SampleReflectance(reflectedDirection, RGBColor::rep(1.0f));
	}

	//estimate reflectance
	float cosTheta_t = std::abs(sqrt(cosTheta_t_sqr));
	float r_parallel = (eta_t*cosTheta_i - cosTheta_t) / (eta_t*cosTheta_i + cosTheta_t);
	float r_perpendicular = (cosTheta_i - eta_t*cosTheta_t) / (cosTheta_i + eta_t*cosTheta_t);
	float reflectance = 0.5f * (sqr(r_parallel) + sqr(r_perpendicular));

	//half the rays are reflected, half are refracted
	if(random() > 0.5f)
	{
		//reflected ray
		Vector reflectedDirection = -outDir + 2 * dot(outDir,normal) * normal;
		return SampleReflectance(reflectedDirection, 2*RGBColor::rep(reflectance));			//multiplied by 2 to compensate for the energy loss, when not considering the other ray
	}
	else
	{
		int sign = (dot(outDir,normal)>0) ? 1 : -1;

		//refracted ray
		Vector refractedRay = ((cosTheta_i*normal*sign - outDir) / eta_t) - normal * sign * cosTheta_t;
		//note: we needed to multiply sign variable with normal above because normal faces opposite directions wrt outDir when a ray enter and leaves a material 
		//see the derivation sheet attached

		//transmittance = (1 - reflectance) / sqr(eta of the refracted ray material)
		float transmittance;
		if(dot(outDir,normal) > 0.0f)
			transmittance = (1.0f-reflectance)/sqr(eta_t);
		else
			transmittance = 1.0f-reflectance;		//eta of refracted ray material = 1

		return SampleReflectance(refractedRay, 2*RGBColor::rep(transmittance));			//multiplied by 2 to compensate for the energy loss, when not considering the other ray
	}
}


Material::Sampling GlassMaterial::useSampling() const {
    return Material::SAMPLING_ALL;
}

}