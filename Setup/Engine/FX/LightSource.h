#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H
 // !LIGHTSOURCE_H

#include <glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class LightSource
{
private:
	glm::vec3 position;
	glm::vec3 lightColour;

	float ambiantValue;
	float diffuseValue;
	float specularValue;

public:

	LightSource(glm::vec3 position_, glm::vec3 lightColour_, float ambiantValue_, float diffuseValue_, float specularValue_);
	~LightSource();

	float getAmbiantValue() const;
	float getDiffuseValue() const;
    float getSpecularValue() const;

	glm::vec3 getPosition() const;
	glm::vec3 getLightColour() const;

	void setPosition(glm::vec3 position_);
	void setLightColor(glm::vec3 lightColour_);

	void setAmbiantValue(float ambiantValue_);
	void setDiffuseValue(float diffuseValue_);
	void setSpecularValue(float specularValue_);
	


};
#endif
