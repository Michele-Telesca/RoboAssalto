#pragma once
#include "weapon.h"
#include "model.h"

class mapObject { //potrebbe essere utilizzato anche per l'albero 

public:

	//coordinate
	float x;
	float y;
	float z;
	float scale;
	float angle;
	float rotate_x;
	float rotate_y;
	float rotate_z;

	Model* objectModel;

	int shadowObject;
	int specular; //HIGH - MODERATE - NONE
	
	//costruttore no arg
	mapObject(){}

	//costruttore con arg
	mapObject(float px, float py, float pz, float s, float a, float r_x, float r_y, float r_z) {
		x = px;
		y = py;
		z = pz;
		scale = s;
		angle = a;
		rotate_x = r_x;
		rotate_y = r_y;
		rotate_z = r_z;
	}

	void initMapObject(string path);
	void drawMapObject(Shader myShader, Shader simpleShader);

	void setX(float new_x) {
		x = new_x;
	}

	void setZ(float new_z) {
		z = new_z;
	}

};

void mapObject::initMapObject(string path) {

	//caricamento modello
	objectModel = new Model();
	objectModel->loadModel(path);
	specular = HIGH;

}

void mapObject::drawMapObject(Shader lightShader,Shader simpleShader) {

	lightShader.use();

	// material properties
	lightShader.setVec3("material.ambient", 1.0f, 1.0f, 1.0f);
	lightShader.setVec3("material.diffuse", 1.0f, 1.0f, 1.0f);

	if (specular == NONE) {
		lightShader.setVec3("material.specular", 0.0f,0.0f, 0.0f);
		lightShader.setFloat("material.shininess", 50.0f);
	}
	else if (specular == MODERATE) {
		lightShader.setVec3("material.specular", 0.3f, 0.3f, 0.3f);
		lightShader.setFloat("material.shininess", 75.0f);
	}
	else if (specular == HIGH) {
		lightShader.setVec3("material.specular", 1.0f, 1.0f, 1.0f);
		lightShader.setFloat("material.shininess", 50.0f);
	}

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(x, y, z));
	model = glm::rotate(model, angle, glm::vec3(rotate_x, rotate_y, rotate_z));
	model = glm::scale(model, glm::vec3(scale, scale, scale));
	lightShader.setMat4("model", model);

	objectModel->Draw(lightShader);

	if (shadowObject != 0) {
		simpleShader.use();

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glActiveTexture(GL_TEXTURE0);

		glBindTexture(GL_TEXTURE_2D, shadowObject);
		glBindVertexArray(cubeVAO);

		//simpleShader.setVec3("colorcube", 1.0f, 0.0f, 0.0f);
		glm::mat4 modelSV = glm::mat4(1.0f);


		modelSV = glm::translate(modelSV, glm::vec3(x, y + 0.55f, z));
		modelSV = glm::rotate(modelSV, 3.14f / 2.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		modelSV = glm::translate(modelSV, glm::vec3(0.0f, 0.0f, 0.0f));
		modelSV = glm::scale(modelSV, glm::vec3(scale, 0.02f, scale));

		simpleShader.setMat4("model", modelSV);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glDisable(GL_BLEND);
	}
	
}

