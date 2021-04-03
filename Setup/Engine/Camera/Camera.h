#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../FX/LightSource.h"
#include <vector>


class Camera
{
public:
	Camera();
	~Camera();
	void SetPosition(glm::vec3 position_);
	void SetRotation(float yaw_, float pitch_);
	void AddLight(LightSource* lightsource_);
	std::vector<LightSource*> GetLight();
	

	glm::mat4 getView() const;
	glm::mat4 getPerspective() const;
	glm::mat4 GetOrthographic() const;
	glm::vec3 GetPosition() const;

private:
	void UpdateCameraVectors();
	glm::vec3 position;
	glm::mat4 perspective, orthographic, view;
	float fieldOfView;
	// yaw: distance in which the camera an go left or right, pitch:up and down of the world, roll;
	float yaw, pitch;
	float nearPlane, farPlane;
	glm::vec3 forward, up, right, worldUp;
	std::vector<LightSource*> lightSource;
};
#endif
