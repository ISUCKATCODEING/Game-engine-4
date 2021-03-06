#ifndef MESH_H
#define Mesh_H

#include <glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../../Camera/Camera.h"

struct Vertex {

	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 textureCoordinates;
	glm::vec3 colour;
};

struct SubMesh {
	std::vector<Vertex> vertexList;
	std::vector<unsigned int> meshIndices;
	GLuint textureID;
};

class Mesh
{
public:
	Mesh(SubMesh& subMesh_, GLuint shaderProgram_);
	~Mesh();

	void Render( Camera* camera_, std::vector<glm::mat4>& instances_);

private:
	void GenerateBuffers();
	GLuint VAO, VBO;
	GLuint shaderProgram;
	SubMesh subMesh;
	GLuint modelLocl, viewLocl, projectionLocl, textureLocl;
	GLuint viewPositionLocl, lightPositionLocl, ambientValueLocl, diffuseValueLocl, specularValueLocl, colourValueLocl;

};
#endif
