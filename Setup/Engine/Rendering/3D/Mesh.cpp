#include "Mesh.h"

Mesh::Mesh(SubMesh& subMesh_, GLuint shaderProgram_) : VAO(0), VBO(0), shaderProgram(0), modelLocl(0), viewLocl(0), projectionLocl(0), textureLocl(0), viewPositionLocl(0), lightPositionLocl(0), ambientValueLocl(0), diffuseValueLocl(0), specularValueLocl(0), colourValueLocl(0) {
	
	subMesh = subMesh_;
	shaderProgram = shaderProgram_;
	GenerateBuffers();
}


Mesh::~Mesh() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	if (subMesh.vertexList.size() > 0) {
		subMesh.vertexList.clear();
	}

	if (subMesh.meshIndices.size() > 0) {
		subMesh.meshIndices.clear();
	}
}

void Mesh::Render(Camera* camera_, std::vector<glm::mat4>& instances_) {
	glUniform1i(textureLocl, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, subMesh.textureID);

	glUniformMatrix4fv(viewLocl, 1, GL_FALSE, glm::value_ptr(camera_->getView()));
	glUniformMatrix4fv(projectionLocl, 1, GL_FALSE, glm::value_ptr(camera_->getPerspective()));
	
	
	glBindVertexArray(VAO);



	glUniform3f(viewPositionLocl, camera_->GetPosition().x, camera_->GetPosition().y, camera_->GetPosition().z) ;
	glUniform3f(lightPositionLocl, camera_->GetLight()[0]->getPosition().x, camera_->GetLight()[0]->getPosition().y, camera_->GetLight()[0]->getPosition().z);
	glUniform3f(colourValueLocl, camera_->GetLight()[0]->getPosition().x, camera_->GetLight()[0]->getPosition().y, camera_->GetLight()[0]->getPosition().z);
	glUniform1f(ambientValueLocl, camera_->GetLight()[0]->getAmbiantValue());
	glUniform1f(diffuseValueLocl, camera_->GetLight()[0]->getDiffuseValue());
	glUniform1f(specularValueLocl, camera_->GetLight()[0]->getSpecularValue());


	glEnable(GL_DEPTH_TEST);

	for (int i = 0; i < instances_.size(); i++) {
		glUniformMatrix4x3fv(modelLocl, 1, GL_FALSE, glm::value_ptr(instances_[i]));
		glDrawArrays(GL_TRIANGLES, 0, subMesh.vertexList.size());
	}

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Mesh::GenerateBuffers() {
	// Generates VBO and VAO only makeing 1 of each so we pass in 1
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// bind the VBO and VAO to the gpu because we will store a lot od data hear and keep it hear.
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//the size of the array is the number of elements multiplied by eacch element of the vertexes
	glBufferData(GL_ARRAY_BUFFER, subMesh.vertexList.size() * sizeof(Vertex), &subMesh.vertexList[0], GL_STATIC_DRAW);

	//This is for position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

	//This is the normal
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));

	//Texture coordinates
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, textureCoordinates));

	//Color
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, colour));

	modelLocl = glGetUniformLocation(shaderProgram, "model");
	viewLocl = glGetUniformLocation(shaderProgram, "view");
	projectionLocl = glGetUniformLocation(shaderProgram, "projection");
	textureLocl = glGetUniformLocation(shaderProgram, "inputTexture");

	viewPositionLocl = glGetUniformLocation(shaderProgram, "light.cameraPosition");
	lightPositionLocl = glGetUniformLocation(shaderProgram, "light.lightPosition");
	ambientValueLocl = glGetUniformLocation(shaderProgram, "light.ambientValue");
	diffuseValueLocl = glGetUniformLocation(shaderProgram, "light.diffuseValue");
	specularValueLocl = glGetUniformLocation(shaderProgram, "light.specularValue");
	colourValueLocl = glGetUniformLocation(shaderProgram, " light.lightColour");

}