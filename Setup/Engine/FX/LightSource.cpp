#include "LightSource.h"

LightSource::LightSource(glm::vec3 position_, glm::vec3 lightColour_, float ambiantValue_, float diffuseValue_, float specularValue_) : ambiantValue(0), diffuseValue(0), specularValue(0), position(glm::vec3()), lightColour(glm::vec3()) {
	ambiantValue = ambiantValue_;
	diffuseValue = diffuseValue_;
	specularValue = specularValue_;
	position = position_;
	lightColour = lightColour_;
}




LightSource::~LightSource()
{

}

float LightSource::getAmbiantValue() const
{
	return ambiantValue;
}

float LightSource::getDiffuseValue() const
{
	return diffuseValue;
}

float LightSource::getSpecularValue() const
{
	return specularValue;
}

glm::vec3 LightSource::getPosition() const
{
	return position;
}

glm::vec3 LightSource::getLightColour() const
{
	return lightColour;
}

void LightSource::setPosition(glm::vec3 position_)
{
}

void LightSource::setLightColor(glm::vec3 lightColour_)
{
}

void LightSource::setAmbiantValue(float ambiantValue_)
{
}

void LightSource::setDiffuseValue(float diffuseValue_)
{
}

void LightSource::setSpecularValue(float specularValue_)
{
}


