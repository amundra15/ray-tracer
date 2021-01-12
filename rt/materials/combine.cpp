#include <rt/materials/combine.h>

namespace rt {

CombineMaterial::CombineMaterial()
{
    /* TODO */
}

void CombineMaterial::add(Material* m, float w) {
	materialsVector.push_back(m);
	weightsVector.push_back(w);
}

//TODO: consider the case when weights dont add up to 

RGBColor CombineMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const {
    
    RGBColor reflectance = RGBColor::rep(0.0f);

	for(int iter = 0; iter < materialsVector.size(); iter++)
	{
		if(materialsVector[iter]->useSampling() == Material::SAMPLING_NOT_NEEDED)
		{
			RGBColor r = materialsVector[iter]->getReflectance(texPoint, normal, outDir, inDir);
			float w = weightsVector[iter];
			reflectance = reflectance + w*r;
		}
	}

	return reflectance;
}

RGBColor CombineMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {

    RGBColor emission = RGBColor::rep(0.0f);

	for(int iter = 0; iter < materialsVector.size(); iter++)
	{
		if(materialsVector[iter]->useSampling() == Material::SAMPLING_NOT_NEEDED)
		{
			RGBColor e = materialsVector[iter]->getEmission(texPoint, normal, outDir);
			float w = weightsVector[iter];
			emission = emission + w*e;
		}
	}

	return emission;
}

Material::SampleReflectance CombineMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {

	int counter = 0;

	for(int iter = 0; iter < materialsVector.size(); iter++)
	{
		if(materialsVector[iter]->useSampling() == Material::SAMPLING_ALL)
		{
			SampleReflectance s = materialsVector[iter]->getSampleReflectance(texPoint, normal, outDir);
			float w = weightsVector[iter];
			return SampleReflectance(s.direction, w * s.reflectance);
		}
	}

	return SampleReflectance();
}

Material::Sampling CombineMaterial::useSampling() const {
    return Material::SAMPLING_SECONDARY;
}

}